#include "convert_dataset.hpp"
#include "serialize.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/features2d.hpp>

namespace fs = std::filesystem;

using cv::xfeatures2d::SiftFeatureDetector;
using cv::xfeatures2d::SiftDescriptorExtractor;

cv::Mat computeSIFTDescriptors(const cv::Mat& image){
    auto detector = SiftFeatureDetector::create();
    std::vector<cv::KeyPoint> keypoints;
    detector->detect(image,keypoints);

    cv::Mat descriptors;
    auto extractor = SiftDescriptorExtractor::create();
    extractor->compute(image,keypoints,descriptors);

    return descriptors;
}

void ipb::serialization::sifts::ConvertDataset(const std::filesystem::path& img_dir_path){

    fs::path binPath;

    if(fs::is_directory(img_dir_path)){
        binPath= img_dir_path/"../bin";
    }else{
        binPath= img_dir_path.parent_path()/"bin";
    }
    fs::create_directory(binPath);

    for(auto const& dir_entry : std::filesystem::directory_iterator(img_dir_path)){
        fs::path imgPath = dir_entry.path();
        if (imgPath.extension() == ".png"){
            cv::Mat image = cv::imread(imgPath);
            cv::Mat descriptors = computeSIFTDescriptors(image);

            fs::path descriptorsPath = binPath/imgPath.stem();
            descriptorsPath += ".bin";

            //std::cout << __func__ << ": Serializing " << imgPath << ", output: " << descriptorsPath <<std::endl;

            Serialize(descriptors,descriptorsPath);
        }
    }

}

std::vector<cv::Mat> ipb::serialization::sifts::LoadDataset(const std::filesystem::path& bin_dir_path){

    std::vector<cv::Mat> descriptors;

    for(auto const& dir_entry : std::filesystem::directory_iterator(bin_dir_path)){
        fs::path binPath = dir_entry.path();
        if (binPath.extension() == ".bin"){
            cv::Mat siftDescriptor = Deserialize(binPath);

            descriptors.push_back(siftDescriptor);
        }
    }

    return descriptors;
}

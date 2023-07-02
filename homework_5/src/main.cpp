#include <iostream>
#include <string>
#include <vector>
#include <homework5.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/features2d.hpp>

using cv::xfeatures2d::SiftFeatureDetector;
using cv::xfeatures2d::SiftDescriptorExtractor;

int testConvertDataset(){
    ipb::serialization::sifts::ConvertDataset("../data/freiburg/images");

    std::vector<cv::Mat> dataset = ipb::serialization::sifts::LoadDataset("../data/freiburg/bin");

    return 0;
}

int testSerialize(){
    cv::Mat image = cv::imread("../data/lenna.png");

    if(image.empty()){
        std::cerr << "Image not found !!\n";
        return 1;
    }

    ipb::serialization::Serialize(image,"../data/lenna_copy.png");

    cv::Mat deserializedImg = ipb::serialization::Deserialize("../data/lenna_copy.png");

    std::string windowName{"Window1"};
    cv::namedWindow(windowName);
    cv::imshow(windowName, deserializedImg);
    cv::waitKey(0);

    return 0;
}

int showImageKeypointsAndDescriptors(){
    cv::Mat image = cv::imread("../data/lenna.png");

    if(image.empty()){
        std::cerr << "Image not found !!\n";
        return 1;
    }

    //Show image
    std::string windowImageName{"WindowImage"};
    cv::namedWindow(windowImageName);
    cv::imshow(windowImageName, image);

    auto detector = SiftFeatureDetector::create();
    std::vector<cv::KeyPoint> keypoints;
    detector->detect(image,keypoints);

    cv::Mat imgKeyPoints;
    cv::drawKeypoints(image,keypoints,imgKeyPoints);

    //Show image with keypoints
    std::string windowKeypointsName{"windowKeypoints"};
    cv::namedWindow(windowKeypointsName);
    cv::imshow(windowKeypointsName, imgKeyPoints);

    cv::Mat descriptors;
    auto extractor = SiftDescriptorExtractor::create();
    extractor->compute(image,keypoints,descriptors);

    //Show Descriptors
    std::string windowDescriptorsName{"windowDescriptors"};
    cv::namedWindow(windowDescriptorsName);
    cv::imshow(windowDescriptorsName, descriptors);

    cv::waitKey(0);

    return 0;
}

int main(int argc, char const *argv[])
{
    return testConvertDataset();
}

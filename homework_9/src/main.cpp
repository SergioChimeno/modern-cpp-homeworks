#include "homework_9.h"
//#include "convert_dataset.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    
    std::vector<cv::Mat> sifts = ipb::serialization::sifts::LoadDataset("../data/bin");
    ipb::kMeans(sifts,5,10);

    ipb::BowDictionary::build(10,5,sifts);
    ipb::BowDictionary& dictionary = ipb::BowDictionary::GetInstance();

    const cv::Mat& vocab = dictionary.vocabulary();
    //std::cout << vocab << std::endl;

    // Hisotgram for first image
    for(const auto& descriptors: sifts)
    {
        ipb::Histogram histogram(descriptors,dictionary);
        std::cout << "Histogram: " << histogram;
    }

    // Write to CSV
    ipb::Histogram histogram1(sifts[0],dictionary);
    histogram1.WriteToCSV("../data/histogram1.csv");
    std::cout << "histogram1: "<< histogram1;

    //Read from CSV
    ipb::Histogram histogram2 = ipb::Histogram::ReadFromCSV("../data/histogram1.csv");
    std::cout << "histogram2: " << histogram2;

    std::cout << "histogram2 empty? " << histogram2.empty() << std::endl;

    return 0;
}

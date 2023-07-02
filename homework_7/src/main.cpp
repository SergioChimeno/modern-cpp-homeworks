#include "homework_7.h"
#include "convert_dataset.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    
    std::vector<cv::Mat> sifts = ipb::serialization::sifts::LoadDataset("../data/bin");
    ipb::kMeans(sifts,5,10);

    ipb::BowDictionary& dictionary = ipb::BowDictionary::GetInstance();
    ipb::BowDictionary::set_params(10,5,sifts);

    const cv::Mat& vocab = dictionary.vocabulary();

    return 0;
}

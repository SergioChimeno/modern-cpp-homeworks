#include "BowDictionary.hpp"
#include "kMeans.h"

namespace ipb
{
    void BowDictionary::set_max_iterations(int maxIter)
    {
        BowDictionary::maxIter = maxIter;
    }
    
    void BowDictionary::set_size(int size)
    {
        dictionarySize = size;
    }

    void BowDictionary::set_descriptors(const std::vector<cv::Mat>& descriptors)
    {
        this->inputDescriptors = descriptors;
    }

    int BowDictionary::max_iterations() const
    {
        return maxIter;
    }

    int BowDictionary::size() const
    {
        return dictionarySize;
    }

    const std::vector<cv::Mat>& BowDictionary::descriptors() const 
    {
        return inputDescriptors;
    }

    const cv::Mat& BowDictionary::vocabulary() const
    {
        return dictionary;
    }

    int BowDictionary::total_features() const
    {
        int total_features = 0;
        for(cv::Mat descriptors: inputDescriptors)
        {
            total_features+=descriptors.rows;
        }
        return total_features;
    }

    bool BowDictionary::empty() const
    {
        if (dictionary.rows == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // Singleton
    BowDictionary BowDictionary::instance;

    BowDictionary& BowDictionary::GetInstance()
    {
        return instance;
    }

    void BowDictionary::set_params(int max_iter, int size, const std::vector<cv::Mat>& descriptors)
    {
        instance.set_max_iterations(max_iter);
        instance.set_size(size);
        instance.set_descriptors(descriptors);
        // Recompute dictionary
        instance.dictionary = kMeans(descriptors,size,max_iter);
    }
}
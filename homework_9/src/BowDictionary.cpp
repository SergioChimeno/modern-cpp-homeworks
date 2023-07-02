#include "BowDictionary.hpp"
#include "kMeans.h"
#include <iostream>
#include <cassert>  

namespace ipb
{
    void BowDictionary::set_size(int size)
    {
        dictionarySize_ = size;
    }

    int BowDictionary::size() const
    {
        assert(dictionarySize_ == vocabulary_.rows);
        return dictionarySize_;
    }

    void BowDictionary::set_vocabulary(const cv::Mat& vocabulary)
    {
        vocabulary_ = vocabulary;
        dictionarySize_ = vocabulary.rows;
    }

    cv::Mat BowDictionary::vocabulary() const
    {
        return vocabulary_;
    }

    bool BowDictionary::empty() const
    {
        if (vocabulary_.rows == 0)
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

    void BowDictionary::build(int max_iter, int size, const std::vector<cv::Mat>& descriptors)
    {
        std::cout << "BowDictionary::" << __func__<< ": dict size:" << size << ", max_iter:" << max_iter << ", number of images:" << descriptors.size()
                  <<  std::endl;
        instance.dictionarySize_ = size;
        // Compute vocabulary
        instance.vocabulary_ = kMeans(descriptors,size,max_iter);
    }
}
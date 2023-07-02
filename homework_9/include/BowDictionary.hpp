#ifndef BOW_DICTIONARY_HPP
#define BOW_DICTIONARY_HPP

#include <vector>
#include <opencv2/core/mat.hpp>

namespace ipb
{
    class BowDictionary
    {
    private:
        BowDictionary() = default;
        ~BowDictionary() = default;
        BowDictionary(BowDictionary& singleton) = delete;
        void operator=(BowDictionary& singleton) = delete;
        BowDictionary(BowDictionary&& singleton) = delete;
        void operator=(BowDictionary&& singleton) = delete;

        int dictionarySize_ = 0; // Number of visual words
        cv::Mat vocabulary_;

        // Singleton
        static BowDictionary instance;
    
    public:
        void set_size(int size);
        void set_vocabulary(const cv::Mat& vocabulary);

        int size() const;
        cv::Mat vocabulary() const;
        bool empty() const;

        // Singleton Methods
        static void build(int max_iter, int size, const std::vector<cv::Mat>& descriptors);
        static BowDictionary& GetInstance();
    };
}

#endif // BOW_DICTIONARY_HPP
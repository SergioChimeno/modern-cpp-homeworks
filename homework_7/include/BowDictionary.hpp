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

        int maxIter = 0;
        int dictionarySize = 0; // Number of visual words
        std::vector<cv::Mat> inputDescriptors;
        cv::Mat dictionary;

        // Singleton
        static BowDictionary instance;
    
    public:
        void set_max_iterations(int maxIter);
        void set_size(int size);
        void set_descriptors(const std::vector<cv::Mat>& descriptors);

        int max_iterations() const;
        int size() const;
        const std::vector<cv::Mat>& descriptors() const;
        const cv::Mat& vocabulary() const;
        int total_features() const;
        bool empty() const;

        // Singleton Methods
        static void set_params(int max_iter, int size, const std::vector<cv::Mat>& descriptors);
        static BowDictionary& GetInstance();
    };
}

#endif // BOW_DICTIONARY_HPP
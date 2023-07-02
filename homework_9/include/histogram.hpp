#include <vector>
#include "BowDictionary.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

namespace ipb
{
    class Histogram
    {
    public:
        Histogram() = default;
        Histogram(std::vector<int>& data);
        Histogram(const cv::Mat& descriptors, const BowDictionary& dictionary);
    
        friend std::ostream& operator<<(std::ostream& stream,const Histogram& histogram);
        bool WriteToCSV(const std::filesystem::path& path) const;
        static Histogram ReadFromCSV(const std::filesystem::path& path);

        // Imitate stl vector functionality
        int& operator[](uint32_t index);
        int operator[](uint32_t index) const;
        std::vector<int> data() const;
        int size() const;
        bool empty() const;
        // Iterators
        std::vector<int>::iterator begin();
        std::vector<int>::const_iterator begin() const;
        std::vector<int>::const_iterator cbegin() const;
        std::vector<int>::iterator end();
        std::vector<int>::const_iterator end() const;
        std::vector<int>::const_iterator cend() const;

    private:
        std::vector<int> data_;
    };
}
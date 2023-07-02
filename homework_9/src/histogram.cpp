#include "histogram.hpp"
#include <fstream>

namespace ipb
{

    Histogram::Histogram(std::vector<int>& data)
    {
        data_ = data;
    }

    Histogram::Histogram(const cv::Mat& descriptors, const BowDictionary& dictionary)
    {
        std::cout << "Histogram::" << __func__ << ": dictionary.size=" << dictionary.size()
                  << ", descriptors.size=" << descriptors.size() << std::endl;
        if(descriptors.rows > 0 && descriptors.cols>0)
        {
            data_.resize(dictionary.size(),0);
            cv::Mat vocabulary = dictionary.vocabulary();

            for(uint32_t i=0; i<descriptors.rows; i++)
            {
                cv::Mat descriptor = descriptors.row(i);

                // Obtain the nearest dictionary word to this descriptor.
                uint32_t nearestWordIndex = 0;
                uint32_t nearestWordDistance = UINT32_MAX;

                for(uint32_t j=0;j<vocabulary.rows;j++)
                {
                    cv::Mat word = vocabulary.row(j);
                    double distance = cv::norm(descriptor,word,cv::NORM_L2);
                    if (distance < nearestWordDistance)
                    {
                        nearestWordIndex = j;
                        nearestWordDistance = distance;
                    }
                }
                data_[nearestWordIndex]+=1;
            }
        }
    }

    std::ostream& operator<<(std::ostream& stream,const Histogram& histogram)
    {
        stream << "[ ";
        if(histogram.data_.size()>0)
        {
            stream << histogram[0];
        }
        for(int i = 1;i<histogram.data_.size();i++)
        {
            stream << ", " << histogram[i] ;
        }

        stream << " ]";
        stream << std::endl;
        return stream;
    }

    bool Histogram::WriteToCSV(const std::filesystem::path& path) const
    {
        std::ofstream fileOut(path);
        if(fileOut.is_open())
        {
            if(data_.size()>0)
            {
                fileOut << data_[0];
            }
            for(uint32_t i = 1;i<data_.size();i++)
            {
                fileOut <<","<<data_[i];
            }

            if(data_.size()>0) fileOut << std::endl;

            fileOut.close();
            return true;
        }
        else
        {
            return false;
        }
    }

    Histogram Histogram::ReadFromCSV(const std::filesystem::path& path)
    {
        std::ifstream fileIn(path);
        if(fileIn)
        {
            std::vector<int> data;
            uint32_t val = 0;
            char c = '\0';
            while(fileIn)
            {
                fileIn >> val;
                fileIn >> c;
                data.push_back(val);
            }
            fileIn.close();

            return Histogram(data);
        }
        else
        {
            return Histogram();
        }
    }

    int& Histogram::operator[](uint32_t index)
    {
        return data_[index];
    }

    int Histogram::operator[](uint32_t index) const
    {
        return data_[index];
    }

    std::vector<int> Histogram::data() const
    {
        return data_;
    }

    int Histogram::size() const
    {
        return data_.size();
    }

    bool Histogram::empty() const
    {
        if(data_.empty())
        {
            return true;
        }
        else
        {
            bool hasVW = false;

            for(int bin_val: data_)
            {
                if(bin_val != 0)
                {
                    hasVW = true;
                    break;
                } 
            }

            return !hasVW;
        }
    }

    std::vector<int>::iterator Histogram::begin()
    {
        return data_.begin();
    }

    std::vector<int>::const_iterator Histogram::begin() const
    {
        return data_.cbegin();
    }

    std::vector<int>::const_iterator Histogram::cbegin() const
    {
        return data_.cbegin();
    }

    std::vector<int>::iterator Histogram::end()
    {
        return data_.end();
    }

    std::vector<int>::const_iterator Histogram::end() const
    {
        return data_.cend();
    }

    std::vector<int>::const_iterator Histogram::cend() const
    {
        return data_.cend();
    }

};
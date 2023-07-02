#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <stdint.h>
#include <string>

namespace igg
{

class Image
{

public:
    Image();
    Image(int rows, int cols);
    
    int rows() const;
    int cols() const;

    uint8_t& at(int row, int col);
    uint8_t at(int row, int col) const;

    bool FillFromPgm(const std::string& file_name);
    void WriteToPgm(const std::string& file_name) const;

    std::vector<float> ComputeHistogram(int bins) const;

    void DownScale(int scale);
    void UpScale(int scale);

    friend std::ostream& operator<<(std::ostream& os, const igg::Image& img);

private:
    int rows_ = 0;
    int cols_ = 0;
    uint8_t max_val_ = 0u;

    std::vector<uint8_t> data_; 

};

}

#endif // IMAGE_HPP
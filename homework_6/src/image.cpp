#include "image.hpp"

#include "igg_image/io_tools.hpp"
#include "math.h"
#include <iostream>
#include <numeric>
#include <math.h>


namespace igg
{

Image::Image(){}

Image::Image(int rows, int cols)
    : data_()
{
    // rows and cols must be >= 0
    rows_ = std::max(rows, 0);
    cols_ = std::max(cols, 0);

    data_.resize(cols_*rows_);
}

int Image::rows() const
{
    return rows_;
}

int Image::cols() const
{
    return cols_;
}

uint8_t& Image::at(int row, int col)
{
    return data_[row*cols_ + col];
}

uint8_t Image::at(int row, int col) const
{
    return data_[row*cols_ + col];
}

bool Image::FillFromPgm(const std::string& file_name)
{
    io_tools::ImageData imageData = io_tools::ReadFromPgm(file_name);

    if (imageData.cols==0 && imageData.rows==0 && imageData.max_val==0 && imageData.data.empty())
        return false;

    rows_ = std::max(0,imageData.rows);
    cols_ = std::max(0,imageData.cols);
    max_val_ = imageData.max_val;

    data_ = std::move(imageData.data);

    return true;
}

void Image::WriteToPgm(const std::string& file_name) const
{
    io_tools::ImageData imageData = {rows_, cols_, max_val_, data_};
    io_tools::WriteToPgm(imageData, file_name);
}

int calculate_bin(uint8_t pixelValue,int bins)
{
    float bin_size = 256.0f/bins;
    int bin = floor(pixelValue/bin_size);

    return bin;
}

std::vector<float> Image::ComputeHistogram(int bins) const
{
    std::vector<float> histogram(bins,0);

    for(int i=0;i<rows_;i++)
    {
        for(int j=0;j<cols_;j++)
        {
            uint8_t pixelValue = at(i,j);
            int bin = calculate_bin(pixelValue,bins);
            histogram[bin]+=1;
        }
    }

    // Normalize histogram
    float totalSum = std::accumulate(histogram.begin(),histogram.end(),0);

    if(totalSum > 0)
        for(int i=0;i<histogram.size();i++)
        {
            histogram[i] = histogram[i]/totalSum;
        }
    

    return histogram;
}

void Image::DownScale(int scale)
{
    std::vector<uint8_t> newData;
    int newRows = rows_/scale;
    int newCols = cols_/scale;
    newData.resize(newRows*newCols);

    for(int i=0;i<newRows;i++)
    {
        for(int j=0;j<newCols;j++)
        {
            int elemOldRow = i*scale;
            int elemOldCol = j*scale;
            newData[i*newCols+j] = data_[elemOldRow*cols_+elemOldCol];
        }
    }

    cols_ = newCols;
    rows_ = newRows;
    data_ = std::move(newData);
}
    
void Image::UpScale(int scale)
{
    std::vector<uint8_t> newData;
    int newRows = rows_*scale;
    int newCols = cols_*scale;
    newData.resize(newRows*newCols);

    for(int i=0;i< newRows;i++)
    {
        for(int j=0;j<newCols;j++)
        {
            int elemOldRow = floor(i/scale);
            int elemOldCol = floor(j/scale);
            newData[i*newCols+j] = data_[elemOldRow*cols_+elemOldCol];
        }
    }

    cols_ = newCols;
    rows_ = newRows;
    data_ = std::move(newData);
}

std::ostream& operator<<(std::ostream& os, const igg::Image& img)
{
    static const int MAX_COLS = 20;
    static const int MAX_ROWS = 10;

    os << img.rows_ << "x" << img.cols_ << " Matrix\n";
    os << "max_val: " << static_cast<int>(img.max_val_) << std::endl;

    int pos=0;
    int i=0;
    for(; i<img.rows_&&i<MAX_ROWS;i++)
    {
        os << "[";
        if(img.cols_ > 0)
        {
            os << static_cast<int>(img.data_[pos++]);
        }

        int j=1;
        for(;j<img.cols_ && j<MAX_COLS ;j++)
        {
            os << ", " << static_cast<int>(img.data_[pos++]);
        }

        if(j==MAX_COLS && j<img.cols_)
        {
            os << " ...";
        }

        os << "]\n";
    }

    if(i==MAX_ROWS && i<img.rows_)
    {
        os << ".....\n";
    }

    return os;
}

}


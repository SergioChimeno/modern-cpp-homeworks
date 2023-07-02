#include "image.hpp"

#include "math.h"
#include <iostream>
#include <numeric>
#include <math.h>


namespace igg
{

Image::Pixel::Pixel(){}

Image::Pixel::Pixel(int red, int green, int blue)
    : red(red), green(green), blue(blue)
{}

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

Image::Pixel& Image::at(int row, int col)
{
    return data_[row*cols_ + col];
}

Image::Pixel Image::at(int row, int col) const
{
    return data_[row*cols_ + col];
}

bool Image::ReadFromDisk(const std::string& file_name)
{
    if(ioStrategy)
    {
        igg::ImageData imageData = ioStrategy->Read(file_name);

        if (imageData.cols==0 && imageData.rows==0 && imageData.max_val==0 && imageData.data.empty())
            return false;

        rows_ = std::max(0,imageData.rows);
        cols_ = std::max(0,imageData.cols);
        max_val_ = imageData.max_val;

        data_ = std::vector<Pixel>();
        for(int i=0;i<rows_*cols_;i++)
        {
            data_.push_back(Pixel(imageData.data[0][i], imageData.data[1][i], imageData.data[2][i]));
        }

        return true;
    }
    else
    {
        exit(1);
        return false;
    }
}

void Image::WriteToDisk(const std::string& file_name) const
{
    if(ioStrategy)
    {
        std::vector<int> red;
        std::vector<int> green;
        std::vector<int> blue;

        for(const Pixel& pixel: data_)
        {
            red.push_back(pixel.red);
            green.push_back(pixel.red);
            blue.push_back(pixel.red);
        }
        igg::ImageData imageData = {rows_, cols_, max_val_, {red,green,blue}};
        ioStrategy->Write(file_name,imageData);
    }
    else
    {
        exit(1);
    }
}

int calculate_bin(uint8_t pixelValue,int bins)
{
    float bin_size = 256.0f/bins;
    int bin = floor(pixelValue/bin_size);

    return bin;
}

void Image::DownScale(int scale)
{
    std::vector<Pixel> newData;
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
    std::vector<Pixel> newData;
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

void Image::SetIoStrategy(std::shared_ptr<IoStrategy> strategy_ptr)
{
    ioStrategy = strategy_ptr;
}

std::ostream& operator<<(std::ostream& os, const igg::Image::Pixel& pixel)
{
    os << "[" << pixel.red << ", " << pixel.green << ", " << pixel.blue << "]";

    return os;
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
            os << img.data_[pos++];
        }

        int j=1;
        for(;j<img.cols_ && j<MAX_COLS ;j++)
        {
            os << ", " << img.data_[pos++];
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


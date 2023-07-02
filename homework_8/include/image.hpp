#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <stdint.h>
#include <string>
#include <memory>
#include "io_strategies/strategy.h"

namespace igg
{

// Forward declaration

class Image
{

public:

    class Pixel
    {
    public:
        Pixel();
        Pixel(int red, int green, int blue);

        int red = 0;
        int green = 0;
        int blue = 0;

        friend std::ostream& operator<<(std::ostream& os, const Pixel& pixel);
    };

    Image();
    Image(int rows, int cols);
    
    int rows() const;
    int cols() const;

    Pixel& at(int row, int col);
    Pixel at(int row, int col) const;

    bool ReadFromDisk(const std::string& file_name);
    void WriteToDisk(const std::string& file_name) const;

    void DownScale(int scale);
    void UpScale(int scale);

    void SetIoStrategy(std::shared_ptr<IoStrategy> strategy_ptr);

    friend std::ostream& operator<<(std::ostream& os, const igg::Image& img);

private:
    int rows_ = 0;
    int cols_ = 0;
    uint8_t max_val_ = 0u;

    std::vector<Pixel> data_;
    std::shared_ptr<IoStrategy> ioStrategy;

};

}

#endif // IMAGE_HPP
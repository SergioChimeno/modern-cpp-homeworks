#include "homework_6.h"
#include <iostream>

int main(int argc, char const *argv[])
{

    igg::Image img;
    igg::Image img2(500,500);

    bool readSuccess = img.FillFromPgm("../data/lena.ascii.pgm");

    std::cout << "## Image 1:\n"<< img << std::endl;
    std::cout << "## Image 2:\n"<< img2 << std::endl;

    if(readSuccess)
    {
        img.UpScale(3);
        img.WriteToPgm("../data/lena_big.ascii.pgm");
        img.DownScale(8);
        img.WriteToPgm("../data/lena_small.ascii.pgm");
        img.UpScale(10);
        img.WriteToPgm("../data/lena_blur.ascii.pgm");
        std::vector<float> hist = img.ComputeHistogram(8);
    }

    return 0;
}

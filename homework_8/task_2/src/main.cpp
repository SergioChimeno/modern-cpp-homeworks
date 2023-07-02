#include "homework_8.h"
#include <iostream>
#include <memory>
#include "io_strategies/png_strategy.h"
#include "io_strategies/ppm_strategy.h"

int main(int argc, char const *argv[])
{

    igg::Image img;
    igg::Image img2(500,500);

    std::shared_ptr<igg::PpmIoStrategy> strategy = std::make_shared<igg::PpmIoStrategy>();
    img.SetIoStrategy(strategy);

    bool readSuccess = img.ReadFromDisk("../data/pbmlib.ascii.ppm");

    std::cout << "## Image 1:\n"<< img << std::endl;
    std::cout << "## Image 2:\n"<< img2 << std::endl;

    if(readSuccess)
    {
        // img.UpScale(3);
        // img.WriteToDisk("../data/lena_big.ascii.pgm");
        // img.DownScale(8);
        // img.WriteToDisk("../data/lena_small.ascii.pgm");
        // img.UpScale(10);
        // img.WriteToDisk("../data/lena_blur.ascii.pgm");
    }

    return 0;
}

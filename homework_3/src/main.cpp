#include "homework3.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    const std::vector<image_browser::ImageRow> imageRows {
        {image_browser::ScoredImage{"data/000000.png",0},image_browser::ScoredImage{"data/000100.png",0.001},image_browser::ScoredImage{"data/000200.png",2.32}},
        {image_browser::ScoredImage{"data/000300.png",2.321},image_browser::ScoredImage{"data/000400.png",1.342},image_browser::ScoredImage{"data/000500.png",5.12344321}},
        {image_browser::ScoredImage{"data/000600.png",45.32},image_browser::ScoredImage{"data/000700.png",4.00000},image_browser::ScoredImage{"data/000800.png",6.66666}}
    };

    image_browser::CreateImageBrowser("My images","./style.css",imageRows);

    return 0;
}

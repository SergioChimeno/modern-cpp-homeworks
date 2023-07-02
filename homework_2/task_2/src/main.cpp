#include <iostream>
#include <cstdlib>
#include <sstream>

#define TXT_EXT ".txt"
#define PNG_EXT ".png"

int main(int argc, char* argv[]){

    if ( argc != 3 ){
        std::cerr << "You have to specify 2 arguments" << std::endl;
        return EXIT_FAILURE;
    }

    std::stringstream ss1, ss2;
    std::string ext1, ext2;
    int num1, num2;

    ss1 << argv[1];
    ss2 << argv[2];

    ss1 >> num1 >> ext1;
    ss2 >> num2 >> ext2;

    if (ext1 == TXT_EXT && ext2 == TXT_EXT)
    {
        std::cout << (num1+num2)/2 << std::endl;
    }
    else if (ext1 == PNG_EXT && ext2 == PNG_EXT)
    {
        std::cout << num1+num2 << std::endl;
    }
    else if (ext1 == TXT_EXT && ext2 == PNG_EXT)
    {
        std::cout << num1%num2 << std::endl;
    }
    else
    {
        std::cerr << "Not supported Extensions" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
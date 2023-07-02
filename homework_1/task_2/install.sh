#!/usr/bin/env bash
mkdir -p install

# Add includes
cp -r include install/include

# Build library
c++ -c src/sum.cpp -I ./include/ -o build/sum.o
c++ -c src/subtract.cpp -I ./include/ -o build/substract.o

ar rcs build/libipb_arithmetic.a build/substract.o build/sum.o

# Add library binaries
mkdir -p install/lib
cp build/libipb_arithmetic.a ./install/lib


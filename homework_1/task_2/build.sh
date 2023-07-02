#!/usr/bin/env bash
mkdir -p build

#build library
c++ -c src/sum.cpp -I ./include/ -o build/sum.o
c++ -c src/subtract.cpp -I ./include/ -o build/substract.o

ar rcs build/libipb_arithmetic.a build/substract.o build/sum.o

#build main.cpp and link with library
c++ -std=c++14 src/main.cpp -I ./include/ -L build/ -lipb_arithmetic -o build/main.o

cp build/main.o results/bin/test_ipb_arithmetic
cp build/libipb_arithmetic.a results/lib
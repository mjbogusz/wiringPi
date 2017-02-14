#!/bin/sh -e
cd build
cmake -D CMAKE_C_COMPILER=gcc-6 -D CMAKE_CXX_COMPILER=g++-6 ..
make


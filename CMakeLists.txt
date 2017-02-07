cmake_minimum_required (VERSION 2.8.8 FATAL_ERROR)

project(WiringPi)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wformat=2 -Wall -Winline -fPIC")

add_subdirectory(wiringPi)
add_subdirectory(devLib)
add_subdirectory(gpio)
add_subdirectory(examples)

cmake_minimum_required (VERSION 2.8.8 FATAL_ERROR)

project(WiringPi)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -O2 -Wformat=2 -Wall -Winline -Wextra -fPIC")

set (LIB_VERSION_MAJOR 2)
set (LIB_VERSION_MINOR 36)
set (LIB_VERSION ${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR})

add_subdirectory(wiringPi)
add_subdirectory(devLib)
add_subdirectory(gpio)
# add_subdirectory(examples)

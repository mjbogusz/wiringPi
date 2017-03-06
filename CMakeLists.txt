cmake_minimum_required (VERSION 2.8.8 FATAL_ERROR)

project(WiringPi)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -O2 -Wformat=2 -Wall -Winline -Wextra -fPIC")
set (CMAKE_INSTALL_PREFIX /usr/)

set (LIB_VERSION_MAJOR 2)
set (LIB_VERSION_MINOR 42)
set (LIB_VERSION ${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR})

add_subdirectory (wiringPi)
add_subdirectory (devLib)
add_subdirectory (gpio)
add_subdirectory (wiringPiD)
add_subdirectory (examples)

# For future CPack commands (from http://stackoverflow.com/questions/11944060/how-to-detect-target-architecture-using-cmake)
# EXECUTE_PROCESS(COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE)

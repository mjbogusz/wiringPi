cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project(libwiringPi_gpio)

set (gpio_source_files
	gpio.c extensions.c readall.c pins.c
)

add_executable (gpio ${gpio_source_files})
target_link_libraries (gpio LINK_PUBLIC wiringPi wiringPiDev pthread)
target_include_directories (gpio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../wiringPi ${CMAKE_CURRENT_SOURCE_DIR}/../devLib)

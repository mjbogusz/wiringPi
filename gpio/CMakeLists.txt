cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project(libwiringPi_gpio)

set (gpio_source_files
  gpio.c
  pins.c
  readall.c
)
set (gpio_link_libraries
  wiringPi
  wiringPiDev
  pthread
  rt
  m
)

add_executable (gpio ${gpio_source_files})
target_link_libraries (gpio LINK_PUBLIC ${gpio_link_libraries})
target_include_directories (gpio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../wiringPi ${CMAKE_CURRENT_SOURCE_DIR}/../devLib)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/gpio
  DESTINATION bin
)

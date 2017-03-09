cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project(libwiringPi_wiringPiD)

set (wiringPiD_source_files
  daemonise.c
  network.c
  runRemote.c
  wiringpid.c
)
set (wiringPiD_link_libraries
  wiringPi
  wiringPiDev
  pthread
  rt
  m
  crypt
)

add_executable (wiringpid ${wiringPiD_source_files})
target_link_libraries (wiringpid LINK_PUBLIC ${wiringPiD_link_libraries})
target_include_directories (wiringpid PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../wiringPi ${CMAKE_CURRENT_SOURCE_DIR}/../devLib)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/wiringpid
  DESTINATION bin
)

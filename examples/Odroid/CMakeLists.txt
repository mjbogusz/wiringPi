cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project(libwiringPi_examples_odroid)

set (examples_include_dirs
  ${CMAKE_CURRENT_SOURCE_DIR}/../../wiringPi
  ${CMAKE_CURRENT_SOURCE_DIR}/../../devLib
)
set (examples_libs
  wiringPi
  wiringPiDev
  pthread
  m
)

set (examples_odroid
  blink_all_c2
)

foreach (example ${examples_odroid})
  add_executable (${example} EXCLUDE_FROM_ALL ${example}.c)
  target_include_directories (${example} PUBLIC ${examples_include_dirs})
  target_link_libraries (${example} LINK_PUBLIC ${examples_libs})
endforeach (example)

add_custom_target (examples_odroid DEPENDS ${examples_odroid})

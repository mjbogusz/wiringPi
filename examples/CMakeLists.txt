cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project(libwiringPi_examples)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")

set (examples_include_dirs
	${CMAKE_CURRENT_SOURCE_DIR}/../wiringPi
	${CMAKE_CURRENT_SOURCE_DIR}/../devLib
)
set (examples_libs
	wiringPi
	wiringPiDev
	pthread
	m
)

set (examples
  blink
  blink12
  blink12drcs
  blink8
  clock
  delayTest
  ds1302
  isr
  isr-osc
  lcd
  lcd-adafruit
  nes
  okLed
  # piglow
  pwm
  rht03
  serialRead
  serialTest
  softPwm
  softTone
  speed
  # tone
  wfi
)

foreach (example ${examples})
  add_executable (${example} EXCLUDE_FROM_ALL ${example}.c)
  target_include_directories (${example} PUBLIC ${examples_include_dirs})
  target_link_libraries (${example} LINK_PUBLIC ${examples_libs})
endforeach (example)

add_executable (piglow EXCLUDE_FROM_ALL PiGlow/piglow.c)
target_include_directories (piglow PUBLIC ${examples_include_dirs})
target_link_libraries (piglow LINK_PUBLIC ${examples_libs})

add_custom_target (examples DEPENDS ${examples})

add_subdirectory (Odroid)

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

add_executable (blink blink.c)
target_include_directories (blink PUBLIC ${examples_include_dirs})
target_link_libraries (blink LINK_PUBLIC ${examples_libs})

add_executable (blink12 blink12.c)
target_include_directories (blink12 PUBLIC ${examples_include_dirs})
target_link_libraries (blink12 LINK_PUBLIC ${examples_libs})

add_executable (blink12drcs blink12drcs.c)
target_include_directories (blink12drcs PUBLIC ${examples_include_dirs})
target_link_libraries (blink12drcs LINK_PUBLIC ${examples_libs})

add_executable (blink8 blink8.c)
target_include_directories (blink8 PUBLIC ${examples_include_dirs})
target_link_libraries (blink8 LINK_PUBLIC ${examples_libs})

add_executable (clock clock.c)
target_include_directories (clock PUBLIC ${examples_include_dirs})
target_link_libraries (clock LINK_PUBLIC ${examples_libs})

add_executable (delayTest delayTest.c)
target_include_directories (delayTest PUBLIC ${examples_include_dirs})
target_link_libraries (delayTest LINK_PUBLIC ${examples_libs})

add_executable (ds1302 ds1302.c)
target_include_directories (ds1302 PUBLIC ${examples_include_dirs})
target_link_libraries (ds1302 LINK_PUBLIC ${examples_libs})

add_executable (isr isr.c)
target_include_directories (isr PUBLIC ${examples_include_dirs})
target_link_libraries (isr LINK_PUBLIC ${examples_libs})

add_executable (isr-osc isr-osc.c)
target_include_directories (isr-osc PUBLIC ${examples_include_dirs})
target_link_libraries (isr-osc LINK_PUBLIC ${examples_libs})

add_executable (lcd lcd.c)
target_include_directories (lcd PUBLIC ${examples_include_dirs})
target_link_libraries (lcd LINK_PUBLIC ${examples_libs})

add_executable (lcd-adafruit lcd-adafruit.c)
target_include_directories (lcd-adafruit PUBLIC ${examples_include_dirs})
target_link_libraries (lcd-adafruit LINK_PUBLIC ${examples_libs})

add_executable (nes nes.c)
target_include_directories (nes PUBLIC ${examples_include_dirs})
target_link_libraries (nes LINK_PUBLIC ${examples_libs})

add_executable (okLed okLed.c)
target_include_directories (okLed PUBLIC ${examples_include_dirs})
target_link_libraries (okLed LINK_PUBLIC ${examples_libs})

add_executable (piglow PiGlow/piglow.c)
target_include_directories (piglow PUBLIC ${examples_include_dirs})
target_link_libraries (piglow LINK_PUBLIC ${examples_libs})

add_executable (pwm pwm.c)
target_include_directories (pwm PUBLIC ${examples_include_dirs})
target_link_libraries (pwm LINK_PUBLIC ${examples_libs})

add_executable (rht03 rht03.c)
target_include_directories (rht03 PUBLIC ${examples_include_dirs})
target_link_libraries (rht03 LINK_PUBLIC ${examples_libs})

add_executable (serialRead serialRead.c)
target_include_directories (serialRead PUBLIC ${examples_include_dirs})
target_link_libraries (serialRead LINK_PUBLIC ${examples_libs})

add_executable (serialTest serialTest.c)
target_include_directories (serialTest PUBLIC ${examples_include_dirs})
target_link_libraries (serialTest LINK_PUBLIC ${examples_libs})

add_executable (softPwm softPwm.c)
target_include_directories (softPwm PUBLIC ${examples_include_dirs})
target_link_libraries (softPwm LINK_PUBLIC ${examples_libs})

add_executable (softTone softTone.c)
target_include_directories (softTone PUBLIC ${examples_include_dirs})
target_link_libraries (softTone LINK_PUBLIC ${examples_libs})

add_executable (speed speed.c)
target_include_directories (speed PUBLIC ${examples_include_dirs})
target_link_libraries (speed LINK_PUBLIC ${examples_libs})

# add_executable (tone tone.c)
# target_include_directories PUBLIC (tone ${examples_include_dirs})
# target_link_libraries (tone LINK_PUBLIC ${examples_libs})

add_executable (wfi wfi.c)
target_include_directories (wfi PUBLIC ${examples_include_dirs})
target_link_libraries (wfi LINK_PUBLIC ${examples_libs})


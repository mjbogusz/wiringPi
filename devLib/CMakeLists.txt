cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project(libwiringPiDev)

set (LIB_VERSION_MAJOR 2)
set (LIB_VERSION_MINOR 0)
set (LIB_VERSION ${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR})

set (libwiringPiDev_source_files
	ds1302.c
	maxdetect.c
	piNes.c
	gertboard.c
	piFace.c
	lcd128x64.c
	lcd.c
	piGlow.c
)

add_library (wiringPiDev SHARED ${libwiringPiDev_source_files})
set_target_properties(wiringPiDev PROPERTIES VERSION ${LIB_VERSION} SOVERSION ${LIB_VERSION_MAJOR})
target_include_directories (wiringPiDev PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../wiringPi)
target_link_libraries (wiringPiDev LINK_PUBLIC wiringPi)

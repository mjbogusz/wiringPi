cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project(libwiringPi)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE")

set (LIB_VERSION_MAJOR 2)
set (LIB_VERSION_MINOR 0)
set (LIB_VERSION ${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR})

set (libwiringPi_source_files
	wiringPi.c
	wiringSerial.c
	wiringShift.c
	piHiPri.c
	piThread.c
	wiringPiSPI.c
	wiringPiI2C.c
	softPwm.c
	softTone.c
	mcp23008.c
	mcp23016.c
	mcp23017.c
	mcp23s08.c
	mcp23s17.c
	sr595.c
	pcf8574.c
	pcf8591.c
	mcp3002.c
	mcp3004.c
	mcp4802.c
	mcp3422.c
	max31855.c
	max5322.c
	sn3218.c
	drcSerial.c
)

add_library (wiringPi SHARED ${libwiringPi_source_files})
set_target_properties(wiringPi PROPERTIES VERSION ${LIB_VERSION} SOVERSION ${LIB_VERSION_MAJOR})
target_include_directories (wiringPi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

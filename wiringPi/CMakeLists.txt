cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project(libwiringPi)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE")

set (libwiringPi_source_files
  ads1115.c
  bmp180.c
  drcNet.c
  drcSerial.c
  ds18b20.c
  htu21d.c
  max31855.c
  max5322.c
  mcp23008.c
  mcp23016.c
  mcp23017.c
  mcp23s08.c
  mcp23s17.c
  mcp3002.c
  mcp3004.c
  mcp3422.c
  mcp4802.c
  pcf8574.c
  pcf8591.c
  piHiPri.c
  piThread.c
  pseudoPins.c
  rht03.c
  sn3218.c
  softPwm.c
  softTone.c
  sr595.c
  wiringPi.c
  wiringPiI2C.c
  wiringPiSPI.c
  wiringSerial.c
  wiringShift.c
  wpiExtensions.c
)

add_library (wiringPi SHARED ${libwiringPi_source_files})
set_target_properties(wiringPi PROPERTIES VERSION ${LIB_VERSION} SOVERSION ${LIB_VERSION_MAJOR})
target_link_libraries (wiringPi LINK_PUBLIC pthread m rt crypt)
target_include_directories (wiringPi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

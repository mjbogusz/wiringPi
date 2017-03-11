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
FILE(GLOB libwiringPi_header_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
FILE(GLOB libwiringPi_main_header_files "${CMAKE_CURRENT_SOURCE_DIR}/wiring*.h")

add_library (wiringPi SHARED ${libwiringPi_source_files})
set_target_properties(wiringPi PROPERTIES
  VERSION ${LIB_VERSION}
  SOVERSION ${LIB_VERSION_MAJOR}
)
target_link_libraries (wiringPi LINK_PUBLIC
  pthread
  m
  rt
  crypt
)
target_include_directories (wiringPi PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:>
)

install (TARGETS wiringPi
  EXPORT wiringPiTargets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION include
)
install (FILES ${libwiringPi_main_header_files}
  DESTINATION include
)
install (FILES ${libwiringPi_header_files}
  DESTINATION include/wiringPi
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/wiringPi/wiringPiConfigVersion.cmake"
  VERSION ${LIB_VERSION}
  COMPATIBILITY AnyNewerVersion
)
configure_file(../CMakeWiringPiConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/wiringPi/wiringPiConfig.cmake"
  COPYONLY
)

install (EXPORT wiringPiTargets
  DESTINATION lib/cmake/wiringPi
)
install (FILES
  "${CMAKE_CURRENT_BINARY_DIR}/wiringPi/wiringPiConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/wiringPi/wiringPiConfigVersion.cmake"
  DESTINATION lib/cmake/wiringPi
)

cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project(libwiringPiDev)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE")

set (libwiringPiDev_source_files
	ds1302.c
	maxdetect.c
	piNes.c
	gertboard.c
	piFace.c
	lcd128x64.c
	lcd.c
  scrollPhat.c
	piGlow.c
)
set (libwiringPiDev_header_files
  ds1302.h
  gertboard.h
  lcd.h
  lcd128x64.h
  maxdetect.h
  piFace.h
  piGlow.h
  piNes.h
  scrollPhat.h
)

add_library (wiringPiDev SHARED ${libwiringPiDev_source_files})
set_target_properties(wiringPiDev PROPERTIES VERSION ${LIB_VERSION} SOVERSION ${LIB_VERSION_MAJOR})
target_include_directories (wiringPiDev PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../wiringPi)
target_link_libraries (wiringPiDev LINK_PUBLIC wiringPi)

install(TARGETS wiringPiDev
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
install(FILES
  ${libwiringPiDev_header_files}
  DESTINATION include/wiringPi
)

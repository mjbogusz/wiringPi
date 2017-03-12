include("${CMAKE_CURRENT_LIST_DIR}/wiringPiTargets.cmake")

set (wiringPi_FOUND TRUE)
set (wiringPi_LIBRARIES "libwiringPi.so")
set (wiringPi_LINK_FLAGS "-lwiringPi")

set (CPACK_GENERATOR "DEB")
set (CPACK_PACKAGE_NAME "wiringpi-odroid")
set (CPACK_PACKAGE_VERSION_MAJOR ${LIB_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${LIB_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${LIB_VERSION_PATCH})
set (CPACK_PACKAGE_VERSION "${LIB_VERSION}")
set (CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, libc6-dev")
set (CPACK_PACKAGE_CONTACT "MJBogusz <mjbogusz.find.me.on.github@not.a.valid.email.address.com>")
set (CPACK_DEBIAN_PACKAGE_SECTION "libraries")
set (CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY
  "GPIO (I2C, SPI...) libraries for Raspberry Pi and Odroid boards"
)
set (CPACK_PACKAGE_DESCRIPTION
  "The wiringPi libraries, headers and gpio command" +
  "Libraries to allow GPIO access on a Raspberry Pi and Odroid boards from C and C++" +
  "and BASIC programs as well as from the command-line"
)
set (CPACK_SOURCE_STRIP_FILES true)
set (CPACK_STRIP_FILES true)
set (CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
  "${CMAKE_CURRENT_SOURCE_DIR}/debian-template/wiringPi/DEBIAN/postinst;" +
  "${CMAKE_CURRENT_SOURCE_DIR}/debian-template/wiringPi/DEBIAN/postrm;"
)
set (CPACK_PACKAGING_INSTALL_PREFIX "/usr")

# Architecture auto-detection. Idea from http://stackoverflow.com/questions/11944060/how-to-detect-target-architecture-using-cmake
execute_process (COMMAND uname -m COMMAND tr -d '\n\r' OUTPUT_VARIABLE ARCHITECTURE)
if ("${ARCHITECTURE}" STREQUAL "x86_64")
  set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
  message (STATUS "Detected architecture: amd64")
elseif ("${ARCHITECTURE}" MATCHES "i.86")
  set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE "i386")
  message (STATUS "Detected architecture: i386")
elseif ("${ARCHITECTURE}" STREQUAL "armhf" OR "${ARCHITECTURE}" STREQUAL "armv7l")
  set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE "armhf")
  message (STATUS "Detected architecture: armhf")
elseif ("${ARCHITECTURE}" STREQUAL "aarch64")
  set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE "arm64")
  message (STATUS "Detected architecture: arm64")
else ()
  message (FATAL_ERROR "Unrecognized processor architecture! Want it added? Create a pull request.")
endif ()

set (CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")

include (CPack)

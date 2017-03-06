#!/bin/sh -e

# build
#	Simple wiringPi build and install script
#
#	Copyright (c) 2012-2015 Gordon Henderson
#################################################################################
# This file is part of wiringPi:
#	A "wiring" library for the Raspberry Pi
#
#    wiringPi is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    wiringPi is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
#################################################################################
#
# wiringPi is designed to run on a Raspberry Pi only.
#	However if you're clever enough to actually look at this script to
#	see why it's not building for you, then good luck.
#
#	To everyone else: Stop using cheap alternatives. Support the
#	Raspberry Pi Foundation	as they're the only ones putting money
#	back into education!
#################################################################################

check_make_ok() {
  if [ $? != 0 ]; then
    echo ""
    echo "Make Failed..."
    echo "Please check the messages and fix any problems. If you're still stuck,"
    echo "then please email all the output and as many details as you can to"
    echo "  projects@drogon.net"
    echo ""
    exit 1
  fi
}

sudo=${WIRINGPI_SUDO-sudo}

if [ x$1 = "xclean" ]; then
  cd wiringPi
  echo -n "wiringPi:   "	; make clean
  cd ../devLib
  echo -n "DevLib:     "	; make clean
  cd ../gpio
  echo -n "gpio:       "	; make clean
  cd ../examples
  echo -n "Examples:   "	; make clean
  cd Gertboard
  echo -n "Gertboard:  "	; make clean
  cd ../PiFace
  echo -n "PiFace:     "	; make clean
  cd ../q2w
  echo -n "Quick2Wire: "	; make clean
  cd ../PiGlow
  echo -n "PiGlow:     "	; make clean
  cd ../scrollPhat
  echo -n "scrollPhat: "	; make clean
  exit
fi

if [ x$1 = "xuninstall" ]; then
  cd wiringPi
  echo -n "wiringPi: " ; $sudo make uninstall
  cd ../devLib
  echo -n "DevLib:   " ; $sudo make uninstall
  cd ../gpio
  echo -n "gpio:     " ; $sudo make uninstall
  exit
fi

# Only if you know what you're doing!

if [ x$1 = "xdebian" ]; then
  here=`pwd`
  cd debian-template/wiringPi
  rm -rf usr
  cd $here/wiringPi
  make install-deb
  cd $here/devLib
  make install-deb INCLUDE='-I. -I../wiringPi'
  cd $here/gpio
  make install-deb INCLUDE='-I../wiringPi -I../devLib' LDFLAGS=-L../debian-template/wiringPi/usr/lib
  cd $here/debian-template
  fakeroot dpkg-deb --build wiringPi
  mv wiringPi.deb  wiringpi-`cat $here/VERSION`-1.deb
  exit
fi

if [ x$1 != "x" ]; then
  echo "Usage: $0 [clean | uninstall]"
  exit 1
fi

  echo "wiringPi Build script"
  echo "====================="
  echo

  hardware=`fgrep Hardware /proc/cpuinfo | head -1 | awk '{ print $3 }'`

#  if [ x$hardware != "xBCM2708" ]; then
#    echo ""
#    echo "   +------------------------------------------------------------+"
#    echo "   |   wiringPi is designed to run on the Raspberry Pi only.    |"
#    echo "   |   This processor does not appear to be a Raspberry Pi.     |"
#    echo "   +------------------------------------------------------------+"
#    echo "   | In the unlikely event that you think it is a Raspberry Pi, |"
#    echo "   | then please accept my apologies and email the contents of  |"
#    echo "   | /proc/cpuinfo to projects@drogon.net.                      |"
#    echo "   |    - Thanks, Gordon                                        |"
#    echo "   +------------------------------------------------------------+"
#    echo ""
#    exit 1
#  fi


  echo
  echo "WiringPi Library"
  cd wiringPi
  $sudo make uninstall
  if [ x$1 = "xstatic" ]; then
    make -j5 static
    check_make_ok
    $sudo make install-static
  else
    make -j5
    check_make_ok
    $sudo make install
  fi
  check_make_ok

  echo
  echo "WiringPi Devices Library"
  cd ../devLib
  $sudo make uninstall
  if [ x$1 = "xstatic" ]; then
    make -j5 static
    check_make_ok
    $sudo make install-static
  else
    make -j5
    check_make_ok
    $sudo make install
  fi
  check_make_ok

  echo
  echo "GPIO Utility"
  cd ../gpio
  make -j5
  check_make_ok
  $sudo make install
  check_make_ok

# echo
# echo "wiringPi Daemon"
# cd ../wiringPiD
# make -j5
# check_make_ok
# $sudo make install
# check_make_ok

# echo
# echo "Examples"
# cd ../examples
# make
# cd ..

echo
echo All Done.
echo ""
echo "NOTE: To compile programs with wiringPi, you need to add:"
echo "    -lwiringPi"
echo "  to your compile line(s) To use the Gertboard, MaxDetect, etc."
echo "  code (the devLib), you need to also add:"
echo "    -lwiringPiDev"
echo "  to your compile line(s)."
echo ""

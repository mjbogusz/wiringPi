/*
 * readall.c:
 *	The readall functions - getting a bit big, so split them out.
 *	Copyright (c) 2012-2017 Gordon Henderson
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <wiringPi.h>

extern int wpMode ;

#ifndef TRUE
#  define       TRUE    (1==1)
#  define       FALSE   (1==2)
#endif

/*
 * doReadallExternal:
 *	A relatively crude way to read the pins on an external device.
 *	We don't know the input/output mode of pins, but we can tell
 *	if it's an analog pin or a digital one...
 *********************************************************************************
 */

static void doReadallExternal (void)
{
  int pin ;

  printf ("+------+---------+--------+\n") ;
  printf ("|  Pin | Digital | Analog |\n") ;
  printf ("+------+---------+--------+\n") ;

  for (pin = wiringPiNodes->pinBase ; pin <= wiringPiNodes->pinMax ; ++pin)
    printf ("| %4d |  %4d   |  %4d  |\n", pin, digitalRead (pin), analogRead (pin)) ;

  printf ("+------+---------+--------+\n") ;
}


/*
 * doReadall:
 *	Read all the GPIO pins
 *	We also want to use this to read the state of pins on an externally
 *	connected device, so we need to do some fiddling with the internal
 *	wiringPi node structures - since the gpio command can only use
 *	one external device at a time, we'll use that to our advantage...
 *********************************************************************************
 */

static char *alts [] =
{
  "IN", "OUT", "ALT5", "ALT4", "ALT0", "ALT1", "ALT2", "ALT3"
} ;

static int physToWpi [64] =
{
  -1,           // 0
  -1, -1,       // 1, 2
   8, -1,
   9, -1,
   7, 15,
  -1, 16,
   0,  1,
   2, -1,
   3,  4,
  -1,  5,
  12, -1,
  13,  6,
  14, 10,
  -1, 11,       // 25, 26
  30, 31,	// Actually I2C, but not used
  21, -1,
  22, 26,
  23, -1,
  24, 27,
  25, 28,
  -1, 29,
  -1, -1,
  -1, -1,
  -1, -1,
  -1, -1,
  -1, -1,
  17, 18,
  19, 20,
  -1, -1, -1, -1, -1, -1, -1, -1, -1
} ;

static char *physNames [64] =
{
  NULL,

  "   3.3v", "5v     ",
  "  SDA.1", "5v     ",
  "  SCL.1", "0v     ",
  "GPIO. 7", "TxD    ",
  "     0v", "RxD    ",
  "GPIO. 0", "GPIO. 1",
  "GPIO. 2", "0v     ",
  "GPIO. 3", "GPIO. 4",
  "   3.3v", "GPIO. 5",
  "   MOSI", "0v     ",
  "   MISO", "GPIO. 6",
  "   SCLK", "CE0    ",
  "     0v", "CE1    ",
  "  SDA.0", "SCL.0  ",
  "GPIO.21", "0v     ",
  "GPIO.22", "GPIO.26",
  "GPIO.23", "0v     ",
  "GPIO.24", "GPIO.27",
  "GPIO.25", "GPIO.28",
  "     0v", "GPIO.29",
       NULL, NULL,
       NULL, NULL,
       NULL, NULL,
       NULL, NULL,
       NULL, NULL,
  "GPIO.17", "GPIO.18",
  "GPIO.19", "GPIO.20",
   NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
} ;

static char *physNamesOdroidc [64] =
{
  NULL,

  "    3.3v", "5v      ",
  "   SDA.1", "5V      ",
  "   SCL.1", "0v      ",
  "GPIO. 83", "TxD1    ",
  "      0v", "RxD1    ",
  "GPIO. 88", "GPIO. 87",
  "GPIO.116", "0v      ",
  "GPIO.115", "GPIO.104",
  "    3.3v", "GPIO.102",
  "    MOSI", "0v      ",
  "    MISO", "GPIO.103",
  "    SCLK", "CE0     ",
  "      0v", "GPIO.118",
  "   SDA.2", "SCL.2   ",
  "GPIO.101", "0v      ",
  "GPIO.100", "GPIO. 99",
  "GPIO.108", "0v      ",
  "GPIO.97 ", "GPIO. 98",
  "   AIN.1", "1v8     ",
  "      0v", "AIN.0   ",

   NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
   NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
   NULL,NULL,NULL,
} ;

static char *physNamesOdroidc2_Rev1_1 [64] =
{
  NULL,

  "    3.3v", "5v      ",
  "   SDA.1", "5V      ",
  "   SCL.1", "0v      ",
  "GPIO.249", "TxD1    ",
  "      0v", "RxD1    ",
  "GPIO.247", "GPIO.238",
  "GPIO.239", "0v      ",
  "GPIO.237", "GPIO.236",
  "    3.3v", "GPIO.233",
  "GPIO.235", "0v      ",
  "GPIO.232", "GPIO.231",
  "GPIO.230", "GPIO.229",
  "      0v", "GPIO.225",
  "   SDA.2", "SCL.2   ",
  "GPIO.228", "0v      ",
  "GPIO.219", "GPIO.224",
  "GPIO.234", "0v      ",
  "GPIO.214", "GPIO.218",
  "   AIN.1", "1v8     ",
  "      0v", "AIN.0   ",

   NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
   NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
   NULL,NULL,NULL,
} ;

static char *physNamesOdroidc2_Rev1_0 [64] =
{
  NULL,

  "    3.3v", "5v      ",
  "   SDA.1", "5V      ",
  "   SCL.1", "0v      ",
  "GPIO.214", "--------",
  "      0v", "--------",
  "GPIO.219", "GPIO.218",
  "GPIO.247", "0v      ",
  "--------", "GPIO.235",
  "    3.3v", "GPIO.233",
  "GPIO.238", "0v      ",
  "GPIO.237", "GPIO.234",
  "GPIO.236", "GPIO.248",
  "      0v", "GPIO.249",
  "   SDA.2", "SCL.2   ",
  "GPIO.232", "0v      ",
  "GPIO.231", "GPIO.230",
  "GPIO.239", "0v      ",
  "GPIO.228", "GPIO.229",
  "   AIN.1", "1v8     ",
  "      0v", "AIN.0   ",

   NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
   NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
   NULL,NULL,NULL,
} ;

static char *physNamesOdroidXU [64] =
{
  NULL,

  "    3.3v", "5v      ",
  "I2C1.SDA", "5V      ",
  "I2C1.SCL", "0v      ",
  "GPIO. 18", "UART0.TX",
  "      0v", "UART0.RX",
  "GPIO.174", "GPIO.173",
  "GPIO. 21", "0v      ",
  "GPIO. 22", "GPIO. 19",
  "    3.3v", "GPIO. 23",
  "    MOSI", "0v      ",
  "    MISO", "GPIO. 24",
  "    SCLK", "CE0     ",
  "      0v", "GPIO. 25",
  "I2C5.SDA", "I2C5.SCL",
  "GPIO. 28", "0v      ",
  "GPIO. 30", "GPIO. 29",
  "GPIO. 31", "0v      ",
  "POWER ON", "GPIO. 33",
  "   AIN.0", "1v8     ",
  "      0v", "AIN.3   ",

   NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
   NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
   NULL,NULL,NULL,
} ;

/*
 * readallPhys:
 *	Given a physical pin output the data on it and the next pin:
 *| BCM | wPi |   Name  | Mode | Val| Physical |Val | Mode | Name    | wPi | BCM |
 *********************************************************************************
 */

static void readallPhys (int physPin)
{
  int pin ;

  if (physPinToGpio (physPin) == -1)
    printf (" |     |    ") ;
  else
    printf (" | %3d | %3d", physPinToGpio (physPin), physToWpi [physPin]) ;

  printf (" | %s", physNames [physPin]) ;

  if (physToWpi [physPin] == -1)
    printf (" |      |  ") ;
  else
  {
    /**/ if (wpMode == WPI_MODE_GPIO)
      pin = physPinToGpio (physPin) ;
    else if (wpMode == WPI_MODE_PHYS)
      pin = physPin ;
    else
      pin = physToWpi [physPin] ;

    printf (" | %4s", alts [getAlt (pin)]) ;
    printf (" | %d", digitalRead (pin)) ;
  }

// Pin numbers:

  printf (" | %2d", physPin) ;
  ++physPin ;
  printf (" || %-2d", physPin) ;

// Same, reversed

  if (physToWpi [physPin] == -1)
    printf (" |   |     ") ;
  else
  {
    /**/ if (wpMode == WPI_MODE_GPIO)
      pin = physPinToGpio (physPin) ;
    else if (wpMode == WPI_MODE_PHYS)
      pin = physPin ;
    else
      pin = physToWpi [physPin] ;

    printf (" | %d", digitalRead (pin)) ;
    printf (" | %-4s", alts [getAlt (pin)]) ;
  }

  printf (" | %-5s", physNames [physPin]) ;

  if (physToWpi     [physPin] == -1)
    printf (" |     |    ") ;
  else
    printf (" | %-3d | %-3d", physToWpi [physPin], physPinToGpio (physPin)) ;

  printf (" |\n") ;
}


/*
 * allReadall:
 *	Read all the pins regardless of the model. Primarily of use for
 *	the compute module, but handy for other fiddling...
 *********************************************************************************
 */

static void allReadall (void)
{
  int pin ;

  printf ("+-----+------+-------+      +-----+------+-------+\n") ;
  printf ("| Pin | Mode | Value |      | Pin | Mode | Value |\n") ;
  printf ("+-----+------+-------+      +-----+------+-------+\n") ;

  for (pin = 0 ; pin < 27 ; ++pin)
  {
    printf ("| %3d ", pin) ;
    printf ("| %-4s ", alts [getAlt (pin)]) ;
    printf ("| %s  ", digitalRead (pin) == HIGH ? "High" : "Low ") ;
    printf ("|      ") ;
    printf ("| %3d ", pin + 27) ;
    printf ("| %-4s ", alts [getAlt (pin + 27)]) ;
    printf ("| %s  ", digitalRead (pin + 27) == HIGH ? "High" : "Low ") ;
    printf ("|\n") ;
  }

  printf ("+-----+------+-------+      +-----+------+-------+\n") ;

}


/*
 * abReadall:
 *	Read all the pins on the model A or B.
 *********************************************************************************
 */

void abReadall (int model, int rev)
{
  int pin ;
  char *type ;

  if (model == PI_MODEL_A)
    type = " A" ;
  else
    if (rev == PI_VERSION_2)
      type = "B2" ;
    else
      type = "B1" ;

  printf (" +-----+-----+---------+------+---+-Model %s-+---+------+---------+-----+-----+\n", type) ;
  printf (" | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |\n") ;
  printf (" +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+\n") ;
  for (pin = 1 ; pin <= 26 ; pin += 2)
    readallPhys (pin) ;

  if (rev == PI_VERSION_2) // B version 2
  {
    printf (" +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+\n") ;
    for (pin = 51 ; pin <= 54 ; pin += 2)
      readallPhys (pin) ;
  }

  printf (" +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+\n") ;
  printf (" | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |\n") ;
  printf (" +-----+-----+---------+------+---+-Model %s-+---+------+---------+-----+-----+\n", type) ;
}


/*
 * piPlusReadall:
 *	Read all the pins on the model A+ or the B+
 *********************************************************************************
 */

static void plus2header (int model)
{
  /**/ if (model == PI_MODEL_AP)
    printf (" +-----+-----+---------+------+---+--A Plus--+---+------+---------+-----+-----+\n") ;
  else if (model == PI_MODEL_BP)
    printf (" +-----+-----+---------+------+---+--B Plus--+---+------+---------+-----+-----+\n") ;
  else if (model == PI_MODEL_ZERO)
    printf (" +-----+-----+---------+------+---+-Pi Zero--+---+------+---------+-----+-----+\n") ;
  else if (model == PI_MODEL_ZERO_W)
    printf (" +-----+-----+---------+------+---+-Pi ZeroW-+---+------+---------+-----+-----+\n") ;
  else if (model == PI_MODEL_2)
    printf (" +-----+-----+---------+------+---+---Pi 2---+---+------+---------+-----+-----+\n") ;
  else if (model == PI_MODEL_3)
    printf (" +-----+-----+---------+------+---+---Pi 3---+---+------+---------+-----+-----+\n") ;
  else
    printf (" +-----+-----+---------+------+---+---Pi ?---+---+------+---------+-----+-----+\n") ;
}


static void piPlusReadall (int model)
{
  int pin ;

  plus2header (model) ;

  printf (" | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |\n") ;
  printf (" +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+\n") ;
  for (pin = 1 ; pin <= 40 ; pin += 2)
    readallPhys (pin) ;
  printf (" +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+\n") ;
  printf (" | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |\n") ;

  plus2header (model) ;
}

static void readallPhysOdroidC (int physPin, int model, int rev)
{
  int pin ;

  if     ((physPinToGpio (physPin) == -1)  && (physToWpi [physPin] == -1))
    printf (" |      |    ");
  else if (physPinToGpio (physPin) != -1)
    printf (" |  %3d | %3d", physPinToGpio (physPin), physToWpi [physPin]);
  else
    printf (" |      | %3d", physToWpi [physPin]);

  if (model == PI_MODEL_ODROIDC)
	printf (" | %s", physNamesOdroidc [physPin]) ;
  else {
	if (rev == PI_VERSION_1)
		printf (" | %s", physNamesOdroidc2_Rev1_0 [physPin]) ;
	else
		printf (" | %s", physNamesOdroidc2_Rev1_1 [physPin]) ;
  }

  if ((physToWpi [physPin] == -1) || (physPinToGpio (physPin) == -1))
    printf (" |      |  ");
  else
  {
    /**/ if (wpMode == WPI_MODE_GPIO)
      pin = physPinToGpio (physPin) ;
    else if (wpMode == WPI_MODE_PHYS)
      pin = physPin ;
    else
      pin = physToWpi [physPin] ;

	if( physPinToGpio (physPin) == -1 )	{
	    printf (" |      |  ") ;
	}
	else	{
	    printf (" | %4s", alts [getAlt (pin)]) ;
	    printf (" | %d", digitalRead (pin)) ;
	}
  }

// Pin numbers:

  printf (" | %2d", physPin) ;
  ++physPin ;
  printf (" || %-2d", physPin) ;

// Same, reversed

  if ((physToWpi [physPin] == -1) || (physPinToGpio (physPin) == -1))
    printf (" |   |     ");
  else
  {
    /**/ if (wpMode == WPI_MODE_GPIO)
      pin = physPinToGpio (physPin) ;
    else if (wpMode == WPI_MODE_PHYS)
      pin = physPin ;
    else
      pin = physToWpi [physPin] ;

	if (physPinToGpio (physPin) == -1)	{
	    printf (" |   |     ") ;
	}
	else	{
	    printf (" | %d", digitalRead (pin)) ;
	    printf (" | %-4s", alts [getAlt (pin)]) ;
	}
  }

  if (model == PI_MODEL_ODROIDC)
	  printf (" | %-6s", physNamesOdroidc [physPin]) ;
  else {
	if (rev == PI_VERSION_1)
		printf (" | %-6s", physNamesOdroidc2_Rev1_0 [physPin]) ;
	else
		printf (" | %-6s", physNamesOdroidc2_Rev1_1 [physPin]) ;
  }

  if     ((physPinToGpio (physPin) == -1) && (physToWpi [physPin] == -1))
    printf (" |     |     ");
  else if (physPinToGpio (physPin) != -1)
    printf (" | %-3d |  %-3d", physToWpi [physPin], physPinToGpio (physPin));
  else
    printf (" | %-3d |     ", physToWpi [physPin]);

  printf (" |\n") ;
}

void ReadallOdroidC (int model, int rev)
{
  int pin ;

  if(model == PI_MODEL_ODROIDC2)
	printf (" +------+-----+----------+------+ Model  ODROID-C2 +------+----------+-----+------+\n") ;
  else
	printf (" +------+-----+----------+------+- Model ODROID-C -+------+----------+-----+------+\n") ;

  printf (" | GPIO | wPi |   Name   | Mode | V | Physical | V | Mode |   Name   | wPi | GPIO |\n") ;
  printf (" +------+-----+----------+------+---+----++----+---+------+----------+-----+------+\n") ;
  for (pin = 1 ; pin <= 40 ; pin += 2)
    readallPhysOdroidC (pin, model, rev) ;
  printf (" +------+-----+----------+------+---+----++----+---+------+----------+-----+------+\n") ;
}

static void readallPhysOdroidXU (int physPin)
{
  int pin ;

  if     ((physPinToGpio (physPin) == -1) && (physToWpi [physPin] == -1))
    printf (" |      |    ") ;
  else if (physPinToGpio (physPin) != -1)
    printf (" |  %3d | %3d", physPinToGpio (physPin), physToWpi [physPin]);
  else
    printf (" |      | %3d", physToWpi [physPin]);

  printf (" | %s", physNamesOdroidXU [physPin]) ;

  if ((physToWpi [physPin] == -1) || (physPinToGpio (physPin) == -1))
    printf (" |      |  ") ;
  else
  {
    /**/ if (wpMode == WPI_MODE_GPIO)
      pin = physPinToGpio (physPin) ;
    else if (wpMode == WPI_MODE_PHYS)
      pin = physPin ;
    else
      pin = physToWpi [physPin] ;

    printf (" | %4s", alts [getAlt (pin)]) ;
    printf (" | %d", digitalRead (pin)) ;
  }

// Pin numbers:

  printf (" | %2d", physPin) ;
  ++physPin ;
  printf (" || %-2d", physPin) ;

// Same, reversed

  if ((physToWpi [physPin] == -1) || (physPinToGpio (physPin) == -1))
    printf (" |   |     ") ;
  else
  {
    /**/ if (wpMode == WPI_MODE_GPIO)
      pin = physPinToGpio (physPin) ;
    else if (wpMode == WPI_MODE_PHYS)
      pin = physPin ;
    else
      pin = physToWpi [physPin] ;

    printf (" | %d", digitalRead (pin)) ;
    printf (" | %-4s", alts [getAlt (pin)]) ;
  }

  printf (" | %-6s", physNamesOdroidXU [physPin]) ;

  if     ((physPinToGpio (physPin) == -1) && (physToWpi [physPin] == -1))
    printf (" |     |     ") ;
  else if (physPinToGpio (physPin) != -1)
    printf (" | %-3d |  %-3d", physToWpi [physPin], physPinToGpio (physPin));
  else
    printf (" | %-3d |     ", physToWpi [physPin]);

  printf (" |\n") ;
}

void ReadallOdroidXU (void)
{
  int pin ;

  printf (" +------+-----+----------+------ Model ODROID-XU3/4 ------+----------+-----+------+\n") ;
  printf (" | GPIO | wPi |   Name   | Mode | V | Physical | V | Mode |   Name   | wPi | GPIO |\n") ;
  printf (" +------+-----+----------+------+---+----++----+---+------+----------+-----+------+\n") ;
  for (pin = 1 ; pin <= 40 ; pin += 2)
    readallPhysOdroidXU (pin) ;
  printf (" +------+-----+----------+------+---+----++----+---+------+----------+-----+------+\n") ;
}

/*
 * doReadall:
 *	Generic read all pins called from main program. Works out the Pi type
 *	and calls the appropriate function.
 *********************************************************************************
 */

void doReadall (void)
{
  int model, rev, mem, maker, overVolted ;

  if (wiringPiNodes != NULL)	// External readall
  {
    doReadallExternal () ;
    return ;
  }

  piBoardId (&model, &rev, &mem, &maker, &overVolted) ;

  /**/ if ((model == PI_MODEL_A) || (model == PI_MODEL_B))
    abReadall (model, rev) ;
  else if ((model == PI_MODEL_BP) || (model == PI_MODEL_AP) || (model == PI_MODEL_2) || (model == PI_MODEL_3) || (model == PI_MODEL_ZERO) || (model == PI_MODEL_ZERO_W))
    piPlusReadall (model) ;
  else if (model == PI_MODEL_ODROIDC || model == PI_MODEL_ODROIDC2)
    ReadallOdroidC (model, rev);
  else if (model == PI_MODEL_ODROIDXU_34)
    ReadallOdroidXU();
  else if ((model == PI_MODEL_CM) || (model == PI_MODEL_CM3))
    allReadall () ;
  else
    printf ("Oops - unable to determine board type... model: %d\n", model) ;
}

/*
 * doAllReadall:
 *	Force reading of all pins regardless of Pi model
 *********************************************************************************
 */

void doAllReadall (void)
{
  allReadall () ;
}

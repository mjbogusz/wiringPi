/*
 * blink_all_c2.c:
 *  "Blink all" program for Odroid C2. Blinks LEDs on all GPIO pins
 *  (ones without specific function) in sequence.
 *
 * Copyright (c) 2017 MJBogusz
 ***********************************************************************
 * This file is part of wiringPi fork by mjbogusz:
 *  https://github.com/mjbogusz/wiringPi
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
#include <wiringPi.h>

// Uncomment for GPIO mode (/sys/class/gpio/gpioXXX numbering)
//#define GPIO_MODE

int main() {
  printf("Odroid C2 blink all\n");

  #ifndef GPIO_MODE
    wiringPiSetup();
    int pins[19] = {
      00, 01, 02, 03, 04,
      05, 06, 07, 10, 11,
      12, 13, 14, 21, 22,
      23, 24, 26, 27
    };
  #else
    // GPIO mode
    wiringPiSetupGpio();
    int pins[19] = {
      247, 238, 239, 237, 236,
      233, 231, 249, 229, 225,
      235, 232, 230, 228, 219,
      234, 214, 224, 218,
    };
  #endif

  for (int i = 0; i < 19; ++i) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }

  while(1) {
    for (int i = 0; i < 19; ++i) {
      digitalWrite(pins[(i+1) % 19], HIGH);
      digitalWrite(pins[i], LOW);
      delay(500);
    }
  }

  return 0;
}

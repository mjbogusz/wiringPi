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

int main() {
  printf("Odroid C2 blink all\n");

  wiringPiSetupGpio();
  int pins[18] = {00, 01, 02, 03, 04,
                  05, 12, 13, 06, 14,
                  10, 11, 21, 22, 26,
                  23, 24, 27};

  for (int i = 0; i < 18; ++i) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }

  while(1) {
    for (int i = 0; i < 18; ++i) {
      digitalWrite(pins[(i+1) % 18], HIGH);
      digitalWrite(pins[i], LOW);
      delay(500);
    }
  }

  return 0;
}

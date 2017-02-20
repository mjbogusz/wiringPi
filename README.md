# WiringPi library
...with Odroid boards support (C2 in particular) and CMake build system

## Yet another identical fork?
Yes and no. Mostly no.

This one combines:
* mainline WiringPi code (from Drogon's official repo, not from github)
* Odroid boards support (merged from Hardkernel's fork and believe me, it was a PITA)
* CMake build system (instead of awful hard-typed Makefiles)

## Building
```
cd build
cmake ..
make
```

_todo: elaborate_

## Installation
_todo (missing cmake rules)_

_for now, use regular `Makefile` or `build.sh`, manually copy compiled files to their destinations ( `*.so*` to `/usr/local/lib` and `*.h` to `/usr/local/include`) or just use this library in an userspace manner._

## API, examples...
See [official webpage](http://wiringpi.com/)

## Pin mappings
* [Odroid C1](http://odroid.com/dokuwiki/doku.php?id=en:c1_hardware#expansion_connectors) ('Description' column)
* [Odroid C2](http://odroid.com/dokuwiki/doku.php?id=en:c2_hardware#expansion_connectors) ('Description' column)
* [Odroid XU3 & XU4](http://odroid.com/dokuwiki/doku.php?id=en:xu3_hardware_gpio#gpio_map_for_wiringpi_library_con10_2_x_15) ('WiringPI GPIO' column)

---
Original readme follows.
---

wiringPi README
===============

Please note that the official way to get wiringPi is via git from
git.drogon.net and not GitHub.

ie.

  git clone git://git.drogon.net/wiringPi

The version of wiringPi held on GitHub by "Gadgetoid" is used to build the
wiringPython, Ruby, Perl, etc. wrappers for these other languages. This
version may lag the official Drogon release.  Pull requests may not be
accepted to Github....

Please see

  http://wiringpi.com/

for the official documentation, etc. and the best way to submit bug reports, etc.
is by sending an email to projects@drogon.net

Thanks!

  -Gordon

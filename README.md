# WiringPi library
...with Odroid boards support (C2 in particular) and CMake build system

## Yet another identical fork?
Yes and no. Mostly no.

This one combines:
* mainline WiringPi code (from Drogon's official repo, not from github)
* Odroid boards support (merged from Hardkernel's fork and believe me, it was a PITA)
* CMake build system (instead of awful hard-typed Makefiles)

## Compiling
```sh
cd build
cmake ..
make
```

## Examples
Examples are in 'examples' directory.
Most of them are from original (i.e. non-fork) version of the library.

### Building
```sh
cd build
cmake ..
make examples
```

### Odroid specific examples
Currently there is 1 example program made specifically for Odroid C2. It _should_ blink LEDs connected to all GPIO pins in order of WiringPi mapping (see [Pin mappings](#pin-mappings) or source code).
You can build and run it with:
```sh
cd build
cmake ..
make examples_odroid
./examples/Odroid/blink_all_c2
```

## Installation
Note: original WiringPi spams `/usr/include` with headers (about 30-40 of them). This fork installs them into `/usr/include/wiringPi` (but main `wiringPi.h` will be installed into `/usr/include` too for convenience)

### Manual (not recommended)
```sh
cd build
cmake ..
make
sudo make install
```

### Automatic (via package manager)
#### Dpkg (Debian, Ubuntu and derivatives)
```sh
cd build
cmake ..
make
cpack -G DEB
sudo dpkg -i wiringpi-odroid-*.deb
```

#### Pacman (Archlinux)
_TODO_

## API, examples...
See [official webpage](http://wiringpi.com/)

## Pin mappings
* [Odroid C1](http://odroid.com/dokuwiki/doku.php?id=en:c1_hardware#expansion_connectors) ('Description' column)
* [Odroid C2](http://odroid.com/dokuwiki/doku.php?id=en:c2_hardware#expansion_connectors) ('Description' column)
* [Odroid XU3 & XU4](http://odroid.com/dokuwiki/doku.php?id=en:xu3_hardware_gpio#gpio_map_for_wiringpi_library_con10_2_x_15) ('WiringPI GPIO' column)

---
Original readme below
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

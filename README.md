# GLStats

GLStats is a generic OpenGL overlay statistics renderer used by the
Equalizer parallel rendering framework.

## Building from Source

GLStats is a cross-platform library, designed to run on any modern
operating system, including all Unix variants and the Windows operating
system. Zeroconf support in Lunchbox is required for the DNS_SD module
and applications. The following platforms and build environments are
tested:

* Linux: Ubuntu 16.04, RHEL 6.8 (Makefile, Ninja)
* Windows: 7 (Visual Studio 2012)
* Mac OS X: 10.9 (Makefile, Ninja)

Building from source is as simple as:

    git clone https://github.com/Eyescale/GLStats.git
    mkdir GLStats/build
    cd GLStats/build
    cmake -GNinja ..
    ninja

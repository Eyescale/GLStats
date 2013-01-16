
# Copyright (c) 2012-2013 Stefan Eilemann <eile@eyescale.ch>

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(GLStats)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

set(RELEASE_VERSION OFF) # OFF or 'Mm0' ABI version
set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")

include(Common)
include(UpdateFile)

set(FIND_PACKAGES_DEFINES GLSTATS_STATIC)
include(FindPackages)
set(GLSTATS_TRANSIENT_LIBRARIES Lunchbox)

add_subdirectory(GLStats)
#add_subdirectory(tests)

include(DoxygenRule) # must be after all targets

#install(FILES CMake/FindGLStats.cmake DESTINATION ${CMAKE_MODULE_INSTALL_PATH}
#  COMPONENT dev)

#include(CPackConfig)
include(CTest)

include(PackageConfig)

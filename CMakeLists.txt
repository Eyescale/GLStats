
# Copyright (c) 2012-2013 Stefan Eilemann <eile@eyescale.ch>

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(GLStats)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

set(RELEASE_VERSION 100) # OFF or 'Mm0' ABI version
set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")

include(Common)
include(GitTargets)
include(UpdateFile)

set(FIND_PACKAGES_DEFINES GLSTATS_STATIC)
include(FindPackages)
set(GLSTATS_DEPENDENT_LIBRARIES Lunchbox)

add_subdirectory(GLStats)
#add_subdirectory(tests)

include(DoxygenRule) # must be after all targets
include(CPackConfig)
include(GNUModules)
include(CTest)

include(PackageConfig)

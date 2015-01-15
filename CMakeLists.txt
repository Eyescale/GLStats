
# Copyright (c) 2012-2015 Stefan Eilemann <eile@eyescale.ch>

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(GLStats)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
  ${PROJECT_SOURCE_DIR}/CMake/common)
include(GitExternal)
include(SubProject)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "3")
set(VERSION_PATCH "1")
set(VERSION_ABI 1)

set(DPUT_HOST "ppa:bbp/ppa") # Target ppa used by 'make dput'

set(PROJECT_INCLUDE_NAME "GLStats")

include(Common)

set(FIND_PACKAGES_DEFINES GLSTATS_STATIC)
include(FindPackages)
set(GLSTATS_DEPENDENT_LIBRARIES Lunchbox)

add_subdirectory(GLStats)
#add_subdirectory(tests)

include(CPackConfig)
include(DoxygenRule) # must be after all targets


# Copyright (c) 2012-2015 Stefan Eilemann <eile@eyescale.ch>

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(GLStats)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)
include(GitExternal)
include(SubProject)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "3")
set(VERSION_PATCH "2")
set(VERSION_ABI 1)

set(COMMON_PROJECT_DOMAIN ch.eyescale)
set(DPUT_HOST "ppa:bbp/ppa") # Target ppa used by 'make dput'
set(GLSTATS_INCLUDE_NAME GLStats)

include(Common)

set(DPUT_HOST "ppa:bbp/ppa") # Target ppa used by 'make dput'
set(COMMON_PACKAGE_DEFINES GLSTATS_STATIC)

common_package(Lunchbox REQUIRED)
common_package(OpenGL REQUIRED)
common_package_post()

set(GLSTATS_DEPENDENT_LIBRARIES Lunchbox)

add_subdirectory(GLStats)
#add_subdirectory(tests)

set(DOXYGEN_MAINPAGE_MD ${PROJECT_SOURCE_DIR}/README.md)
set(DOXYGEN_EXTRA_INPUT ${DOXYGEN_MAINPAGE_MD})
include(CPackConfig)
include(DoxygenRule) # must be after all targets

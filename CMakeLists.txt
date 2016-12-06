
# Copyright (c) 2012-2016 Stefan Eilemann <eile@eyescale.ch>

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(GLStats VERSION 0.3.3)
set(GLStats_VERSION_ABI 1)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)
include(GitExternal)

set(DPUT_HOST "ppa:bbp/ppa") # Target ppa used by 'make dput'
set(GLSTATS_INCLUDE_NAME GLStats)
set(GLSTATS_DEB_DEPENDS libx11-dev libgl1-mesa-dev)
set(GLSTATS_LICENSE LGPL)
set(COMMON_PROJECT_DOMAIN ch.eyescale)

include(Common)

set(COMMON_FIND_PACKAGE_DEFINES GLSTATS_STATIC)

common_find_package(Lunchbox REQUIRED)
common_find_package(OpenGL REQUIRED)
common_find_package_post()

set(GLSTATS_DEPENDENT_LIBRARIES Lunchbox)

add_subdirectory(GLStats)
add_subdirectory(tests)

set(DOXYGEN_MAINPAGE_MD ${PROJECT_SOURCE_DIR}/README.md)
set(DOXYGEN_EXTRA_INPUT ${DOXYGEN_MAINPAGE_MD})
include(CPackConfig)
include(DoxygenRule)

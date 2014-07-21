
# Copyright (c) 2012-2014 Stefan Eilemann <eile@eyescale.ch>

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(GLStats)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)
include(GitExternal)

include(Buildyard)
if(BUILDYARD_STOP)
  return()
endif()

set(LAST_RELEASE 0.3.0)
set(VERSION_MAJOR "0")
set(VERSION_MINOR "3")
set(VERSION_PATCH "0")
set(VERSION_ABI 101)

# Tell 'make branch' to name the new branch "VERSION_MAJOR.VERSION_MINOR"
set(GITTARGETS_RELEASE_BRANCH "minor")
set(DPUT_HOST "ppa:bbp/ppa") # Target ppa used by 'make dput'

set(PROJECT_INCLUDE_NAME "GLStats")

include(Common)
include(GitTargets)
include(UpdateFile)

set(FIND_PACKAGES_DEFINES GLSTATS_STATIC)
include(FindPackages)
set(GLSTATS_DEPENDENT_LIBRARIES Lunchbox)

add_subdirectory(GLStats)

add_subdirectory(tests)

include(DoxygenRule) # must be after all targets
include(CPackConfig)
include(GNUModules)
include(CTest)

include(PackageConfig)

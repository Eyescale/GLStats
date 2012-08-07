
# Copyright (c) 2012 Stefan Eilemann <eile@eyescale.ch>

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(GLStats)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

set(RELEASE_VERSION OFF) # OFF or 'Mm0' ABI version
set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

set(GLSTATS_OSX_VERSION 10.6)
if(RELEASE_VERSION)
  set(GLSTATS_DEFINITIONS -DGLSTATS_RELEASE)
  set(CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX${GLSTATS_OSX_VERSION}.sdk
      CACHE PATH "" FORCE)
  set(VERSION_ABI ${RELEASE_VERSION})
else()
#  set(VERSION_ABI ${VERSION_MAJOR}${VERSION_MINOR}${VERSION_PATCH})
  set(VERSION_ABI ${VERSION_MINOR}${VERSION_PATCH})
endif()

include(Common)
include(DoxygenSetup)
include(UpdateFile)
include(InstallSymlink)
include(FindPackages)

link_directories(${LUNCHBOX_LIBRARY_DIRS})
include_directories(${LUNCHBOX_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})

add_subdirectory(GLStats)
#add_subdirectory(tests)

include(DoxygenRule) # must be after all targets

#install(FILES CMake/FindGLStats.cmake DESTINATION ${CMAKE_MODULE_INSTALL_PATH}
#  COMPONENT dev)

#include(CPackConfig)
include(CTest)

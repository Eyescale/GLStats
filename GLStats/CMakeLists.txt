
# Copyright (c) 2012-2013 Stefan Eilemann <eile@eyescale.ch>

include(files.cmake)

list(APPEND GLSTATS_LINK_LIBRARIES PUBLIC Lunchbox)

set(GLSTATS_LIBRARY_TYPE STATIC)
common_library(GLStats)



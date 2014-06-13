
# Copyright (c) 2012-2013 Stefan Eilemann <eile@eyescale.ch>

set(GLSTATS_PUBLIC_HEADERS
  ${COMMON_INCLUDES} 
  data.h
  entity.h
  item.h
  renderer.h
  thread.h
  type.h
  types.h
  )

set(GLSTATS_SOURCES
  ${COMMON_SOURCES}
  data.cpp
  renderer.cpp
  )

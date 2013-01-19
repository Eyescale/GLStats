
# Copyright (c) 2012-2013 Stefan Eilemann <eile@eyescale.ch>

update_file(${CMAKE_CURRENT_SOURCE_DIR}/version.in.h
  ${OUTPUT_INCLUDE_DIR}/GLStats/version.h)


set(GLSTATS_PUBLIC_HEADERS
  ${OUTPUT_INCLUDE_DIR}/GLStats/version.h
  ${DEFINES_FILE}
  api.h
  data.h
  defines.h
  entity.h
  item.h
  renderer.h
  thread.h
  type.h
  types.h
  GLStats.h
  )

set(GLSTATS_SOURCES
  data.cpp
  renderer.cpp
  version.cpp
  )

set(GLSTATS_ALL ${GLSTATS_PUBLIC_HEADERS} ${GLSTATS_SOURCES})

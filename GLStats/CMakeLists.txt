
# Copyright (c) 2012 Stefan Eilemann <eile@eyescale.ch>

include(files.cmake)
source_group(\\ FILES CMakeLists.txt)
source_group(GLStats FILES ${GLSTATS_PUBLIC_HEADERS} ${GLSTATS_HEADERS}
  ${GLSTATS_SOURCES})

set(LIBRARY GLStats)
set(LIB_INCLUDE ${LIBRARY})

add_library(${LIBRARY} STATIC ${GLSTATS_ALL})
target_link_libraries(${LIBRARY} ${GLSTATS_LINKLIB})
set_target_properties(${LIBRARY}
  PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION_ABI}
  COMPILE_DEFINITIONS GLSTATS_SHARED
)

install(FILES ${GLSTATS_PUBLIC_HEADERS}
        DESTINATION include/${LIB_INCLUDE} COMPONENT dev)
install(TARGETS ${LIBRARY}
        ARCHIVE DESTINATION lib COMPONENT dev
        RUNTIME DESTINATION bin COMPONENT lib
        LIBRARY DESTINATION lib COMPONENT lib)

#configure_file(GLStats.in.pc ${CMAKE_CURRENT_BINARY_DIR}/GLStats.pc @ONLY)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/GLStats.pc
#        DESTINATION ${LIBRARY_DIR}/pkgconfig COMPONENT lib)

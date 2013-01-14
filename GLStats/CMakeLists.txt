
# Copyright (c) 2012-2013 Stefan Eilemann <eile@eyescale.ch>

include(files.cmake)
source_group(\\ FILES CMakeLists.txt)
source_group(GLStats FILES ${GLSTATS_PUBLIC_HEADERS} ${GLSTATS_HEADERS}
  ${GLSTATS_SOURCES})

add_library(GLStats STATIC ${GLSTATS_ALL})
target_link_libraries(GLStats ${GLSTATS_LINKLIB})
set_target_properties(GLStats
  PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION_ABI} COMPILE_DEFINITIONS GLSTATS_STATIC)

install(FILES ${GLSTATS_PUBLIC_HEADERS}
        DESTINATION include/GLStats COMPONENT dev)
install(TARGETS GLStats
        ARCHIVE DESTINATION lib COMPONENT dev
        RUNTIME DESTINATION bin COMPONENT lib
        LIBRARY DESTINATION lib COMPONENT lib)

#configure_file(GLStats.in.pc ${CMAKE_CURRENT_BINARY_DIR}/GLStats.pc @ONLY)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/GLStats.pc
#        DESTINATION ${LIBRARY_DIR}/pkgconfig COMPONENT lib)

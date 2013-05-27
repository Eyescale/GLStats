# Copyright (c) 2012-2013 Stefan Eilemann <eile@eyescale.ch>
# Info: http://www.itk.org/Wiki/CMake:Component_Install_With_CPack

set(CPACK_PACKAGE_VENDOR "www.eyescale.ch")
set(CPACK_PACKAGE_CONTACT "Stefan Eilemann <eile@eyescale.ch>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OpenGL overlay statistics renderer")
#set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/doc/RelNotes.md)
#set(CPACK_RESOURCE_FILE_README ${CMAKE_SOURCE_DIR}/doc/RelNotes.md)

set(CPACK_DEBIAN_BUILD_DEPENDS
  ${GLSTATS_BUILD_DEBS} ${LUNCHBOX_DEB_DEV_DEPENDENCY})
set(CPACK_DEBIAN_PACKAGE_DEPENDS
  "libstdc++6, libgl1-mesa-glx, ${LUNCHBOX_DEB_DEV_DEPENDENCY}")

set(CPACK_MACPORTS_CATEGORY devel)
set(CPACK_MACPORTS_DEPENDS boost Lunchbox)

include(CommonCPack)

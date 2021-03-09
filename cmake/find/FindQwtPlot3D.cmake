# Find QwtPlot3D
# ~~~~~~~~~~~~~
# Once run this will define:
#
# QWTPLOT3D_FOUND       = system has QwtPlot3D lib
# QWTPLOT3D_LIBRARY     = full path to the QwtPlot3D library
# QWTPLOT3D_INCLUDE_DIR = where to find headers
#


set(QWTPLOT3D_LIBRARY_NAMES qwtplot3d-qt5)

find_library(QWTPLOT3D_LIBRARY
  NAMES ${QWTPLOT3D_LIBRARY_NAMES}
  PATHS
    /usr/lib
    /usr/local/lib
    /usr/local/lib/qt5
    "$ENV{LIB_DIR}/lib"
    "$ENV{LIB}"
)

set(_qwt_fw)
if(QWTPLOT3D_LIBRARY MATCHES "/qwt.*\\.framework")
  string(REGEX REPLACE "^(.*/qwt.*\\.framework).*$" "\\1" _qwt_fw "${QWTPLOT3D_LIBRARY}")
endif()

FIND_PATH(QWTPLOT3D_INCLUDE_DIR NAMES qwt3d_plot.h PATHS
  "${_qwt_fw}/Headers"
  /usr/include
  /usr/include/qt5
  /usr/local/include
  /usr/local/include/qt5
  "$ENV{LIB_DIR}/include"
  "$ENV{INCLUDE}"
  PATH_SUFFIXES qwtplot3d
)

IF (QWTPLOT3D_INCLUDE_DIR AND QWTPLOT3D_LIBRARY)
  SET(QWTPLOT3D_FOUND TRUE)
ENDIF (QWTPLOT3D_INCLUDE_DIR AND QWTPLOT3D_LIBRARY)

IF (QWTPLOT3D_FOUND)
  FILE(READ ${QWTPLOT3D_INCLUDE_DIR}/qwt3d_global.h qwt_header)
  STRING(REGEX REPLACE "^.*QWT3D_MAJOR_VERSION +([0-9]+).*$" "\\1" QWT3D_MAJOR_VERSION "${qwt_header}")
  STRING(REGEX REPLACE "^.*QWT3D_MINOR_VERSION +([0-9]+).*$" "\\1" QWT3D_MINOR_VERSION "${qwt_header}")
  STRING(REGEX REPLACE "^.*QWT3D_PATCH_VERSION +([0-9]+).*$" "\\1" QWT3D_PATCH_VERSION "${qwt_header}")
  IF (NOT QWTPLOT3D_FIND_QUIETLY)
    MESSAGE(STATUS "Found QwtPlot3D: ${QWTPLOT3D_LIBRARY} (${QWT3D_MAJOR_VERSION}.${QWT3D_MINOR_VERSION}.${QWT3D_PATCH_VERSION})")
  ENDIF (NOT QWTPLOT3D_FIND_QUIETLY)
ELSE (QWTPLOT3D_FOUND)
  IF (QWTPLOT3D_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find QwtPlot3D")
  ENDIF (QWTPLOT3D_FIND_REQUIRED)
ENDIF (QWTPLOT3D_FOUND)

# Find QwtPolar
# ~~~~~~~~~~~~~
# Once run this will define:
#
# QWTPOLAR_FOUND       = system has QWTPOLAR lib
# QWTPOLAR_LIBRARY     = full path to the QWTPOLAR library
# QWTPOLAR_INCLUDE_DIR = where to find headers
#


set(QWTPOLAR_LIBRARY_NAMES qwtpolar)

find_library(QWTPOLAR_LIBRARY
  NAMES ${QWTPOLAR_LIBRARY_NAMES}
  PATHS
    /usr/lib
    /usr/local/lib
    /usr/local/lib/qt5
    "$ENV{LIB_DIR}/lib"
    "$ENV{LIB}"
)

set(_qwt_fw)
if(QWTPOLAR_LIBRARY MATCHES "/qwt.*\\.framework")
  string(REGEX REPLACE "^(.*/qwt.*\\.framework).*$" "\\1" _qwt_fw "${QWTPOLAR_LIBRARY}")
endif()

FIND_PATH(QWTPOLAR_INCLUDE_DIR NAMES qwt_polar.h PATHS
  "${_qwt_fw}/Headers"
  /usr/include
  /usr/include/qt5
  /usr/local/include
  /usr/local/include/qt5
  "$ENV{LIB_DIR}/include"
  "$ENV{INCLUDE}"
  PATH_SUFFIXES qwt-qt5 qwt qwt6
)

IF (QWTPOLAR_INCLUDE_DIR AND QWTPOLAR_LIBRARY)
  SET(QWTPOLAR_FOUND TRUE)
ENDIF (QWTPOLAR_INCLUDE_DIR AND QWTPOLAR_LIBRARY)

IF (QWTPOLAR_FOUND)
  FILE(READ ${QWTPOLAR_INCLUDE_DIR}/qwt_polar_global.h qwt_header)
  STRING(REGEX REPLACE "^.*QWT_POLAR_VERSION_STR +\"([^\"]+)\".*$" "\\1" QWT_POLAR_VERSION_STR "${qwt_header}")
  IF (NOT QWTPOLAR_FIND_QUIETLY)
    MESSAGE(STATUS "Found QwtPolar: ${QWTPOLAR_LIBRARY} (${QWT_POLAR_VERSION_STR})")
  ENDIF (NOT QWTPOLAR_FIND_QUIETLY)
ELSE (QWTPOLAR_FOUND)
  IF (QWTPOLAR_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find QwtPolar")
  ENDIF (QWTPOLAR_FIND_REQUIRED)
ENDIF (QWTPOLAR_FOUND)

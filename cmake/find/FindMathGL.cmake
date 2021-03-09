set(MATHGP_PREFIX "" CACHE PATH "The path to the previx of an MathGL installation")

find_path(MATHGL_INCLUDE_DIR NAMES mgl2/mgl.h
  PATHS
  ${MPFR_PREFIX}/include
  /opt/local/include
  /usr/include
  /usr/local/include
  )

find_library(MATHGL_LIBRARIES NAMES mgl mgl
  PATHS
  ${MPFR_PREFIX}/lib
  /opt/local/include
  /usr/include
  /usr/local/include
  )

find_library(MATHGL_QT5_LIBRARIES NAMES mgl-qt5
  PATHS
  ${MPFR_PREFIX}/lib
  /opt/local/include
  /usr/include
  /usr/local/include
  )

if(MATHGL_INCLUDE_DIR AND MATHGL_LIBRARIES)
  get_filename_component(MATHGL_LIBRARY_DIR ${MATHGL_LIBRARIES} PATH)
  set(MATHGL_FOUND TRUE)
endif()

if(MATHGL_FOUND)
  if(NOT MATHGL_FIND_QUIETLY)
    MESSAGE(STATUS "Found MathGL: ${MATHGL_LIBRARIES}")
  endif()
  set(HAVE_MATHGL 1)
elseif(MATHGL_FOUND)
  if(MATHGL_FIND_REQUIRED)
    message(FATAL_ERROR "Could not find MATHGL")
  endif()
endif()

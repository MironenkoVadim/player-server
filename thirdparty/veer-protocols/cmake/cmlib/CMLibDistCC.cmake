find_program(DISTCC_EXECUTABLE distcc)
mark_as_advanced(DISTCC_EXECUTABLE)
if(DISTCC_EXECUTABLE)
  foreach(LANG C CXX)
    if(NOT DEFINED CMAKE_${LANG}_COMPILER_LAUNCHER AND NOT CMAKE_${LANG}_COMPILER MATCHES ".*/distcc$")
      message(STATUS "Enabling distcc for ${LANG}")
      set(CMAKE_${LANG}_COMPILER_LAUNCHER ${DISTCC_EXECUTABLE} CACHE STRING "")
    endif()
  endforeach()
endif()

if(CMAKE_CROSSCOMPILING)
  return()
endif()

if(LSB_RELEASE)
  return()
endif()

set(LSB_DISTRIBUTOR_ID "unknown")
set(LSB_CODENAME "unknown")
set(LSB_RELEASE "unknown")

if(EXISTS /etc/mcst_version)
  set(LSB_DISTRIBUTOR_ID "ElbrusD")
  set(LSB_CODENAME "Jessie")
  execute_process(COMMAND cat /etc/mcst_version OUTPUT_VARIABLE LSB_RELEASE OUTPUT_STRIP_TRAILING_WHITESPACE)
else()
  find_program(_lsb_release_executable lsb_release)
  if(_lsb_release_executable)
    execute_process(COMMAND ${_lsb_release_executable} -si OUTPUT_VARIABLE LSB_DISTRIBUTOR_ID
                                                                           OUTPUT_STRIP_TRAILING_WHITESPACE)

    execute_process(COMMAND ${_lsb_release_executable} -sc OUTPUT_VARIABLE LSB_CODENAME
                                                                           OUTPUT_STRIP_TRAILING_WHITESPACE)

    execute_process(COMMAND ${_lsb_release_executable} -sr OUTPUT_VARIABLE LSB_RELEASE
                                                                           OUTPUT_STRIP_TRAILING_WHITESPACE)
  endif()
endif()

find_program(CLANG_CHECK_EXE NAMES clang-check-10 clang-check-9 clang-check)
if(CLANG_CHECK_EXE)
  option(CMLIB_CLANG_ANALYZE_FIX "Perform fixes for Clang-Check" OFF)
endif()

function(add_clang_analyze_check target)
  set(_sources ${ARGN})
  set(_args -analyze -extra-arg="-Wno-unknown-warning-option")

  if(CLANG_CHECK_EXE)
    if(CMLIB_CLANG_ANALYZE_FIX)
      list(APPEND _args "--fixit")
    endif()
    if(NOT TARGET clang-analyze-check)
      add_custom_target(clang-analyze-check)
    endif()
    add_custom_target(clang-analyze-check-${target} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                      COMMAND ${CLANG_CHECK_EXE} ${_args} -p ${CMAKE_BINARY_DIR} ${_sources})
    add_dependencies(clang-analyze-check-${target} ${target})
    add_dependencies(clang-analyze-check clang-analyze-check-${target})
  else()
    message(STATUS "CMLIB warning:")
    message(STATUS "  Clang-Check analyzer is not found")
  endif()
endfunction()

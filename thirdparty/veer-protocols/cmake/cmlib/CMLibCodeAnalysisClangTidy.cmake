find_program(
  CLANG_TIDY_EXE
  NAMES
    clang-tidy-13
    clang-tidy-12
    clang-tidy-11
    clang-tidy-10
    clang-tidy-9
    clang-tidy)
if(CLANG_TIDY_EXE)
  option(CMLIB_CLANG_TIDY_FIX "Perform fixes for Clang-Tidy" OFF)
endif()

function(add_clang_tidy_check target)
  set(_sources ${ARGN})
  set(_args -extra-arg="-Wno-unknown-warning-option")

  if(CLANG_TIDY_EXE)
    if(CMLIB_CLANG_TIDY_FIX)
      list(APPEND _args "--fix")
    endif()
    if(NOT TARGET clang-tidy-check)
      add_custom_target(clang-tidy-check)
    endif()
    add_custom_target(clang-tidy-check-${target} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                      COMMAND ${CLANG_TIDY_EXE} ${_args} -p ${CMAKE_BINARY_DIR} ${_sources})
    add_dependencies(clang-tidy-check-${target} ${target})
    add_dependencies(clang-tidy-check clang-tidy-check-${target})
  else()
    message(STATUS "CMLIB warning:")
    message(STATUS "  ClangTidy analyzer is not found")
  endif()
endfunction()

find_program(CLANG_APPLY_REPLACEMENTS_EXE NAMES clang-apply-replacements-10 clang-apply-replacements-9
                                                clang-apply-replacements)

find_program(CLAZY_EXE NAMES clazy-standalone)

if(CLAZY_EXE AND CLANG_APPLY_REPLACEMENTS_EXE)
  option(CMLIB_CLAZY_FIX "Perform fixes for Clazy" OFF)
endif()

function(add_clazy_check target)
  set(options)
  set(oneValueArgs CHECKS)
  set(multiValueArgs)

  cmake_parse_arguments(_CLAZY "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  set(_sources ${_CLAZY_UNPARSED_ARGUMENTS})
  if(NOT _CLAZY_CHECKS)
    set(_CLAZY_CHECKS
        "level2,container-inside-loop,heap-allocated-small-trivial-type,inefficient-qlist,isempty-vs-count,qt-keywords,unneeded-cast"
    )
  endif()
  set(_args -checks=${_CLAZY_CHECKS} -extra-arg="-Wno-unknown-warning-option"
            -export-fixes=clazy-fixes-file.yaml)

  if(CLAZY_EXE)
    if(NOT TARGET clazy-check)
      add_custom_target(clazy-check)
    endif()
    if(CMLIB_CLAZY_FIX)
      add_custom_target(
        clazy-check-${target}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${CLAZY_EXE} ${_args} -p ${CMAKE_BINARY_DIR} ${_sources}
        COMMAND ${CLANG_APPLY_REPLACEMENTS_EXE} ${CMAKE_BINARY_DIR})
    else()
      add_custom_target(clazy-check-${target} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        COMMAND ${CLAZY_EXE} ${_args} -p ${CMAKE_BINARY_DIR} ${_sources})
    endif()
    add_dependencies(clazy-check-${target} ${target})
    add_dependencies(clazy-check clazy-check-${target})
  else()
    message(STATUS "CMLIB warning:")
    message(STATUS "  Clazy standalone analyzer is not found")
  endif()
endfunction()

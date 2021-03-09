option(CMLIB_ENABLE_CODE_COVERAGE "Enable code coverage support" OFF)
find_program(LCOV_EXE NAMES lcov)
find_program(GENHTML_EXE NAMES genhtml)

function(add_code_coverage target)

  if(CMLIB_ENABLE_CODE_COVERAGE)
    if(CMAKE_CXX_COMPILER_IS_GCC)
      target_compile_options(${target} PUBLIC "--coverage")
      set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS " --coverage")

      if(LCOV_EXE)
        add_custom_target(
          coverage-${target} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
          COMMAND ${LCOV_EXE} --test-name ${target} --output "${target}.lcov" --capture --directory
                  ${CMAKE_BINARY_DIR})
        add_dependencies(coverage-${target} ${target})

        if(GENHTML_EXE)
          add_custom_target(coverage-report-${target} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                            COMMAND ${GENHTML_EXE} --output-directory "report-${target}" "${target}.lcov")
          add_dependencies(coverage-report-${target} coverage-${target})
        endif()
      endif()
    else()
      message("Only GCC is supported for code coverage")
    endif()
  endif()
endfunction()

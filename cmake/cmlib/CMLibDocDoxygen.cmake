set(DOXYGEN_FOUND AUTO CACHE STRING "Enable Doxygen documentation generator")
set_property(CACHE DOXYGEN_FOUND PROPERTY STRINGS ON OFF AUTO)

find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN_FOUND ON CACHE STRING "Doxygen documentation generator enabled" FORCE)
else()
  set(DOXYGEN_FOUND OFF CACHE STRING "Doxygen documentation generator disabled" FORCE)
endif()

function(add_doxygen target)
  set(options)
  set(oneValueArgs SQLITE LATEX HTML)
  set(multiValueArgs)

  cmake_parse_arguments(_DOXYGEN "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  if(DOXYGEN_FOUND)
    set(GENERATE_XML YES)
    set(GENERATE_HTML NO)
    set(GENERATE_LATEX NO)
    if(_DOXYGEN_HTML)
      set(GENERATE_HTML YES)
    endif()
    if(_DOXYGEN_LATEX)
      set(GENERATE_LATEX YES)
    endif()

    set(WORK_DIR ${CMAKE_BINARY_DIR}/doc/doxygen)
    configure_file(${CMAKE_SOURCE_DIR}/cmake/doc/Doxyfile.in ${WORK_DIR}/Doxyfile @ONLY)

    add_custom_target(
      ${target}
      VERBATIM
      COMMAND "${CMAKE_COMMAND}" -E remove -f "${WORK_DIR}/doxygen_sqlite3.db"
      COMMAND ${DOXYGEN_EXECUTABLE} ${WORK_DIR}/Doxyfile
      WORKING_DIRECTORY ${WORK_DIR}
      COMMENT "Generating API documentation with Doxygen")
  else()
    message(STATUS "CMLIB warning:")
    add_custom_target(${target} VERBATIM COMMENT "  Doxygen is not found. Skipping target ${target} build")
  endif()
endfunction()

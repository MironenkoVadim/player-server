set(BREATHE_FOUND AUTO CACHE STRING "Enable Breathe documentation generator")
set_property(CACHE BREATHE_FOUND PROPERTY STRINGS ON OFF AUTO)

find_package(Doxygen)
find_package(Perl)
set(Python_ADDITIONAL_VERSIONS 3.8;3.7;3.6;3.5;3.4;3.3;3.2)
find_package(PythonInterp)
if(PYTHONINTERP_FOUND)
  find_package(Sphinx)
  include(FindPythonModule)
  find_python_module(breathe)
  find_python_module(recommonmark)
  if(DOXYGEN_FOUND
     AND PERL_FOUND
     AND PYTHONINTERP_FOUND
     AND SPHINX_EXECUTABLE
     AND breathe
     AND recommonmark)
    set(BREATHE_FOUND ON CACHE STRING "Breathe documentation generator enabled" FORCE)
  else()
    set(BREATHE_FOUND OFF CACHE STRING "Breathe documentation generator disabled" FORCE)
  endif()
else()
  set(BREATHE_FOUND OFF CACHE STRING "Breathe documentation generator disabled" FORCE)
endif()

function(add_breathe target)
  set(options)
  set(oneValueArgs COMMENT)
  set(multiValueArgs)

  cmake_parse_arguments(_BREATHE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  if(BREATHE_FOUND)
    set(WORK_DIR ${CMAKE_BINARY_DIR}/_breathe)
    set(BREATHE_DOCS_BUILD_DIR ${WORK_DIR})
    set(GENERATE_XML YES)
    set(GENERATE_HTML NO)
    set(GENERATE_LATEX NO)
    set(CONF_FILE ${CMAKE_SOURCE_DIR}/cmake/doc/breathe-conf.py.in)
    set(DOXY_FILE ${CMAKE_SOURCE_DIR}/cmake/doc/Doxyfile.in)

    configure_file(${CONF_FILE} ${WORK_DIR}/conf.py @ONLY)
    configure_file(${DOXY_FILE} ${WORK_DIR}/Doxyfile @ONLY)

    add_custom_target(
      ${target}
      VERBATIM
      COMMAND ${SPHINX_EXECUTABLE} -q -b html -c ${WORK_DIR} -d ${WORK_DIR}/cache ${WORK_DIR}
              ${CMAKE_BINARY_DIR}/doc/breathe
      COMMENT "Building ${target} documentation with Breathe")

    set(INDEX_MD_FILE ${CMAKE_SOURCE_DIR}/doc/breathe/index.md.in)
    if(EXISTS ${INDEX_MD_FILE})
      configure_file(${INDEX_MD_FILE} ${WORK_DIR}/index.md @ONLY)
      file(GLOB MD_FILES ${CMAKE_SOURCE_DIR}/doc/breathe/*.md)
      if(MD_FILES)
        add_custom_command(TARGET ${target} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
                                                              ${MD_FILES} ${WORK_DIR})
      endif()
    endif()

    set(INDEX_RST_FILE ${CMAKE_SOURCE_DIR}/doc/breathe/index.rst.in)
    if(EXISTS ${INDEX_RST_FILE})
      configure_file(${INDEX_RST_FILE} ${WORK_DIR}/index.rst @ONLY)
      file(GLOB RST_FILES ${CMAKE_SOURCE_DIR}/doc/breathe/*.rst)
      if(RST_FILES)
        add_custom_command(TARGET ${target} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
                                                              ${RST_FILES} ${WORK_DIR})
      endif()
    endif()
  else()
    message(STATUS "CMLIB warning:")
    add_custom_target(${target} VERBATIM COMMENT "  Breathe is not found. Skipping target ${target} build")
  endif()
endfunction()

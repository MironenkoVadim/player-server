function(generate_pkgconfig library_name)
  set(options)
  set(oneValueArgs COMPONENT INSTALL_LIBRARY)
  set(multiValueArgs)

  cmake_parse_arguments(_PKG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if(${_PKG_INSTALL_LIBRARY})
    configure_file(${CMLIB_MODULE_DIR}/pc/lib.pc.in ${CMAKE_BINARY_DIR}/${library_name}.pc)
  else()
    configure_file(${CMLIB_MODULE_DIR}/pc/lib-header-only.pc.in ${CMAKE_BINARY_DIR}/${library_name}.pc)
  endif()
  install(FILES ${CMAKE_BINARY_DIR}/${library_name}.pc COMPONENT ${_PKG_COMPONENT}
          DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
endfunction()

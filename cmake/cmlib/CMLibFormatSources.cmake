function(add_format_sources target)
  set(_sources ${ARGN})

  if(NOT TARGET format-sources)
    add_custom_target(format-sources)
  endif()
  if(NOT TARGET doc-add-comments)
    add_custom_target(doc-add-comments)
  endif()

  find_program(UNCRUSTIFY_EXE NAMES uncrustify)
  if(UNCRUSTIFY_EXE)
    list(APPEND UNCRUSTIFY_OPTS --replace --no-backup)
    if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/etc/uncrustify/default.cfg)
      list(APPEND UNCRUSTIFY_OPTS -c ${CMAKE_SOURCE_DIR}/cmake/etc/uncrustify/default.cfg)
    endif()
    # cmake-format: off
    add_custom_target(format-sources-uncrustify-${target} COMMAND ${UNCRUSTIFY_EXE} ${UNCRUSTIFY_OPTS}
      --mtime ${_sources})
    add_custom_target(doc-add-comments-uncrustify-${target} COMMAND ${UNCRUSTIFY_EXE} ${UNCRUSTIFY_OPTS}
      --set cmt_insert_file_header=fileheader.txt
      --set cmt_insert_file_footer=filefooter.txt
      --set cmt_insert_func_header=funcheader.txt
      --set cmt_insert_class_header=classheader.txt
      --set cmt_insert_before_ctor_dtor=true ${_sources})
    # cmake-format: on
    add_dependencies(format-sources format-sources-uncrustify-${target})
    add_dependencies(doc-add-comments doc-add-comments-uncrustify-${target})
  else()
    message(STATUS "CMLIB warning:")
    message(STATUS "  uncrustify executable is not found")
  endif()

  find_program(DOS2UNIX_EXE NAMES dos2unix)
  if(DOS2UNIX_EXE)
    list(APPEND DOS2UNIX_OPTS -k -r)
    add_custom_target(format-sources-dos2unix-${target} COMMAND ${DOS2UNIX_EXE} ${DOS2UNIX_OPTS} ${_sources})
    add_dependencies(format-sources format-sources-dos2unix-${target})
  else()
    message(STATUS "CMLIB warning:")
    message(STATUS "  dos2unix executable is not found")
  endif()
endfunction()

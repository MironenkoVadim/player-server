# cmake-format: off
if(NOT TARGET create_auxilary_symlinks)
  if(UNIX)
    add_custom_target(
      create_auxilary_symlinks
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/files
      # Ссылка на каталог с журналами
      COMMAND ${CMAKE_COMMAND} -E create_symlink
              ${CMAKE_SOURCE_DIR}/files/log ${CMAKE_BINARY_DIR}/files/log
      # Ссылка на каталог с обрабатываемыми данными
      COMMAND ${CMAKE_COMMAND} -E create_symlink
              ${CMAKE_SOURCE_DIR}/files/lib ${CMAKE_BINARY_DIR}/files/lib
      # Ссылка на каталог с временными данными
      COMMAND ${CMAKE_COMMAND} -E create_symlink
              ${CMAKE_SOURCE_DIR}/files/cache ${CMAKE_BINARY_DIR}/files/cache
      # Ссылка на каталог с постоянными данными
      COMMAND ${CMAKE_COMMAND} -E create_symlink
              ${CMAKE_SOURCE_DIR}/files/data ${CMAKE_BINARY_DIR}/files/data
      # Ссылка на каталог настроек
      COMMAND ${CMAKE_COMMAND} -E create_symlink
              ${CMAKE_SOURCE_DIR}/files/etc ${CMAKE_BINARY_DIR}/etc)
  endif()
endif()
# cmake-format: on

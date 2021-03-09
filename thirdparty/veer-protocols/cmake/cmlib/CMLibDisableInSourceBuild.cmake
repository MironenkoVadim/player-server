# Запись результатов сборки проекта внутрь иерархии каталогов
# с исходными текстами приводит к засорению файлами формируемыми
# на этапе сборки, которые затрудняют разработку, поиск в оригинальных
# файлах и мешают ориентироваться в проекте. При работе с несколькими
# типами сборки, например, отладка и выпуск, появляется необходимость
# корректного полного удаления результатов предыдущего варианта.

get_filename_component(_source_realpath "${CMAKE_SOURCE_DIR}" REALPATH)
get_filename_component(_binary_realpath "${CMAKE_BINARY_DIR}" REALPATH)

if(${_source_realpath} STREQUAL ${_binary_realpath})
  message(FATAL_ERROR "In-source builds are not allowed.")
endif()

# Очистка от сгенерированных файлов
file(GLOB_RECURSE _cmakelists_files RELATIVE ${_source_realpath} CMakeLists.txt)
foreach(_it ${_cmakelists_files})
  get_filename_component(_file ${_it} REALPATH)
  get_filename_component(_dir ${_file} DIRECTORY)
  file(
    REMOVE_RECURSE
    ${_dir}/CMakeFiles
    ${_dir}/CMakeCache.txt
    ${_dir}/cmake_install.cmake
    ${_dir}/Makefile
    ${_dir}/build.ninja
    ${_dir}/rules.ninja)
endforeach()

# Минимальная версия Cmake
cmake_minimum_required(VERSION 3.3)
cmake_policy(VERSION 3.0.2..3.7)

# Название проекта
project(veer-protocols VERSION 0.2.0 LANGUAGES C CXX)

# В каталоге cmake/lib находятся файлы с библиотечными функциями
if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/cmake/cmlib)
  list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake/cmlib)
else()
  message(FATAL_ERROR "CMake library directory not exists")
endif()
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/find)

include(CMLibCommon)

if(${CMAKE_VERSION} VERSION_LESS "3.10.0")
  check_cxx_compiler_flag(-std=gnu++17 HAVE_FLAG_STD_GNUXX17)
  if(HAVE_FLAG_STD_GNUXX17)
    add_compile_options("-std=gnu++17")
  else()
    check_cxx_compiler_flag(-std=gnu++1z HAVE_FLAG_STD_GNUXX1Z)
    if(HAVE_FLAG_STD_GNUXX1Z)
      add_compile_options("-std=gnu++1z")
    else()
      check_cxx_compiler_flag(-std=c++17 HAVE_FLAG_STD_CXX17)
      if(HAVE_FLAG_STD_CXX17)
        add_compile_options("-std=c++17")
      else()
        check_cxx_compiler_flag(-std=c++1z HAVE_FLAG_STD_CXX1Z)
        if(HAVE_FLAG_STD_CXX1Z)
          add_compile_options("-std=c++1z")
        endif()
      endif()
    endif()
  endif()
else()
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_EXTENSIONS YES)
endif()

# Поиск библиотек с помощью pkgconfig
find_package(PkgConfig REQUIRED)

find_package(Qt5 COMPONENTS Core REQUIRED)

# Автоматически генерируемый заголовочный файл
cmlib_config_hpp_generate()

# Приложение
add_subdirectory(src/veer)

# Документация
add_subdirectory(cmake/doc)

# Тесты
option(BUILD_TESTS "Build unit tests" OFF)

if(BUILD_TESTS AND IS_DIRECTORY ${CMAKE_SOURCE_DIR}/tests)
  enable_testing()
  add_subdirectory(tests)
endif()

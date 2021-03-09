# Минимальная версия Cmake
cmake_minimum_required(VERSION 3.3)
cmake_policy(VERSION 3.0.2..3.7)

# Название проекта
project(
    player-server
    VERSION 0.3.0
    LANGUAGES C CXX)

# В каталоге cmake/lib находятся файлы с библиотечными функциями
if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/cmake/cmlib)
  list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake/cmlib)
else()
  message(FATAL_ERROR "CMake library directory not exists")
endif()
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/find)

include(CMLibCommon)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_CODE_COVERAGE "Enable code coverage" OFF)

# Подключение внешних проектов
include(ExternalProject)

ExternalProject_Add(veer-protocols
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/thirdparty/veer-protocols
  INSTALL_DIR ${CMAKE_BINARY_DIR}
  DOWNLOAD_COMMAND ""
  CONFIGURE_COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" ${CMLIB_EXT_PROJ_DEFAULT_ARGS} <SOURCE_DIR>
  BUILD_COMMAND true)

# Поиск библиотек с помощью pkgconfig
find_package(PkgConfig REQUIRED)

# Потоки
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Boost
find_package(Boost 1.55.0 REQUIRED)

# Qt5
find_package(Qt5 COMPONENTS Core Network REQUIRED)

# Автоматически генерируемый заголовочный файл
cmlib_config_hpp_generate()
configure_file(${CMAKE_SOURCE_DIR}/src/player-server/config_flags.hpp.in
               ${CMAKE_BINARY_DIR}/include/config_flags.hpp)

# Приложение
add_subdirectory(src/player-server)

# Документация
add_subdirectory(cmake/doc)

#add_executable(${PROJECT_NAME} "main.cpp")

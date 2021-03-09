cmake_policy(SET CMP0057 NEW)

# Добавление конфигурации для профилирования
if(CMAKE_CONFIGURATION_TYPES)
  if(NOT "Profile" IN_LIST CMAKE_CONFIGURATION_TYPES)
    list(APPEND CMAKE_CONFIGURATION_TYPES Profile)
  endif()
else()
  set(_allowed_build_types
      None
      Debug
      Release
      Profile
      RelWithDebInfo
      MinSizeRel)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${_allowed_build_types})
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
  elseif(NOT "${CMAKE_BUILD_TYPE}" IN_LIST _allowed_build_types)
    message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
  endif()
endif()

set(_gcc_debug_flags "-ggdb -fno-omit-frame-pointer")
set(_gcc_profile_flags "-pg")

if(CMAKE_BUILD_TYPE STREQUAL Profile)
  # Ключи компиляции для режима профилирования в зависимости от типа компилятора
  if(CMAKE_CXX_COMPILER_IS_Clang OR CMAKE_CXX_COMPILER_IS_GCC)
    set(CMAKE_C_FLAGS_PROFILE "${CMAKE_C_FLAGS_RELEASE} ${_gcc_debug_flags} ${_gcc_profile_flags}"
        CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS_PROFILE "${CMAKE_CXX_FLAGS_RELEASE} ${_gcc_debug_flags} ${_gcc_profile_flags}"
        CACHE STRING "" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS_PROFILE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} ${_gcc_profile_flags}"
        CACHE STRING "" FORCE)
    set(CMAKE_SHARED_LINKER_FLAGS_PROFILE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} ${_gcc_profile_flags}"
        CACHE STRING "" FORCE)
    set(CMAKE_STATIC_LINKER_FLAGS_PROFILE "${CMAKE_STATIC_LINKER_FLAGS_RELEASE}"
        CACHE STRING "" FORCE)
    set(CMAKE_MODULE_LINKER_FLAGS_PROFILE "${CMAKE_MODULE_LINKER_FLAGS_RELEASE} ${_gcc_profile_flags}"
        CACHE STRING "" FORCE)
  elseif(CMAKE_CXX_COMPILER_IS_Intel)
    message("Set options for profiling with Intel C++")
  elseif(CMAKE_CXX_COMPILER_IS_MSVC)
    message("Set options for profiling with Visual Studio C++")
  endif()
  set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "Enable generation of verbose build scripts." FORCE)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Enable generation of compile_commands.json." FORCE)
  set(PROFILE 1)
elseif(CMAKE_BUILD_TYPE STREQUAL Debug)
  # В режиме отладки подробный вывод сообщений компилятора
  if(CMAKE_CXX_COMPILER_IS_Clang OR CMAKE_CXX_COMPILER_IS_GCC)
    string(REPLACE " ${_gcc_debug_flags}" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${_gcc_debug_flags}" CACHE STRING "" FORCE)

    string(REPLACE " ${_gcc_debug_flags}" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${_gcc_debug_flags}" CACHE STRING "" FORCE)
  endif()
  set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "Enable generation of verbose build scripts." FORCE)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Enable generation of compile_commands.json." FORCE)
  set(DEBUG 1)
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
  set(RELEASE 1)
elseif(CMAKE_BUILD_TYPE STREQUAL None)
  # Режим None используется для статического анализа кода
  set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "Enable generation of verbose build scripts." FORCE)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Enable generation of compile_commands.json." FORCE)
  set(ANALYSIS 1)
endif()

unset(_gcc_debug_flags)
unset(_gcc_profile_flags)

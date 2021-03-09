set(COMMON_CXX_FEATURES cxx_alias_templates cxx_nullptr cxx_override)

function(common_target_properties target)
  get_target_property(_targetType ${target} TYPE)

  set(__visibility PUBLIC)
  if(_targetType STREQUAL INTERFACE_LIBRARY)
    set(__interface 1)
    set(__visibility INTERFACE)
  endif()

  get_target_property(__sources ${target} SOURCES)
  foreach(__src IN LISTS __sources)
    string(REGEX MATCH ".*/qrc_.*\\.cpp$" __qrc ${__src})
    if(__qrc)
      set_property(SOURCE ${__qrc} PROPERTY COTIRE_EXCLUDED ON)
    endif()
  endforeach()

  target_compile_features(${target} ${__visibility} ${COMMON_CXX_FEATURES})
  if(_targetType STREQUAL "EXECUTABLE")
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                               ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
    if(CMAKE_CXX_COMPILE_OPTIONS_PIE)
      target_compile_options(${target} PUBLIC "${CMAKE_CXX_COMPILE_OPTIONS_PIE}")
    endif()
  endif()

  target_include_directories(
    ${target}
    PUBLIC $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
           $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>)

  if(APPLE)
    target_compile_definitions(${target} ${__visibility} Darwin)
  endif()

  if(NOT __interface)
    if(TARGET Qt5::Core)
      if(_targetType STREQUAL "EXECUTABLE")
        target_compile_options(${target} PUBLIC "${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
      endif()
      if(NOT CMLIB_DEBUG_OUTPUT)
        add_definitions(-DQT_NO_DEBUG_OUTPUT)
      endif()
      if(NOT CMLIB_INFO_OUTPUT)
        add_definitions(-DQT_NO_INFO_OUTPUT)
      endif()
      if(NOT CMLIB_WARNING_OUTPUT)
        add_definitions(-DQT_NO_WARNING_OUTPUT)
      endif()
    endif()
    if(CMAKE_CXX_COMPILER_IS_GCC AND NOT APPLE)
      set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS " -Wl,--no-as-needed")
    endif()
  endif()

  # LTO only for executables (not libraries) in Release build type
  if(_targetType STREQUAL "EXECUTABLE" AND CMAKE_BUILD_TYPE STREQUAL "Release")
    check_cxx_compiler_flag(-flto CXX_HAS_LTO_FLAG)
    check_cxx_compiler_flag(-fno-fat-lto-objects CXX_HAS_NO_FAT_LTO_FLAG)
    if(CXX_HAS_LTO_FLAG)
      target_compile_options(${target} PUBLIC "-flto")
      set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS " -flto")
      if(CXX_HAS_NO_FAT_LTO_FLAG)
        target_compile_options(${target} PUBLIC "-fno-fat-lto-objects")
        set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS " -fno-fat-lto-objects")
      endif()
    endif()
  endif()

  set_property(TARGET ${target} PROPERTY COTIRE_ENABLE_PRECOMPILED_HEADER
                                         ${CMLIB_COTIRE_ENABLE_PRECOMPILED_HEADER})
  set_property(TARGET ${target} PROPERTY COTIRE_ADD_UNITY_BUILD ${CMLIB_COTIRE_ADD_UNITY_BUILD})

  if(CMAKE_BUILD_TYPE STREQUAL Profile)
    target_compile_definitions(${target} ${__visibility} PROFILE)
  elseif(CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(${target} ${__visibility} DEBUG)
  elseif(CMAKE_BUILD_TYPE STREQUAL Release)
    target_compile_definitions(${target} ${__visibility} RELEASE)
  elseif(CMAKE_BUILD_TYPE STREQUAL None)
    target_compile_definitions(${target} ${__visibility} ANALYSIS)
  endif()
  target_compile_definitions(
    ${target}
    ${__visibility}
    "TARGET_LSB_ID_${LSB_DISTRIBUTOR_ID}"
    "TARGET_LSB_CODENAME_${LSB_CODENAME}")
endfunction()

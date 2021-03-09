# Создание статической и динамической библиотеки из одинаковых объектных файлов
function(add_common_library target)
  set(options)
  set(oneValueArgs OUTPUT_NAME)
  set(multiValueArgs SOURCES)

  cmake_parse_arguments(_LOCAL "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  set(SOURCES ${_LOCAL_SOURCES})

  if(_LOCAL_OUTPUT_NAME)
    set(OUTNAME ${_LOCAL_OUTPUT_NAME})
  else()
    set(OUTNAME ${target})
  endif()

  add_library(${target} OBJECT ${SOURCES})
  target_include_directories(
    ${target} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                     $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include> $<INSTALL_INTERFACE:include/${target}>)
  set_target_properties(${target} PROPERTIES POSITION_INDEPENDENT_CODE ON)

  # cmake-format: off
  if(BUILD_SHARED_LIBS)
    add_library(${target}_shared SHARED $<TARGET_OBJECTS:${target}>)
    set_target_properties(${target}_shared PROPERTIES OUTPUT_NAME ${OUTNAME}
      VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR}
      LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
    install(TARGETS ${target}_shared LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
  endif()

  if(NOT SKIP_STATIC_LIBS)
    add_library(${target}_static STATIC $<TARGET_OBJECTS:${target}>)
    set_target_properties(${target}_static PROPERTIES OUTPUT_NAME ${OUTNAME}
      ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
    install(TARGETS ${target}_static ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
  endif()
  # cmake-format: on
endfunction()

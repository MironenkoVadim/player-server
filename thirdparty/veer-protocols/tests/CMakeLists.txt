find_package(Qt5 COMPONENTS Test REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/src)

set(tests
  test_base.cpp
  test_control_header.cpp
  test_error.cpp
  test_ping.cpp
  test_marks.cpp
  test_points.cpp
  test_radar_tracks.cpp
  test_spectrums.cpp
  test_track.cpp
  )

foreach(filename ${tests})
  get_filename_component(TRGT ${filename} NAME_WE)
  set(filename_cpp "${CMAKE_CURRENT_SOURCE_DIR}/${TRGT}.cpp")
  set(filename_hpp "${CMAKE_CURRENT_SOURCE_DIR}/${TRGT}.hpp")
  qt5_wrap_cpp(filename_moc ${filename_hpp})
  add_executable(${TRGT} ${filename_cpp} ${filename_moc} ${filename_hpp})
  add_format_sources(${TRGT} ${filename_cpp} ${filename_hpp})
  target_include_directories(${TRGT} SYSTEM PUBLIC ${Qt5Core_INCLUDE_DIRS})
  target_include_directories(${TRGT} SYSTEM PUBLIC ${Qt5Test_INCLUDE_DIRS})
  target_link_libraries(${TRGT} veer)
  target_link_libraries(${TRGT} Qt5::Core Qt5::Test)
  add_test(NAME ${TRGT} COMMAND ${TRGT})
  unset(filename_cpp)
  unset(filename_hpp)
  unset(filename_moc)
endforeach(filename)

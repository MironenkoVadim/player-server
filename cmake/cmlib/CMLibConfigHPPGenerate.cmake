function(cmlib_config_hpp_generate)
  include(CMLibLargeFiles)
  cmlib_test_large_files(HAVE_LARGEFILES)

  set(OUTPUT_FILE ${CMAKE_BINARY_DIR}/include/cmlib_private_config.hpp)
  if(CMLIB_GENERATED_HEADERS_PATH)
    set(OUTPUT_FILE ${CMLIB_GENERATED_HEADERS_PATH}/cmlib_private_config.hpp)
  elseif(ARGV0)
    set(OUTPUT_FILE ${ARGV0})
  endif()

  get_property(PROJECT_VERSION_INT GLOBAL PROPERTY PROJECT_VERSION_INT)
  configure_file(${CMLIB_MODULE_DIR}/hpp/cmlib_private_config.hpp.in ${OUTPUT_FILE})
endfunction()

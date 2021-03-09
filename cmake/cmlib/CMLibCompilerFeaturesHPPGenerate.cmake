if(${CMAKE_VERSION} VERSION_GREATER "3.6.0")
  include(WriteCompilerDetectionHeader)

  set(OUTPUT_FILE ${CMAKE_BINARY_DIR}/include/compiler_features.hpp)
  if(CMLIB_GENERATED_HEADERS_PATH)
    set(OUTPUT_FILE ${CMLIB_GENERATED_HEADERS_PATH}/compiler_features.hpp)
  endif()

  write_compiler_detection_header(
    FILE ${OUTPUT_FILE}
    PREFIX ${CMLIB_PROJECT_NAME_CANONICAL}
    COMPILERS GNU Clang MSVC Intel
    FEATURES
      cxx_nullptr
      cxx_override
      cxx_alignas
      cxx_alignof
      cxx_attributes
      cxx_auto_type
      cxx_constexpr
      cxx_digit_separators
      cxx_range_for)

  unset(OUTPUT_FILE)
endif()

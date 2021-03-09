function(set_project_version)
  if(NOT ${PROJECT_VERSION_PATCH} MATCHES "([0-9]+)")
    message(FATAL_ERROR "Please set project version in X.Y.Z format")
  endif()

  math(EXPR _version_int
       "(${PROJECT_VERSION_MAJOR} << 16) + (${PROJECT_VERSION_MINOR} << 8) + ${PROJECT_VERSION_PATCH}")
  set_property(GLOBAL PROPERTY PROJECT_VERSION_INT ${_version_int})
endfunction()

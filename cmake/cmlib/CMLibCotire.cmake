include(cotire)

if(COMMAND cotire)
  option(CMLIB_COTIRE_ENABLE_PRECOMPILED_HEADER "Enable precompiled headers" OFF)
  option(CMLIB_COTIRE_ADD_UNITY_BUILD "Enable unity build" OFF)
endif()

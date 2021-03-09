# По умолчанию отключена отладочная печать
# (если не включена явно программистом)
option(CMLIB_DEBUG_OUTPUT "Enable debug output" OFF)
option(CMLIB_INFO_OUTPUT "Enable info output" OFF)
option(CMLIB_WARNING_OUTPUT "Enable warning output" OFF)

# Если сборка производится в режиме для отладки,
# то включаются флаги для разрешения отладочной печати
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMLIB_DEBUG_OUTPUT ON CACHE BOOL "" FORCE)
  set(CMLIB_INFO_OUTPUT ON CACHE BOOL "" FORCE)
  set(CMLIB_WARNING_OUTPUT ON CACHE BOOL "" FORCE)
endif()

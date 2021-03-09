if(NOT EXISTS "${CMAKE_SOURCE_DIR}/cmake/etc/Variables.cmake")
  message(FATAL_ERROR "Required file cmake/etc/Variables.cmake does not exist")
endif()

include("${CMAKE_SOURCE_DIR}/cmake/etc/Variables.cmake")

if(NOT ORGANIZATION_NAME)
  message(FATAL_ERROR "Required variable ORGANIZATION_NAME is not defined")
endif()

set(CPACK_PACKAGE_VENDOR ${ORGANIZATION_NAME})

if(NOT CPACK_PACKAGE_CONTACT)
  message(FATAL_ERROR "Required variable CPACK_PACKAGE_CONTACT is not defined")
endif()

if(NOT CPACK_PACKAGE_DESCRIPTION_SUMMARY)
  message(FATAL_ERROR "Required variable CPACK_PACKAGE_DESCRIPTION_SUMMARY is not defined")
endif()

# По умолчанию пакет собирается для дистрибутива unstable
if(NOT DEBIAN_PACKAGE_TYPE)
  set(DEBIAN_PACKAGE_TYPE "unstable")
endif()

if(NOT CPACK_DEBIAN_PACKAGE_SECTION)
  set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
endif()

if(NOT CPACK_DEBIAN_PACKAGE_PRIORITY)
  set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
endif()

# По умолчанию пакет для Debian делится на компоненты
if(NOT CPACK_DEB_COMPONENT_INSTALL)
  set(CPACK_DEB_COMPONENT_INSTALL ON)
endif()

if(CMLIB_CPACK_DEFAULT_SCHEME)
  # Если имя компонента по умолчанию не определено, то устанавливается MAIN
  if(NOT CMAKE_INSTALL_DEFAULT_COMPONENT_NAME)
    set(CMAKE_INSTALL_DEFAULT_COMPONENT_NAME main)
  endif()

  # В списке компонентов обязательно должны быть main, base-dev, libs-dev и doc
  list(
    APPEND
    CPACK_COMPONENTS_ALL
    main
    base-dev
    libs-dev
    doc)
  list(REMOVE_DUPLICATES CPACK_COMPONENTS_ALL)

  # Правило формирования имени пакета и файла для компонента main
  set(CPACK_DEBIAN_MAIN_PACKAGE_NAME "${CMLIB_PROJECT_NAME_LOWER}")
  set(CPACK_DEBIAN_MAIN_FILE_NAME
      ${CMLIB_PROJECT_NAME_LOWER}_${CPACK_PACKAGE_VERSION}_${CPACK_TARGET_ARCH}.deb)

  # Правило формирования имени пакета и файла для компонента base-dev
  set(CPACK_DEBIAN_BASE-DEV_PACKAGE_NAME "lib${CMLIB_PROJECT_NAME_LOWER}-base-dev")
  set(CPACK_DEBIAN_BASE-DEV_FILE_NAME
      lib${CMLIB_PROJECT_NAME_LOWER}-base-dev_${CPACK_PACKAGE_VERSION}_${CPACK_TARGET_ARCH}.deb)

  # Правило формирования имени пакета и файла для компонента libs-dev
  set(CPACK_DEBIAN_LIBS-DEV_PACKAGE_NAME lib${CMLIB_PROJECT_NAME_LOWER}-dev)
  set(CPACK_DEBIAN_LIBS-DEV_FILE_NAME
      lib${CMLIB_PROJECT_NAME_LOWER}-dev_${CPACK_PACKAGE_VERSION}_${CPACK_TARGET_ARCH}.deb)

  set(CPACK_DEBIAN_LIBS-DEV_PACKAGE_DEPENDS "lib${CMLIB_PROJECT_NAME_LOWER}-base-dev")

  foreach(_C ${CPACK_COMPONENTS_ALL})
    string(TOLOWER ${_C} _cl)
    string(TOUPPER ${_C} _cu)
    # Правила формирования имени пакета и файла для остальных компонентов
    if(NOT ${_cl} STREQUAL main AND NOT ${_cl} STREQUAL base-dev AND NOT ${_cl} STREQUAL libs-dev)
      set(CPACK_DEBIAN_${_cu}_PACKAGE_NAME "${CMLIB_PROJECT_NAME_LOWER}-${_cl}")
      set(CPACK_DEBIAN_${_cu}_FILE_NAME
          "${CMLIB_PROJECT_NAME_LOWER}-${_cl}_${CPACK_PACKAGE_VERSION}_${CPACK_TARGET_ARCH}.deb")
    endif()

    # Если в каталоге ${CMAKE_SOURCE_DIR}/cmake/deb/${_cl} находятся сценарии сопровождающего
    # postinst, preinst, postrm и prerm, то они будут добавлены к пакету.
    if(EXISTS "${CMAKE_SOURCE_DIR}/cmake/deb/${_cl}/preinst")
      list(APPEND CPACK_DEBIAN_${_cu}_PACKAGE_CONTROL_EXTRA "${CMAKE_SOURCE_DIR}/cmake/deb/${_cl}/preinst")
    endif()
    if(EXISTS "${CMAKE_SOURCE_DIR}/cmake/deb/${_cl}/postinst")
      list(APPEND CPACK_DEBIAN_${_cu}_PACKAGE_CONTROL_EXTRA "${CMAKE_SOURCE_DIR}/cmake/deb/${_cl}/postinst")
    endif()
    if(EXISTS "${CMAKE_SOURCE_DIR}/cmake/deb/${_cl}/prerm")
      list(APPEND CPACK_DEBIAN_${_cu}_PACKAGE_CONTROL_EXTRA "${CMAKE_SOURCE_DIR}/cmake/deb/${_cl}/prerm")
    endif()
    if(EXISTS "${CMAKE_SOURCE_DIR}/cmake/deb/${_cl}/postrm")
      list(APPEND CPACK_DEBIAN_${_cu}_PACKAGE_CONTROL_EXTRA "${CMAKE_SOURCE_DIR}/cmake/deb/${_cl}/postrm")
    endif()
  endforeach()
endif()

if(UNIX AND NOT TARGET deb)
  add_custom_target(deb WORKING_DIRECTORY ${CMAKE_BINARY_DIR} COMMAND cpack -G DEB)
endif()

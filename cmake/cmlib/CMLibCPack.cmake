# Общие настройки для пакета: организация, автор, версия
set(CPACK_PACKAGE_VENDOR ${CMLIB_ORGANIZATION_NAME_LOWER})
set(CPACK_PACKAGE_NAME ${CMLIB_PROJECT_NAME_LOWER})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

# Параметры для архива исходных текстов
if(NOT CPACK_SOURCE_GENERATOR)
  set(CPACK_SOURCE_GENERATOR "TGZ")
endif()
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMLIB_PROJECT_NAME_LOWER}-${CPACK_PACKAGE_VERSION}")

# Типы генераторов для бинарных архивов
if(NOT CPACK_GENERATOR)
  set(CPACK_GENERATOR "TGZ" "DEB")
endif()

# Параметры для архива собранного проекта
set(CPACK_TARGET_ARCH ${CMAKE_SYSTEM_PROCESSOR})
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
  set(CPACK_TARGET_ARCH "amd64")
endif()
set(CPACK_PACKAGE_FILE_NAME "${CMLIB_PROJECT_NAME_LOWER}_${CPACK_TARGET_ARCH}_${CPACK_PACKAGE_VERSION}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMLIB_PROJECT_NAME_LOWER}-${CPACK_PACKAGE_VERSION}")

# Список масок для исключения из архива исходных текстов
set(CPACK_SOURCE_IGNORE_FILES
    "${CPACK_SOURCE_IGNORE_FILES}"
    "${CMAKE_BINARY_DIR}"
    "^${CMAKE_SOURCE_DIR}/.?build.?/"
    "^${CMAKE_SOURCE_DIR}/.?output.?/"
    "^${CMAKE_SOURCE_DIR}/files/lib"
    "^${CMAKE_SOURCE_DIR}/files/log"
    "CMakeLists.txt.user.*"
    ".*.autosave"
    ".*.status"
    "~$"
    "\\\\.swp$")

option(CMLIB_COMPACT_SOURCE_PACKAGE "Make compact source package" ON)
if(CMLIB_COMPACT_SOURCE_PACKAGE)
  # Список масок для исключения из архива исходных текстов для более компактного архива
  set(CPACK_SOURCE_IGNORE_FILES
      "${CPACK_SOURCE_IGNORE_FILES}"
      "\\\\.git"
      "/\\\\.git/"
      "/\\\\.gitlab-ci/"
      "\\\\.clang-tidy$"
      "\\\\.cmake-format$"
      "\\\\.gitignore$"
      "\\\\.gitattributes$"
      "\\\\.gitmodules$"
      "\\\\.gitlab-ci.yml$")
endif()

set(CPACK_PROJECT_CONFIG_FILE ${CMAKE_CURRENT_LIST_DIR}/CMLibCPackProject.cmake)

option(CMLIB_CPACK_DEFAULT_SCHEME "Use packaging default scheme" ON)

# Правила для сборки обычных архивов
if(CMLIB_CPACK_DEFAULT_SCHEME)
  set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
  set(CPACK_COMPONENTS_GROUPING IGNORE)
endif()

# Правила для сборки пакетов для Debian
include(CMLibCPackDeb)

# Подключение модуля, выполняющего сборку архивов и пакетов
include(CPack)

# CMake Modules

Репозиторий модулей для CMake.

## Установка

В каталоге проекта выполнить команду

```sh
git submodule add git@host:user/cmlib cmake/cmlib
```

заменив `host` и `user` на нужные значения.

Кроме того желательно установить библиотеки `find` и `generators`.

```sh
git submodule add git@host:user/cmake-find cmake/find
git submodule add git@host:user/cmake-generators cmake/generators
```


## Использование

В основном для проекта файле `CMakeLists.txt` добавить:

```cmake
if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/cmake/cmlib)
  list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake/cmlib)
else()
  message(FATAL_ERROR "CMake library directory not exists")
endif()

include(CMLibCommon)
```

Создать файл `cmake/etc/Variable.cmake`, в котором нужно
определить переменные, используемые в проекте, например:

```cmake
set(ORGANIZATION_NAME "org")

set(CPACK_GENERATOR "TXZ;DEB")
set(CPACK_PACKAGE_CONTACT "John Doe <john.doe@example.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Useful software")
set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_SOURCE_IGNORE_FILES
    .git$
    .swp$
    obj.*/
    _build/
    _output/
    files/var
    CMakeLists.txt.user
    ~$
    \\\\..*\\\\.swp$)
```


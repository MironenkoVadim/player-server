# Если выбран генератор Ninja, то в основном сборочном каталоге
# создаётся файл Makefile, который обрабатывается командой make и
# передаёт исполнение системе сборки ninja.
# Таким образом можно выполнять команду make, даже если правила
# сборки проекта сгенерированы для ninja.

if("${CMAKE_GENERATOR}" MATCHES "Ninja")
  file(WRITE ${CMAKE_BINARY_DIR}/Makefile ".PHONY: build\n%:\n\t@ninja \$@\nbuild:\n\t@ninja\n")
endif()

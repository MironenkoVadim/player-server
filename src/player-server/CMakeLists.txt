# Название основной цели в текущем каталоге
set(TRGT player-server)

# Список файлов исходных текстов
set(TRGT_cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/base_reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/base_server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/surok_marks_reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/surok_marks_server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/surok_adsb_reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/surok_adsb_server.cpp
    )

set(TRGT_moc_hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/base_reader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/base_server.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/surok_adsb_reader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/surok_marks_reader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/player.hpp
    )

set(TRGT_hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/application.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/file_format.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/surok_marks_server.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/surok_adsb_server.hpp
    )

set(TRGT_headers ${TRGT_hpp} ${TRGT_moc_hpp})

# Правило для автоматической генерации препроцессором moc
qt5_wrap_cpp(TRGT_moc_cpp ${TRGT_moc_hpp})

# Правила для создания файла ресурсов с вложенными файлами переводов
qt5_translation(
    TRGT_qrc_cpp
    OUTPUT_DIR ${CMAKE_SOURCE_DIR}/l10n BASE_NAME ${TRGT}
    SOURCES ${TRGT_cpp} ${TRGT_ui} LANGUAGES ru_RU)

# Правило для автоматической генерации препроцессором qrc
# (обязательно после вызова функции qt5_translation, если она есть,
# так как она добавляет свои файлы к списку ресурсов)
# qt5_add_resources(TRTG_qrc_cpp ${TRGT_qrc})

# Путь поиска библиотек внутри проекта
link_directories(${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})

# Цель для создания исполняемого файла
add_executable(${TRGT} ${TRGT_cpp} ${TRGT_ui_h} ${TRGT_moc_cpp} ${TRGT_qrc_cpp} ${TRGT_headers})

common_target_properties(${TRGT})
add_clang_tidy_check(${TRGT} ${TRGT_cpp} ${TRGT_headers})
add_clang_analyze_check(${TRGT} ${TRGT_cpp} ${TRGT_headers})
add_clazy_check(${TRGT} ${TRGT_cpp})
add_pvs_check(${TRGT})

# Форматирование исходников
add_format_sources(${TRGT} ${TRGT_cpp} ${TRGT_headers})

target_include_directories(${TRGT} SYSTEM PUBLIC ${Qt5Core_INCLUDE_DIRS})
target_include_directories(${TRGT} SYSTEM PUBLIC ${Qt5Network_INCLUDE_DIRS})
target_include_directories(${TRGT} SYSTEM PUBLIC ${CMAKE_BINARY_DIR}/include)

target_include_directories(${TRGT} SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})

#add_dependencies(${TRGT} myxlib)

target_include_directories(${TRGT} PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>)


# Имя выходного файла для цели
set_target_properties(${TRGT}
  PROPERTIES
  OUTPUT_NAME player-server
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}
  )


target_link_libraries(${TRGT} myx-filesystem myx-qt)
target_link_libraries(${TRGT} Qt5::Core Qt5::Network)
target_link_libraries(${TRGT} Threads::Threads)

add_sanitizers(${TRGT})
add_code_coverage(${TRGT})

# cotire(${TRGT})

# Правила для установки
install(TARGETS ${TRGT} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

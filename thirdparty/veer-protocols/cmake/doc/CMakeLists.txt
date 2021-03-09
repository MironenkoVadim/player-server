# cmake-format: off
if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/doc/breathe)
  add_breathe(
    doc-breathe
    COMMENT "Documentation in HTML format with Breathe generator")

  # Если цель doc-breathe была создана, то создаётся правило
  # для установки сгенерированной этой целью документации
  if(TARGET doc-breathe)
    install(DIRECTORY ${CMAKE_BINARY_DIR}/doc/breathe
            COMPONENT doc OPTIONAL
            DESTINATION ${CMAKE_INSTALL_DATADIR}/doc)
  endif()
endif()

add_doxygen(
  doc-doxygen
  LATEX ${DOXYGEN_GENERATE_LATEX}
  HTML ${DOXYGEN_GENERATE_HTML}
  COMMENT "Documentation in HTML and LaTeX format with Doxygen")

# Если цель doc-doxygen была создана, то создаётся правило
# для установки сгенерированной этой целью документации
if(TARGET doc-doxygen)
  install(DIRECTORY ${CMAKE_BINARY_DIR}/doc/doxygen/html/
          COMPONENT doc OPTIONAL
          DESTINATION ${CMAKE_INSTALL_DATADIR}/doc/doxygen)
endif()
# cmake-format: on

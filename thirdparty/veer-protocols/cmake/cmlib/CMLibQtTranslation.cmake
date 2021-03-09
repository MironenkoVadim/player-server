function(qt5_translation outfiles)
  find_package(Qt5 COMPONENTS LinguistTools REQUIRED)

  set(options)
  set(oneValueArgs BASE_NAME OUTPUT_DIR)
  set(multiValueArgs SOURCES LANGUAGES)

  cmake_parse_arguments(_QTTR "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  set(_base_name ${_QTTR_BASE_NAME})
  set(_sources ${_QTTR_SOURCES})
  set(_output_dir ${_QTTR_OUTPUT_DIR})
  set(_languages ${_QTTR_LANGUAGES})

  set(L10N_QRC_BODY "")
  make_directory(${_output_dir})

  foreach(_lang ${_languages})
    set(_ts "${_base_name}_${_lang}.ts")
    set(_qm "${_base_name}_${_lang}.qm")
    list(APPEND _ts_list ${_output_dir}/${_ts})
    list(APPEND _l10n_names_list "${_base_name}_l10n_${_lang}")
    string(APPEND L10N_QRC_BODY "<file alias=\"${_qm}\">${CMAKE_BINARY_DIR}/${_qm}</file>\n")

    add_custom_target(
      ${_base_name}_l10n_${_lang} COMMAND ${Qt5_LUPDATE_EXECUTABLE} ${_sources} -ts ${_output_dir}/${_ts}
                                          -target-language ${_lang} DEPENDS ${_sources})

    if(NOT EXISTS "${_output_dir}/${_ts}")
      add_custom_target(${_ts} DEPENDS ${_base_name}_l10n_${_lang})
    else()
      add_custom_target(${_ts} COMMAND echo "Skipping lupdate for ${_ts}")
    endif()

    add_custom_command(
      OUTPUT ${CMAKE_BINARY_DIR}/${_qm} COMMAND ${Qt5_LRELEASE_EXECUTABLE} ARGS ${_output_dir}/${_ts} -qm
                                                ${CMAKE_BINARY_DIR}/${_qm} DEPENDS ${_ts} ${_sources})
  endforeach()

  configure_file(${CMLIB_MODULE_DIR}/qrc/l10n.qrc.in ${CMAKE_BINARY_DIR}/${_base_name}_l10n.qrc)
  qt5_add_resources(${outfiles} ${CMAKE_BINARY_DIR}/${_base_name}_l10n.qrc)
  add_custom_target(${_base_name}_qrc DEPENDS ${_qrc})
  add_custom_target(${_base_name}_l10n DEPENDS ${_l10n_names_list})
  if(NOT TARGET l10n)
    add_custom_target(l10n)
  endif()
  add_dependencies(l10n ${_base_name}_l10n)

  # add_dependencies(${_target} ${_target}_qrc)
  # target_sources(${_target} PUBLIC ${_qrc})
  set(${outfiles} ${${outfiles}} PARENT_SCOPE)
endfunction()

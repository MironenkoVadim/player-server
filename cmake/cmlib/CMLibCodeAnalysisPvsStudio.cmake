function(add_pvs_check target)
  if(CMAKE_EXPORT_COMPILE_COMMANDS)
    include(PVS-Studio)
    find_program(PVS_STUDIO_ANALYZER_EXE NAMES pvs-studio-analyzer)
    if(PVS_STUDIO_ANALYZER_EXE)
      if(NOT TARGET pvs-check)
        add_custom_target(pvs-check)
      endif()
      pvs_studio_add_target(
        TARGET pvs-check-${target}
        DEPENDS ${target}
        COMPILE_COMMANDS HIDE_HELP OUTPUT
        FORMAT errorfile
        CONFIG "${CMAKE_BINARY_DIR}/PVS-Studio-${target}.cfg"
        ARGS --analysis-mode 29 --exclude-path ${CMAKE_CURRENT_BINARY_DIR}/${target}_autogen
        MODE GA:1,2,3;64:1;OP:1,2;CS:1,2)
      add_dependencies(pvs-check pvs-check-${target})
      configure_file("${CMLIB_MODULE_DIR}/hpp/pvs_studio.hpp.in" "${CMAKE_BINARY_DIR}/include/pvs_studio.hpp")
      get_target_property(target_type ${target} TYPE)
      if (${target_type} STREQUAL "INTERFACE_LIBRARY")
        set(target_type INTERFACE)
      else()
        set(target_type PRIVATE)
      endif()
      if(MSVC)
        target_compile_options(${target} BEFORE ${target_type} /FI "${CMAKE_BINARY_DIR}/include/pvs_studio.hpp")
      else() # GCC/Clang
        target_compile_options(${target} BEFORE ${target_type} -include "${CMAKE_BINARY_DIR}/include/pvs_studio.hpp")
      endif()
    else()
      message(STATUS "CMLIB warning:")
      message(STATUS "  PVS-Studio analyzer is not found")
    endif()
  else()
    message(STATUS "CMLIB warning:")
    message(STATUS "  Option CMAKE_EXPORT_COMPILE_COMMANDS is not set. PVS checks will be disabled.")
  endif()
endfunction()

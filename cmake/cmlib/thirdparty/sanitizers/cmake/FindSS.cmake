option(SANITIZE_SS "Enable SafeStack for sanitized targets." OFF)

set(FLAG_CANDIDATES
  "-g -fsanitize=safe-stack"
  )

# There might be some conflict with the other sanitizer
# hence it might need an if statement here.

# add some handy functions
include(sanitize-helpers)

if(SANITIZE_SS)
  sanitizer_check_compiler_flags("${FLAG_CANDIDATES}" "SafeStack"
    "SS")
endif() 

function (add_sanitize_ss TARGET)
  if (NOT SANITIZE_SS)
    return()
  endif()

  sanitizer_add_flags(${TARGET} "SafeStack" "SS")
endfunction()

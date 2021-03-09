option(SANITIZE_CFI "Enable Control Flow Integrity (CFI) for sanitized targets." OFF)

# FIXME: Might also want to add the variants of the CFI options

set(FLAG_CANDIDATES
  # FIXME: Brief comment on why the additional flags
  # In this case you need a 
  # linker that does optimization at
  # linking time such as LLVM lld or GNU gold.
  "-g -fsanitize=cfi -fvisibility=hidden -flto -fuse-ld=lld"
  )

# There might be some conflict with the other sanitizer
# hence it might need an if statement here.

# add some handy functions
include(sanitize-helpers)

if(SANITIZE_CFI)
  sanitizer_check_compiler_flags("${FLAG_CANDIDATES}" "ControlFlowIntegrity"
    "CFI")
endif() 

function (add_sanitize_cfi TARGET)
  if (NOT SANITIZE_CFI)
    return()
  endif()

  sanitizer_add_flags(${TARGET} "ControlFlowIntegrity" "CFI")
endfunction()


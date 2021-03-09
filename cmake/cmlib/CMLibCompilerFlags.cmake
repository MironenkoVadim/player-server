# based on https://github.com/bluescarni/yacma

option(CMLIB_WARNING_FLAGS "Enable warning flags" ON)

include(CheckCXXCompilerFlag)

macro(CHECK_ENABLE_CXX_FLAG flag)
  set(CMAKE_REQUIRED_QUIET TRUE)
  check_cxx_compiler_flag("${flag}" CHECK_CXX_FLAG)
  unset(CMAKE_REQUIRED_QUIET)

  if(CHECK_CXX_FLAG)
    message(STATUS "'${flag}': flag is enabled.")
    add_compile_options("${flag}")
  else()
    message(STATUS "'${flag}': flag is NOT supported.")
  endif()
  # NOTE: check_cxx_compiler stores variables in the cache.
  unset(CHECK_CXX_FLAG CACHE)
endmacro()

if(LSB_DISTRIBUTOR_ID STREQUAL "AstraLinuxSE" AND LSB_CODENAME STREQUAL "smolensk" AND LSB_RELEASE STREQUAL
                                                                                       "1.5")
  set(_CMAKE_TOOLCHAIN_PREFIX "x86_64-linux-gnu-")
  set(_CMAKE_TOOLCHAIN_SUFFIX "-4.7")
  set(_CMAKE_TOOLCHAIN_LOCATION} "/usr/bin")
else()
  # -Wshadow gives a lot of false positives with GCC 4.7.2 in Astra Linux 1.5
  if(CMAKE_CXX_COMPILER_IS_GCC)
    check_enable_cxx_flag(-Wshadow)
  endif()
endif()

# Выбор стандарта по умолчанию (можно переопределить в проекте)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

check_cxx_compiler_flag(-std=c++14 HAVE_FLAG_STD_CXX14)
if(HAVE_FLAG_STD_CXX14)
  set(CMAKE_CXX_STANDARD 14)
  check_cxx_compiler_flag(-std=gnu++14 HAVE_FLAG_STD_GNUXX14)
  if(HAVE_FLAG_STD_GNUXX14)
    set(CMAKE_CXX_EXTENSIONS YES)
  endif()
else()
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_EXTENSIONS YES)
endif()

# Common configuration for GCC, clang and Intel.
if(CMAKE_CXX_COMPILER_IS_CLANG OR CMAKE_CXX_COMPILER_IS_INTEL OR CMAKE_CXX_COMPILER_IS_GCC)
  if(CMLIB_WARNING_FLAGS AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    check_enable_cxx_flag(-Wall)
    check_enable_cxx_flag(-Wextra)
    check_enable_cxx_flag(-Wnon-virtual-dtor)
    check_enable_cxx_flag(-Wnoexcept)
    check_enable_cxx_flag(-Wlogical-op)
    check_enable_cxx_flag(-Wconversion)
    check_enable_cxx_flag(-Wdeprecated)
    # This limit is supposed to be at least 1024 in C++11, but for some reason
    # clang sets this to 256, and gcc to 900.
    check_enable_cxx_flag(-ftemplate-depth=1024)
    check_enable_cxx_flag(-Wold-style-cast)
    check_enable_cxx_flag(-Wdisabled-optimization)
    # This is useful when the compiler decides the template backtrace is too
    # verbose.
    check_enable_cxx_flag(-ftemplate-backtrace-limit=0)
    check_enable_cxx_flag(-fstack-protector-all)
    # A few suggestion flags.
    check_enable_cxx_flag(-Wsuggest-attribute=pure)
    check_enable_cxx_flag(-Wsuggest-attribute=const)
    check_enable_cxx_flag(-Wsuggest-attribute=noreturn)
    check_enable_cxx_flag(-Wsuggest-attribute=format)
    # From GCC 5.
    check_enable_cxx_flag(-Wodr)
    check_enable_cxx_flag(-Wsuggest-final-types)
    check_enable_cxx_flag(-Wsuggest-final-methods)
    check_enable_cxx_flag(-Wsuggest-override)
    # From GCC 6.
    check_enable_cxx_flag(-Wshift-negative-value)
    check_enable_cxx_flag(-Wshift-overflow=2)
    check_enable_cxx_flag(-Wduplicated-cond)
    check_enable_cxx_flag(-Wnull-dereference)
    # From GCC 7.
    check_enable_cxx_flag(-Wrestrict)
    check_enable_cxx_flag(-Waligned-new)
    # From GCC 8.
    check_enable_cxx_flag(-Wcast-align=strict)
    # This is supposed to produce a nice graphical visualization of mismatching
    # template errors.
    check_enable_cxx_flag(-fdiagnostics-show-template-tree)
    check_enable_cxx_flag(-fdiagnostics-show-option)

    check_enable_cxx_flag(-pedantic)
    check_enable_cxx_flag(-Wcast-align)
    check_enable_cxx_flag(-Wcast-qual)
    check_enable_cxx_flag(-Wctor-dtor-privacy)
    check_enable_cxx_flag(-Wdisabled-optimization)
    check_enable_cxx_flag(-Wformat=2)
    check_enable_cxx_flag(-Winit-self)
    check_enable_cxx_flag(-Wmissing-include-dirs)
    check_enable_cxx_flag(-Woverloaded-virtual)
    check_enable_cxx_flag(-Wredundant-decls)
    check_enable_cxx_flag(-Wsign-promo)
    check_enable_cxx_flag(-Wstrict-overflow=5)
    check_enable_cxx_flag(-Wundef)
    check_enable_cxx_flag(-Wno-unused)
    check_enable_cxx_flag(-Wno-variadic-macros)
    check_enable_cxx_flag(-Wno-parentheses)
    check_enable_cxx_flag(-Wstrict-null-sentinel)
    check_enable_cxx_flag(-Wshadow-all)
  endif()
endif()

if(CMAKE_CXX_COMPILER_IS_GCC)
  check_enable_cxx_flag(-fdiagnostics-color=auto)
  # The -Wmaybe-uninitialized flag is enabled by -Wall,
  # but it is known to emit a lot of possibly spurious warnings.
  # Let's just disable it.
  check_enable_cxx_flag(-Wno-maybe-uninitialized)
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "5.999")
    # NOTE: GCC >= 6 seems to be wrongly warning about visibility attributes
    # in some situations:
    # https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80947
    # Let's just disable the warning for now.
    check_enable_cxx_flag(-Wno-attributes)
  endif()
endif()

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "e2k")
  check_enable_cxx_flag(-Wno-invalid-offsetof)
  list(APPEND CMAKE_LIBRARY_PATH "/usr/lib/e2k-linux-gnu")
endif()

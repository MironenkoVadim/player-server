# Copyright (c) 2008-2010 Kent State University
# Copyright (c) 2011-2012 Texas A&M University
#
# This file is distributed under the MIT License. See the accompanying file
# LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
# and conditions.

# NOTE: MPFR prefix is understood to be the path to the root of the MPFR
# installation library.

set(MPFR_PREFIX "" CACHE PATH "The path to the previx of an MPFR installation")

find_path(MPFR_INCLUDE_DIR mpfr.h
  PATHS ${MPFR_PREFIX}/include)

find_library(MPFR_LIBRARIES NAMES mpfr
  PATHS ${MPFR_PREFIX}/lib)

if(MPFR_INCLUDE_DIR AND MPFR_LIBRARIES)
  get_filename_component(MPFR_LIBRARY_DIR ${MPFR_LIBRARIES} PATH)
  set(MPFR_FOUND TRUE)
endif()

if(MPFR_FOUND)
  if(NOT MPFR_FIND_QUIETLY)
    MESSAGE(STATUS "Found MPFR: ${MPFR_LIBRARIES}")
  endif()
  set(HAVE_MPFR 1)
elseif(MPFR_FOUND)
  if(MPFR_FIND_REQUIRED)
    message(FATAL_ERROR "Could not find MPFR")
  endif()
endif()

# ##############################################################################
# The MIT License (MIT)
#
# Copyright (c) <2015> hanepjiv <hanepjiv@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ==============================================================================
# settings ---------------------------------------------------------------------
add_definitions(-DHAVE_CONFIG_H)
include_directories(${OBORO_INCLUDE_DIRS})
link_directories(${OBORO_LIBRARY_DIRS})
# ==============================================================================
# oboro  --------------------------------------------------------------------
#set(OBORO_SOURCES
#  oboro.cc
#  )
# ------------------------------------------------------------------------------
#add_library(oboro SHARED ${OBORO_SOURCES})
#target_link_libraries(oboro
#  )
#set_target_properties(oboro
#  PROPERTIES
#  OUTPUT_NAME "oboro"
#  VERSION ${OBORO_VERSION}
#  SOVERSION ${OBORO_SOVERSION}
#  COMPILE_FLAGS "-DOBORO_EXPORTS ${OBORO_CXX_FLAGS}"
#  )
# ------------------------------------------------------------------------------
#add_library(oboro-static STATIC ${OBORO_SOURCES})
#target_link_libraries(oboro-static
#  )
#set_target_properties(oboro-static
#  PROPERTIES
#  OUTPUT_NAME "oboro"
#  COMPILE_FLAGS "-DOBORO_EXPORTS ${OBORO_CXX_FLAGS}"
#  )
# ------------------------------------------------------------------------------
#install(TARGETS
#  oboro
#  oboro-static
#  RUNTIME DESTINATION bin
#  LIBRARY DESTINATION lib
#  ARCHIVE DESTINATION lib
#  )
# ==============================================================================
# tests  -----------------------------------------------------------------------
if(OBORO_ENABLE_TEST)
  # ----------------------------------------------------------------------------
  set(OBORO_SRC_TEST_EXE)
  # splint  --------------------------------------------------------------------
  if(SPLINT)
    add_test(src-splint ${SPLINT_SH})
    list(APPEND OBORO_SRC_TEST_EXE src-splint)
  endif()
  # cpplint  -------------------------------------------------------------------
  if(PYTHON)
    add_test(src-cpplint ${CPPLINT_SH})
    list(APPEND OBORO_SRC_TEST_EXE src-cpplint)
  endif()
  # environment  ---------------------------------------------------------------
  set(TEST_ENV_ "${TEST_ENV}")
  list(APPEND TEST_ENV_ "SRCDIR=${CMAKE_CURRENT_SOURCE_DIR}")
  list(APPEND TEST_ENV_ "BUILDDIR=${CMAKE_CURRENT_BINARY_DIR}")
  set_tests_properties(${OBORO_SRC_TEST_EXE}
    PROPERTIES ENVIRONMENT "${TEST_ENV_}")
endif()

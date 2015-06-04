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
# ##############################################################################
# subdirectory =================================================================
# ------------------------------------------------------------------------------

# ==============================================================================
# oboro ------------------------------------------------------------------------
set(OBORO_INCLUDE_OBORO_SRC "${OBORO_ROOT_DIR}/include/oboro")
set(OBORO_INCLUDE_OBORO_DEST "include/oboro")
# ------------------------------------------------------------------------------
set(oboro_HEADERS
  ${OBORO_INCLUDE_OBORO_SRC}/call.h
  ${OBORO_INCLUDE_OBORO_SRC}/declspec.h
  ${OBORO_INCLUDE_OBORO_SRC}/begin.h

  ${OBORO_INCLUDE_OBORO_SRC}/debug.h

  ${OBORO_INCLUDE_OBORO_SRC}/oboro.hpp
  ${OBORO_INCLUDE_OBORO_SRC}/module.hpp
  ${OBORO_INCLUDE_OBORO_SRC}/function.hpp

  ${OBORO_INCLUDE_OBORO_SRC}/oboro.hh
  )
# ------------------------------------------------------------------------------
install(FILES
  ${oboro_HEADERS}
  DESTINATION ${OBORO_INCLUDE_OBORO_DEST})
# ==============================================================================
# tests  -----------------------------------------------------------------------
if(OBORO_ENABLE_TEST)
  # ----------------------------------------------------------------------------
  set(OBORO_SRC_TEST_EXE)
  # splint  --------------------------------------------------------------------
  if(SPLINT)
    add_test(splint-include-oboro ${SPLINT_SH})
    list(APPEND OBORO_SRC_TEST_EXE splint-include-oboro)
  endif()
  # cpplint  -------------------------------------------------------------------
  if(PYTHON2)
    add_test(cpplint-include-oboro ${CPPLINT_SH})
    list(APPEND OBORO_SRC_TEST_EXE cpplint-include-oboro)
  endif()
  # environment  ---------------------------------------------------------------
  set(TEST_ENV_ "${TEST_ENV}")
  list(APPEND TEST_ENV_ "SRCDIR=${OBORO_ROOT_DIR}/include/oboro")
  list(APPEND TEST_ENV_ "BUILDDIR=${CMAKE_CURRENT_BINARY_DIR}")
  set_tests_properties(${OBORO_SRC_TEST_EXE}
    PROPERTIES ENVIRONMENT "${TEST_ENV_}")
endif()

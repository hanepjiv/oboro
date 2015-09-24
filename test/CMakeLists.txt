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
# tests ------------------------------------------------------------------------
if(OBORO_ENABLE_TEST)
  # ----------------------------------------------------------------------------
  set(OBORO_TEST_TEST_EXE)
  # splint  --------------------------------------------------------------------
  if(SPLINT)
    add_test(splint-test ${SPLINT_SH})
    list(APPEND OBORO_TEST_TEST_EXE splint-test)
  endif()
  # cpplint  -------------------------------------------------------------------
  if(PYTHON2)
    add_test(cpplint-test ${CPPLINT_SH})
    list(APPEND OBORO_TEST_TEST_EXE cpplint-test)
  endif()
  # ----------------------------------------------------------------------------
  set(test00_SRCS
    ${abs_top_srcdir}/include/oboro/debug.h

    ${abs_top_srcdir}/include/oboro/oboro.hpp
    ${abs_top_srcdir}/include/oboro/module.hpp
    ${abs_top_srcdir}/include/oboro/function.hpp

    ${abs_top_srcdir}/include/oboro/oboro.hh

    ${abs_top_srcdir}/test/test00.cc
    )
  add_executable(test00 ${test00_SRCS})
  target_link_libraries(test00 ${OBORO_LIBRARIES})
  set_target_properties(test00
    PROPERTIES
    COMPILE_FLAGS "${OBORO_CXX_FLAGS}"
    )
  add_test(test00 test00)
  list(APPEND OBORO_TEST_TEST_EXE test00)
  # ----------------------------------------------------------------------------
  set(test01_SRCS
    ${abs_top_srcdir}/include/oboro/debug.h

    ${abs_top_srcdir}/include/oboro/oboro.hpp
    ${abs_top_srcdir}/include/oboro/module.hpp
    ${abs_top_srcdir}/include/oboro/function.hpp

    ${abs_top_srcdir}/include/oboro/oboro.hh

    ${abs_top_srcdir}/test/test01.cc
    )
  add_executable(test01 ${test01_SRCS})
  target_link_libraries(test01 ${OBORO_LIBRARIES})
  set_target_properties(test01
    PROPERTIES
    COMPILE_FLAGS "${OBORO_CXX_FLAGS}"
    )
  add_test(test01 test01)
  list(APPEND OBORO_TEST_TEST_EXE test01)
  # environment  ---------------------------------------------------------------
  set(TEST_ENV_ "${TEST_ENV}")
  set(TEST_ENV_ "${TEST_ENV_};SRCDIR=${abs_top_srcdir}/test")
  set(TEST_ENV_ "${TEST_ENV_};BUILDDIR=${CMAKE_CURRENT_BINARY_DIR}")
  set_tests_properties(${OBORO_TEST_TEST_EXE}
    PROPERTIES ENVIRONMENT "${TEST_ENV_}")
endif()

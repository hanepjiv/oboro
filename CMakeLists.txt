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
# CMake  =======================================================================
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.3)
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/Modules/")
# ##############################################################################
# oboro  ====================================================================
# ------------------------------------------------------------------------------
set(OBORO_PACKAGE     "oboro")
set(OBORO_CURRENT     "0")
set(OBORO_REVISION    "0")
set(OBORO_AGE         "0")
set(OBORO_BUGREPORT   "hanepjiv <hanepjiv@gmail.com>")
set(OBORO_URL         "https://")
# ------------------------------------------------------------------------------
if(${OBORO_CURRENT} LESS ${OBORO_AGE})
  message(FATAL_ERROR
    "OBORO_AGE `${OBORO_AGE}' is greater than the current interface number `${OBORO_CURRENT}'.")
endif()
# ------------------------------------------------------------------------------
string(TOUPPER ${OBORO_PACKAGE} OBORO_PACKAGE_UPPER)
math(EXPR OBORO_MAJOR "${OBORO_CURRENT}-${OBORO_AGE}")
set(OBORO_VERSION "${OBORO_MAJOR}.${OBORO_AGE}.${OBORO_REVISION}")
set(OBORO_SOVERSION "${OBORO_MAJOR}")
# ------------------------------------------------------------------------------
project(${OBORO_PACKAGE}
  VERSION ${OBORO_VERSION}
  LANGUAGES C CXX)
# ##############################################################################
# include  =====================================================================
# ------------------------------------------------------------------------------
include(FindPkgConfig)
include(FindThreads)
include(CCxxFlags)
# ##############################################################################
# options  =====================================================================
# ------------------------------------------------------------------------------
option(OBORO_ENABLE_TEST "Test feature." OFF)
# ##############################################################################
# flags  =======================================================================
# ------------------------------------------------------------------------------
set(OBORO_C_CXX_FLAGS_DEBUG             "-DOBORO_DEBUG")
set(OBORO_C_CXX_FLAGS_RELWITHDEBINFO    "-DOBORO_DEBUG")
set(OBORO_C_CXX_FLAGS_RELEASE           "-DNDEBUG")
set(OBORO_C_CXX_FLAGS_MINSIZEREL        "-DNDEBUG")
# ------------------------------------------------------------------------------
if (CMAKE_COMPILER_IS_GNUCC OR
    CMAKE_C_COMPILER_ID STREQUAL "Clang")       # GCC or Clang  ================
  set(OBORO_C_CXX_FLAGS                 "-fno-asm -fno-builtin")
  set(OBORO_C_CXX_FLAGS_DEBUG           "${OBORO_C_CXX_FLAGS_DEBUG}")
  set(OBORO_C_CXX_FLAGS_RELWITHDEBINFO  "${OBORO_C_CXX_FLAGS_RELWITHDEBINFO}")
  set(OBORO_C_CXX_FLAGS_RELEASE         "${OBORO_C_CXX_FLAGS_RELEASE}")
  set(OBORO_C_CXX_FLAGS_MINSIZEREL      "${OBORO_C_CXX_FLAGS_MINSIZEREL}")
  set(OBORO_C_FLAGS                     "-std=c99")
  set(OBORO_C_FLAGS_DEBUG               "")
  set(OBORO_C_FLAGS_RELWITHDEBINFO      "")
  set(OBORO_C_FLAGS_RELEASE             "")
  set(OBORO_C_FLAGS_MINSIZEREL          "")
  set(OBORO_CXX_FLAGS                   "-std=c++11 -fexceptions -frtti")
  set(OBORO_CXX_FLAGS_DEBUG             "")
  set(OBORO_CXX_FLAGS_RELWITHDEBINFO    "")
  set(OBORO_CXX_FLAGS_RELEASE           "")
  set(OBORO_CXX_FLAGS_MINSIZEREL        "")
endif()
# ------------------------------------------------------------------------------
if (CMAKE_COMPILER_IS_GNUCC)                    # GCC  =========================

elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")    # Clang  =======================

elseif(CMAKE_C_COMPILER_ID STREQUAL "Intel")    # Intel  =======================
  message(FATAL_ERROR "Intel is not yet supported.")
  set(OBORO_C_CXX_FLAGS                 "TODO")
  set(OBORO_C_CXX_FLAGS_DEBUG           "${OBORO_C_CXX_FLAGS_DEBUG TODO}")
  set(OBORO_C_CXX_FLAGS_RELWITHDEBINFO  "${OBORO_C_CXX_FLAGS_RELWITHDEBINFO TODO}")
  set(OBORO_C_CXX_FLAGS_RELEASE         "${OBORO_C_CXX_FLAGS_RELEASE TODO}")
  set(OBORO_C_CXX_FLAGS_MINSIZEREL      "${OBORO_C_CXX_FLAGS_MINSIZEREL TODO}")
  set(OBORO_C_FLAGS                     "TODO")
  set(OBORO_C_FLAGS_DEBUG               "TODO")
  set(OBORO_C_FLAGS_RELWITHDEBINFO      "TODO")
  set(OBORO_C_FLAGS_RELEASE             "TODO")
  set(OBORO_C_FLAGS_MINSIZEREL          "TODO")
  set(OBORO_CXX_FLAGS                   "TODO")
  set(OBORO_CXX_FLAGS_DEBUG             "TODO")
  set(OBORO_CXX_FLAGS_RELWITHDEBINFO    "TODO")
  set(OBORO_CXX_FLAGS_RELEASE           "TODO")
  set(OBORO_CXX_FLAGS_MINSIZEREL        "TODO")
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")     # MSVC  ========================
  message(FATAL_ERROR "MSVC is not yet supported.")
  set(OBORO_C_CXX_FLAGS                 "TODO")
  set(OBORO_C_CXX_FLAGS_DEBUG           "${OBORO_C_CXX_FLAGS_DEBUG TODO}")
  set(OBORO_C_CXX_FLAGS_RELWITHDEBINFO  "${OBORO_C_CXX_FLAGS_RELWITHDEBINFO TODO}")
  set(OBORO_C_CXX_FLAGS_RELEASE         "${OBORO_C_CXX_FLAGS_RELEASE TODO}")
  set(OBORO_C_CXX_FLAGS_MINSIZEREL      "${OBORO_C_CXX_FLAGS_MINSIZEREL TODO}")
  set(OBORO_C_FLAGS                     "TODO")
  set(OBORO_C_FLAGS_DEBUG               "TODO")
  set(OBORO_C_FLAGS_RELWITHDEBINFO      "TODO")
  set(OBORO_C_FLAGS_RELEASE             "TODO")
  set(OBORO_C_FLAGS_MINSIZEREL          "TODO")
  set(OBORO_CXX_FLAGS                   "TODO")
  set(OBORO_CXX_FLAGS_DEBUG             "TODO")
  set(OBORO_CXX_FLAGS_RELWITHDEBINFO    "TODO")
  set(OBORO_CXX_FLAGS_RELEASE           "TODO")
  set(OBORO_CXX_FLAGS_MINSIZEREL        "TODO")
endif()
# ------------------------------------------------------------------------------
set(OBORO_USER_C_CXX_FLAGS "${OBORO_C_CXX_FLAGS}"  CACHE STRING "")
set(OBORO_USER_C_CXX_FLAGS_DEBUG "${OBORO_C_CXX_FLAGS_DEBUG}"  CACHE STRING "")
set(OBORO_USER_C_CXX_FLAGS_RELWITHDEBINFO "${OBORO_C_CXX_FLAGS_RELWITHDEBINFO}"  CACHE STRING "")
set(OBORO_USER_C_CXX_FLAGS_RELEASE "${OBORO_C_CXX_FLAGS_RELEASE}"  CACHE STRING "")
set(OBORO_USER_C_CXX_FLAGS_MINSIZEREL "${OBORO_C_CXX_FLAGS_MINSIZEREL}"  CACHE STRING "")
set(OBORO_USER_C_FLAGS "${OBORO_C_FLAGS}"  CACHE STRING "")
set(OBORO_USER_C_FLAGS_DEBUG "${OBORO_C_FLAGS_DEBUG}"  CACHE STRING "")
set(OBORO_USER_C_FLAGS_RELWITHDEBINFO "${OBORO_C_FLAGS_RELWITHDEBINFO}"  CACHE STRING "")
set(OBORO_USER_C_FLAGS_RELEASE "${OBORO_C_FLAGS_RELEASE}"  CACHE STRING "")
set(OBORO_USER_C_FLAGS_MINSIZEREL "${OBORO_C_FLAGS_MINSIZEREL}"  CACHE STRING "")
set(OBORO_USER_CXX_FLAGS "${OBORO_CXX_FLAGS}"  CACHE STRING "")
set(OBORO_USER_CXX_FLAGS_DEBUG "${OBORO_CXX_FLAGS_DEBUG}"  CACHE STRING "")
set(OBORO_USER_CXX_FLAGS_RELWITHDEBINFO "${OBORO_CXX_FLAGS_RELWITHDEBINFO}"  CACHE STRING "")
set(OBORO_USER_CXX_FLAGS_RELEASE "${OBORO_CXX_FLAGS_RELEASE}"  CACHE STRING "")
set(OBORO_USER_CXX_FLAGS_MINSIZEREL "${OBORO_CXX_FLAGS_MINSIZEREL}"  CACHE STRING "")
# ------------------------------------------------------------------------------
if    ("None" STREQUAL CMAKE_BUILD_TYPE OR NOT CMAKE_BUILD_TYPE)
elseif("Debug" STREQUAL CMAKE_BUILD_TYPE)
  set(OBORO_C_FLAGS "${OBORO_USER_C_CXX_FLAGS} ${OBORO_USER_C_CXX_FLAGS_DEBUG} ${OBORO_USER_C_FLAGS} ${OBORO_USER_C_FLAGS_DEBUG}")
  set(OBORO_CXX_FLAGS "${OBORO_USER_C_CXX_FLAGS} ${OBORO_USER_C_CXX_FLAGS_DEBUG} ${OBORO_USER_CXX_FLAGS} ${OBORO_USER_CXX_FLAGS_DEBUG}")
elseif("RelWithDebInfo" STREQUAL CMAKE_BUILD_TYPE)
  set(OBORO_C_FLAGS "${OBORO_USER_C_CXX_FLAGS} ${OBORO_USER_C_CXX_FLAGS_RELWITHDEBINFO} ${OBORO_USER_C_FLAGS} ${OBORO_USER_C_FLAGS_RELWITHDEBINFO}")
  set(OBORO_CXX_FLAGS "${OBORO_USER_C_CXX_FLAGS} ${OBORO_USER_C_CXX_FLAGS_RELWITHDEBINFO} ${OBORO_USER_CXX_FLAGS} ${OBORO_USER_CXX_FLAGS_RELWITHDEBINFO}")
elseif("Release" STREQUAL CMAKE_BUILD_TYPE)
  set(OBORO_C_FLAGS "${OBORO_USER_C_CXX_FLAGS} ${OBORO_USER_C_CXX_FLAGS_RELEASE} ${OBORO_USER_C_FLAGS} ${OBORO_USER_C_FLAGS_RELEASE}")
  set(OBORO_CXX_FLAGS "${OBORO_USER_C_CXX_FLAGS} ${OBORO_USER_C_CXX_FLAGS_RELEASE} ${OBORO_USER_CXX_FLAGS} ${OBORO_USER_CXX_FLAGS_RELEASE}")
elseif("MinSizeRel" STREQUAL CMAKE_BUILD_TYPE)
  set(OBORO_C_FLAGS "${OBORO_USER_C_CXX_FLAGS} ${OBORO_USER_C_CXX_FLAGS_MINSIZEREL} ${OBORO_USER_C_FLAGS} ${OBORO_USER_C_FLAGS_MINSIZEREL}")
  set(OBORO_CXX_FLAGS "${OBORO_USER_C_CXX_FLAGS} ${OBORO_USER_C_CXX_FLAGS_MINSIZEREL} ${OBORO_USER_CXX_FLAGS} ${OBORO_USER_CXX_FLAGS_MINSIZEREL}")
endif()
# ##############################################################################
# root  ========================================================================
# ------------------------------------------------------------------------------
set(abs_top_srcdir "${CMAKE_CURRENT_SOURCE_DIR}")
# ##############################################################################
# programs =====================================================================
# ------------------------------------------------------------------------------
if (NOT (CMAKE_C_COMPILER_ID STREQUAL CMAKE_CXX_COMPILER_ID))
  message(FATAL_ERROR "Requires C_COMPILER(${CMAKE_C_COMPILER_ID}) == CXX_COMPILER(${CMAKE_CXX_COMPILER_ID})")
endif()

# ##############################################################################
# dirs  ========================================================================
# ------------------------------------------------------------------------------
set(prefix ${CMAKE_INSTALL_PREFIX})
set(exec_prefix "\${prefix}")
set(libdir "\${exec_prefix}/lib")
set(includedir "\${prefix}/include")
# ------------------------------------------------------------------------------
set(OBORO_INCLUDE_DIRS "")
list(APPEND OBORO_INCLUDE_DIRS  ${CMAKE_CURRENT_BINARY_DIR})
list(APPEND OBORO_INCLUDE_DIRS  ${abs_top_srcdir}/include)
# ------------------------------------------------------------------------------
set(OBORO_LIBRARY_DIRS "")
list(APPEND OBORO_LIBRARY_DIRS  ${CMAKE_CURRENT_BINARY_DIR}/src)
# ------------------------------------------------------------------------------
set(OBORO_LIBRARIES "")
# ##############################################################################
# libraries  ===================================================================
# lua --------------------------------------------------------------------------
find_package(Lua51 REQUIRED)
list(APPEND OBORO_INCLUDE_DIRS  ${LUA_INCLUDE_DIR})
list(APPEND OBORO_LIBRARY_DIRS  ${LUA_LIBRARY_DIR})
list(APPEND OBORO_LIBRARIES     ${LUA_LIBRARIES})
# boost  -----------------------------------------------------------------------
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.56.0 REQUIRED COMPONENTS)
list(APPEND OBORO_INCLUDE_DIRS  ${Boost_INCLUDE_DIR})
list(APPEND OBORO_LIBRARY_DIRS  ${Boost_LIBRARY_DIR})
# ltdl  ------------------------------------------------------------------------
find_path(LTDL_INCLUDE_DIR ltdl.h)
find_library(LTDL_LIBRARIES NAMES ltdl)
list(APPEND OBORO_INCLUDE_DIRS  ${LTDL_INCLUDE_DIR})
list(APPEND OBORO_LIBRARY_DIRS  ${LTDL_LIBRARY_DIR})
list(APPEND OBORO_LIBRARIES     ${LTDL_LIBRARIES})
list(APPEND OBORO_LIBRARIES     ${CMAKE_DL_LIBS})
# Thread  ----------------------------------------------------------------------
set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads)
set(OBORO_THREAD_LIBS           ${CMAKE_THREAD_LIBS_INIT})
list(APPEND OBORO_LIBRARIES     ${CMAKE_THREAD_LIBS_INIT})
# ##############################################################################
# dirs cleanup  ================================================================
# ------------------------------------------------------------------------------
list(REMOVE_DUPLICATES  OBORO_INCLUDE_DIRS)
list(REMOVE_ITEM        OBORO_INCLUDE_DIRS "")
# -----------------------------------------------------------------------------
list(REMOVE_DUPLICATES  OBORO_LIBRARY_DIRS)
list(REMOVE_ITEM        OBORO_LIBRARY_DIRS "")
# ------------------------------------------------------------------------------
list(REMOVE_DUPLICATES OBORO_LIBRARIES)
list(REMOVE_ITEM        OBORO_LIBRARIES "")
# ##############################################################################
# extra  =======================================================================
# ------------------------------------------------------------------------------
configure_file(${abs_top_srcdir}/config.h.cmake config.h @ONLY)
configure_file(${abs_top_srcdir}/oboro.pc.in oboro.pc @ONLY)
configure_file(${abs_top_srcdir}/Doxyfile.in Doxyfile @ONLY)
# ##############################################################################
# uninstall  ===================================================================
# ------------------------------------------------------------------------------
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in cmake_uninstall.cmake
  IMMEDIATE @ONLY
  )
add_custom_target(uninstall
  ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
  )
# ##############################################################################
# pkgconfig  ===================================================================
# ------------------------------------------------------------------------------
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/oboro.pc
  DESTINATION lib/pkgconfig)
# ##############################################################################
# test  ========================================================================
# ------------------------------------------------------------------------------
if(OBORO_ENABLE_TEST)
  # ============================================================================
  # ----------------------------------------------------------------------------
  enable_testing()
  # checks  ====================================================================
  # splint  --------------------------------------------------------------------
  find_program(SPLINT splint)
  if(NOT SPLINT)
    message(FATAL_ERROR "Test feature requires splint.")
  endif()
  message(STATUS "${SPLINT}")
  configure_file(${abs_top_srcdir}/tools/et-splint/splint.sh.in
    tools/et-splint/splint.sh @ONLY)
  set(SPLINT_FLAGS "")
  set(SPLINT_FLAGS "${SPLINT_FLAGS} -DOBORO_EXPORTS")
  foreach(loop_var IN LISTS OBORO_INCLUDE_DIRS)
    set(SPLINT_FLAGS "${SPLINT_FLAGS} -I ${loop_var}")
  endforeach()
  set(SPLINT_SH /bin/env sh ${CMAKE_CURRENT_BINARY_DIR}/tools/et-splint/splint.sh
   )
  # cpplint  -------------------------------------------------------------------
  find_program(PYTHON python)
  if(NOT PYTHON)
    message(FATAL_ERROR "Test feature requires python.")
  endif()
  message(STATUS "${PYTHON}")
  configure_file(${abs_top_srcdir}/tools/et-cpplint/cpplint.sh.in
    tools/et-cpplint/cpplint.sh @ONLY)
  set(CPPLINT "python ${abs_top_srcdir}/tools/et-cpplint/cpplint.py"
   )
  set(CPPLINT_FLAGS "")
  set(CPPLINT_SH /bin/env sh ${CMAKE_CURRENT_BINARY_DIR}/tools/et-cpplint/cpplint.sh
   )
  # LD_LIBRARY_PATH  -----------------------------------------------------------
  set(LD_LIBRARY_PATH "")
  foreach(loop_var IN LISTS OBORO_LIBRARY_DIRS)
    set(LD_LIBRARY_PATH "${LD_LIBRARY_PATH}:${loop_var}")
  endforeach()
  # environment  ---------------------------------------------------------------
  set(TEST_ENV "")
  list(APPEND TEST_ENV "LD_LIBRARY_PATH=${LD_LIBRARY_PATH}")
  list(APPEND TEST_ENV "TOP_SRCDIR=${abs_top_srcdir}")
  list(APPEND TEST_ENV "TOP_BUILDDIR=${CMAKE_CURRENT_BINARY_DIR}")
  list(APPEND TEST_ENV "SPLINT=${SPLINT} ${SPLINT_FLAGS} -DOBORO_EXPORTS")
  list(APPEND TEST_ENV "CPPLINT=${CPPLINT} ${CPPLINT_FLAGS}")
endif()
# ##############################################################################
# subdirectory  ================================================================
# ------------------------------------------------------------------------------
add_subdirectory(include)
add_subdirectory(src)
#add_subdirectory(example)
add_subdirectory(test)

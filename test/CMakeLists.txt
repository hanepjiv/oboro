# =============================================================================
# settings --------------------------------------------------------------------
add_definitions(-DHAVE_CONFIG_H)
include_directories(${OBORO_INCLUDE_DIRS})
link_directories(${OBORO_LIBRARY_DIRS})
# =============================================================================
# tests -----------------------------------------------------------------------
if(OBORO_ENABLE_TEST)
  # ---------------------------------------------------------------------------
  set(OBORO_TEST_TEST_EXE)
  # splint  -------------------------------------------------------------------
  if(SPLINT)
    add_test(test-splint ${SPLINT_SH})
    list(APPEND OBORO_TEST_TEST_EXE test-splint)
  endif()
  # cpplint  ------------------------------------------------------------------
  if(PYTHON)
    add_test(test-cpplint ${CPPLINT_SH})
    list(APPEND OBORO_TEST_TEST_EXE test-cpplint)
  endif()
  # ---------------------------------------------------------------------------
  set(test00_SOURCES
    test00.cc
    )
  add_executable(test00 ${test00_SOURCES})
  target_link_libraries(test00 ${OBORO_LIBRARIES})
  set_target_properties(test00
    PROPERTIES
    COMPILE_FLAGS "-fPIE -DPIC -DPIE ${OBORO_CXX_FLAGS}"
    )
  add_test(test-test00 test00)
  list(APPEND OBORO_TEST_TEST_EXE test-test00)
  # ---------------------------------------------------------------------------
  set(test01_SOURCES
    test01.cc
    )
  add_executable(test01 ${test01_SOURCES})
  target_link_libraries(test01 ${OBORO_LIBRARIES})
  set_target_properties(test01
    PROPERTIES
    COMPILE_FLAGS "-fPIE -DPIC -DPIE ${OBORO_CXX_FLAGS}"
    )
  add_test(test-test01 test01)
  list(APPEND OBORO_TEST_TEST_EXE test-test01)
  # environment  --------------------------------------------------------------
  set(TEST_ENV_ "${TEST_ENV}")
  list(APPEND TEST_ENV_ "SRCDIR=${CMAKE_CURRENT_SOURCE_DIR}")
  list(APPEND TEST_ENV_ "BUILDDIR=${CMAKE_CURRENT_BINARY_DIR}")
  set_tests_properties(${OBORO_TEST_TEST_EXE}
    PROPERTIES ENVIRONMENT "${TEST_ENV_}")
endif()

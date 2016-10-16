# #############################################################################
# subdirectory ================================================================
# -----------------------------------------------------------------------------
add_subdirectory(oboro)
# =============================================================================
# tests  ----------------------------------------------------------------------
if(OBORO_ENABLE_TEST)
  # ---------------------------------------------------------------------------
  set(OBORO_INCLUDE_TEST_EXE)
  # splint  -------------------------------------------------------------------
  if(SPLINT)
    add_test(include-splint ${SPLINT_SH})
    list(APPEND OBORO_INCLUDE_TEST_EXE include-splint)
  endif()
  # cpplint  ------------------------------------------------------------------
  if(PYTHON)
    add_test(include-cpplint ${CPPLINT_SH})
    list(APPEND OBORO_INCLUDE_TEST_EXE include-cpplint)
  endif()
  # environment  --------------------------------------------------------------
  set(TEST_ENV_ "${TEST_ENV}")
  list(APPEND TEST_ENV_ "INCLUDEDIR=${CMAKE_CURRENT_SOURCE_DIR}")
  list(APPEND TEST_ENV_ "BUILDDIR=${CMAKE_CURRENT_BINARY_DIR}")
  set_tests_properties(${OBORO_INCLUDE_TEST_EXE}
    PROPERTIES ENVIRONMENT "${TEST_ENV_}")
endif()

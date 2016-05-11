# ##############################################################################
# subdirectory =================================================================
# ------------------------------------------------------------------------------

# ==============================================================================
# oboro ------------------------------------------------------------------------
file(RELATIVE_PATH OBORO_INCLUDE_OBORO_DEST
  ${abs_top_srcdir} ${CMAKE_CURRENT_SOURCE_DIR})
install(FILES
  begin.h

  debug.h

  initializer.hpp
  oboro.hpp
  module.hpp
  function.hpp

  DESTINATION ${OBORO_INCLUDE_OBORO_DEST})

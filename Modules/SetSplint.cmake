find_program(SPLINT splint)
if(NOT SPLINT)
  message(FATAL_ERROR "requires splint.")
endif()
foreach(loop_var ${SPLINT_INCLUDE_DIRS})
  list(APPEND SPLINT_FLAGS "-I ${loop_var}")
endforeach()
list(JOIN SPLINT_FLAGS " " SPLINT_FLAGS_STR)
set(SPLINT_SH "${PROJECT_BINARY_DIR}/splint.sh")
file(WRITE ${SPLINT_SH}
  "#!/bin/env sh\n"
  "find \$1 -type f \\( -name *.c \\) -exec "
  "${SPLINT} ${SPLINT_FLAGS_STR} {} +\n"
  "exit $?\n\n"
)
file(CHMOD ${SPLINT_SH} PERMISSIONS
  OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_WRITE GROUP_EXECUTE
)

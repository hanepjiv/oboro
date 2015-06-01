#						-*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# ==============================================================================
# version info
define([CURRENT],	[0])
define([REVISION],	[0])
define([AGE],		[0])
define([MAJOR],		[m4_eval(CURRENT-AGE)])
# ==============================================================================
AC_PREREQ([2.69])
AC_INIT([oboro],
	[MAJOR.AGE.REVISION],
	[hanepjiv <hanepjiv@gmail.com>])

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])

AC_CANONICAL_SYSTEM
# ==============================================================================
# automake
AM_INIT_AUTOMAKE([1.13.4 foreign -Wall])
# ==============================================================================
# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AM_PROG_AR
# ==============================================================================
# Checks for libraries.
# ------------------------------------------------------------------------------
# pthread
AX_PTHREAD
# ------------------------------------------------------------------------------
# libtool
LT_PREREQ([2.4.6])
LT_CONFIG_LTDL_DIR([libltdl])
LT_INIT([static shared win32-dll dlopen])
LTDL_INIT
# ------------------------------------------------------------------------------
# lua
AX_PROG_LUA(
	[5.1], [5.4],
	[],
	[AC_MSG_ERROR([*** Lua not found!])])
AX_LUA_HEADERS(
	[],
	[AC_MSG_ERROR([*** Lua not found!])])
AX_LUA_LIBS(
	[],
	[AC_MSG_ERROR([*** Lua not found!])])
#AX_LUA_READLINE([ACTION-IF-FOUND], [ACTION-IF-NOT-FOUND])
# ==============================================================================
# Checks for header files.

# ==============================================================================
# Checks for typedefs, structures, and compiler characteristics.

# ==============================================================================
# Checks for library functions.

# ==============================================================================
# define oboro
OBORO_PACKAGE="${PACKAGE}"
OBORO_RELEASE="indir([MAJOR]).indir([AGE]).indir([REVISION])"
OBORO_VERSION_INFO="indir([CURRENT]):indir([REVISION]):indir([AGE])"
OBORO_CPPFLAGS=
OBORO_C_CXX_FLAGS="\
	-pipe -fPIC -DPIC -D_REENTRANT -D_THREAD_SAFE \
	-fno-asm -fno-builtin -fvisibility=hidden -fstrict-aliasing -pedantic \
	-Werror -W -Wall -Wextra -Wstrict-aliasing=1 -Wformat=2 -Wundef \
	-Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings \
	-Wno-missing-field-initializers -Wno-sign-compare -Wconversion \
	-Wfloat-equal -Wredundant-decls -Wno-unused-parameter -Wunused-result \
	-Wmissing-declarations -Wsign-compare \
	"
OBORO_CFLAGS="\
	${OBORO_C_CXX_FLAGS} \
	${PTHREAD_CFLAGS} \
	-std=c99 \
	-Wbad-function-cast -Wstrict-prototypes -Wold-style-definition \
	-Wmissing-prototypes -Wnested-externs -Wdeclaration-after-statement \
	"
OBORO_CXXFLAGS="\
	${OBORO_C_CXX_FLAGS} \
	-std=c++11 \
	-fvisibility-inlines-hidden -fthreadsafe-statics \
	-Weffc++ -Woverloaded-virtual -Wsign-promo -Wsynth \
	"
OBORO_THREAD_LIBS=${PTHREAD_LIBS}
OBORO_LDFLAGS=${OBORO_THREAD_LIBS}
# ==============================================================================
# Checks for debug mode
AC_MSG_CHECKING([for debug mode])
AC_ARG_ENABLE([debug],
	[  --enable-debug	turn on debug mode. default=no],
	[case "${enableval}" in
	  yes) enable_debug=yes ;;
	  no)  enable_debug=no ;;
	  *)   AC_MSG_ERROR(bad value ${enableval} for --enable-debug) ;;
	 esac],
	[enable_debug=no])
if test "x$enable_debug" = "xyes"; then
	mydebugopt="\
		-g -gstabs -pg \
		-pedantic-errors \
		-Wall -Wextra -Wformat=2 -Wundef -Wshadow -Wpointer-arith \
		-Wcast-qual -Wcast-align -Wwrite-strings \
		-Wno-missing-field-initializers -Wno-sign-compare -Wpadded \
		-Wconversion -Wfloat-equal \
		-Wredundant-decls -Winline \
		-Wno-unused-parameter -Wmissing-declarations -Wsign-compare \
		-Wstrict-aliasing=1 \
		"
	OBORO_CPPFLAGS="\
		${OBORO_CPPFLAGS} -DDEBUG -DOBORO_DEBUG \
		"
	OBORO_CFLAGS="\
		${OBORO_CFLAGS} ${mydebugopt} \
		-Wbad-function-cast -Wstrict-prototypes \
		-Wold-style-definition -Wmissing-prototypes \
		-Wnested-externs -Wdeclaration-after-statement \
		"
	OBORO_CXXFLAGS="\
		${OBORO_CXXFLAGS} ${mydebugopt} \
		-Weffc++ -Woverloaded-virtual -Wsign-promo -Wsynth \
		"
	OBORO_LDFLAGS="\
		-pg \
		"
else
	myopt="\
		-fomit-frame-pointer \
		"
	OBORO_CPPFLAGS="${OBORO_CPPFLAGS} -DNDEBUG"
	OBORO_CFLAGS="${OBORO_CFLAGS} ${myopt}"
	OBORO_CXXFLAGS="${OBORO_CXXFLAGS} ${myopt}"
fi
AC_MSG_RESULT([$enable_debug])
AM_CONDITIONAL(DEBUG, test x$enable_debug = xyes)
# ==============================================================================
# Checks for test
AC_MSG_CHECKING([for test])
AC_ARG_ENABLE([test],
	[  --enable-test	turn on test. default=no],
	[case "${enableval}" in
	  yes) enable_test=yes ;;
	  no)  enable_test=no ;;
	  *)   AC_MSG_ERROR(bad value ${enableval} for --enable-test) ;;
	 esac],
	[enable_test=no])
if test "x$enable_test" = "xyes"; then
   AC_CHECK_PROG(SPLINT, [splint], [splint])
   AC_CHECK_PROG(PYTHON2, [python2], [python2])
fi
AC_MSG_RESULT([$enable_test])
AM_CONDITIONAL(TEST, test x$enable_test = xyes)
# ==============================================================================
# export
AC_SUBST(OBORO_PACKAGE)
AC_SUBST(OBORO_RELEASE)
AC_SUBST(OBORO_VERSION_INFO)

AC_SUBST(OBORO_CPPFLAGS)
AC_SUBST(OBORO_CFLAGS)
AC_SUBST(OBORO_CXXFLAGS)
AC_SUBST(OBORO_THREAD_LIBS)
AC_SUBST(OBORO_LDFLAGS)

AC_CONFIG_FILES([
	oboro.pc
	Makefile
	include/Makefile
	src/Makefile
	test/Makefile
	tools/et-splint/splint.sh
	tools/et-cpplint/cpplint.sh
	],
	[
	chmod ug+x tools/et-splint/splint.sh
	chmod ug+x tools/et-cpplint/cpplint.sh
	])
AC_CONFIG_SUBDIRS([
	])
# ==============================================================================
AC_OUTPUT

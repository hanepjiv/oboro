# /////////////////////////////////////////////////////////////////////////////
AM_CPPFLAGS=\
	${OBORO_CPPFLAGS} \
	${LTDLINCL} \
	-I$(top_builddir) \
	-I$(top_srcdir)/include
AM_CFLAGS=${OBORO_CFLAGS}
AM_CXXFLAGS=${OBORO_CXXFLAGS}
AM_LDFLAGS=\
	${OBORO_LDFLAGS} \
	-L$(top_builddir)/src
# /////////////////////////////////////////////////////////////////////////////
if TEST
check_PROGRAMS=
check_SCRIPTS=
# -----------------------------------------------------------------------------
TESTS_ENVIRONMENT=\
	LD_LIBRARY_PATH=@top_builddir@/src \
	TOP_BUILDDIR=@top_builddir@ \
	BUILDDIR=@builddir@ \
	TOP_SRCDIR=@top_srcdir@ \
	SRCDIR=@srcdir@ \
	SPLINT="${SPLINT}" \
	CPPLINT="${PYTHON} @top_srcdir@/tools/et-cpplint/cpplint.py"
TESTS=
# -----------------------------------------------------------------------------
check_PROGRAMS+=test00
test00_SOURCES=test00.cc
test00_DEPENDENCIES=${LTDLDEPS} ${top_builddir}/src/liboboro.la
test00_LDADD=\
	${OBORO_THREAD_LIBS} \
	${LIBLTDL} \
	${LUA_LIB} \
	${top_builddir}/src/liboboro.la
# -----------------------------------------------------------------------------
check_PROGRAMS+=test01
test01_SOURCES=test01.cc
test01_DEPENDENCIES=${LTDLDEPS} ${top_builddir}/src/liboboro.la
test01_LDADD=\
	${OBORO_THREAD_LIBS} \
	${LIBLTDL} \
	${LUA_LIB} \
	${top_builddir}/src/liboboro.la
# -----------------------------------------------------------------------------
@top_builddir@/tools/et-splint/splint.sh: @top_srcdir@/tools/et-splint/splint.sh.in @top_builddir@/Makefile Makefile
	cd @top_builddir@ && /bin/sh ./config.status tools/et-splint/splint.sh
@top_builddir@/tools/et-cpplint/cpplint.sh: @top_srcdir@/tools/et-cpplint/cpplint.sh.in @top_builddir@/Makefile Makefile
	cd @top_builddir@ && /bin/sh ./config.status tools/et-cpplint/cpplint.sh
# -----------------------------------------------------------------------------
check_SCRIPTS+=@top_builddir@/tools/et-splint/splint.sh
check_SCRIPTS+=@top_builddir@/tools/et-cpplint/cpplint.sh
# -----------------------------------------------------------------------------
TESTS+=${check_PROGRAMS} ${check_SCRIPTS}
endif

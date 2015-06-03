# //////////////////////////////////////////////////////////////////////////////
AM_CPPFLAGS=\
	${OBORO_CPPFLAGS} \
	${LTDLINCL} \
	-I$(top_builddir) \
	-I$(top_srcdir)/include
AM_CFLAGS=\
	${OBORO_CFLAGS} \
	${PTHREAD_CFLAGS}
AM_CXXFLAGS=${OBORO_CXXFLAGS}
AM_LDFLAGS=\
	${OBORO_LDFLAGS} \
	-L$(top_builddir)/src
# //////////////////////////////////////////////////////////////////////////////
if TEST
check_PROGRAMS=
check_SCRIPTS=
# ------------------------------------------------------------------------------
TESTS_ENVIRONMENT=\
	LD_LIBRARY_PATH=@top_builddir@/src \
	TOP_BUILDDIR=@top_builddir@ \
	BUILDDIR=@builddir@ \
	TOP_SRCDIR=@top_srcdir@ \
	SRCDIR=@srcdir@ \
	SPLINT="${SPLINT}" \
	CPPLINT="${PYTHON2} @top_srcdir@/tools/et-cpplint/cpplint.py"
TESTS=
# ------------------------------------------------------------------------------
check_PROGRAMS+=test00
test00_SOURCES=test00.cc
test00_DEPENDENCIES=${LTDLDEPS} ${top_builddir}/src/liboboro.la
test00_LDADD=\
	${PTHREAD_LIBS} \
	${LIBLTDL} \
	${LUA_LIB} \
	${top_builddir}/src/liboboro.la
# ------------------------------------------------------------------------------
check_PROGRAMS+=test01
test01_SOURCES=test01.cc
test01_DEPENDENCIES=${LTDLDEPS} ${top_builddir}/src/liboboro.la
test01_LDADD=\
	${PTHREAD_LIBS} \
	${LIBLTDL} \
	${BOOST_UNIT_TEST_FRAMEWORK_LIB} \
	${LUA_LIB} \
	${top_builddir}/src/liboboro.la
# ------------------------------------------------------------------------------
check_SCRIPTS+=@top_builddir@/tools/et-splint/splint.sh
check_SCRIPTS+=@top_builddir@/tools/et-cpplint/cpplint.sh
# ------------------------------------------------------------------------------
TESTS+=${check_PROGRAMS} ${check_SCRIPTS}
endif

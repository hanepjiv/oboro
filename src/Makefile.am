# //////////////////////////////////////////////////////////////////////////////
AM_CPPFLAGS=\
	${OBORO_CPPFLAGS} \
	${LTDLINCL} \
	-I$(top_builddir) \
	-I$(top_srcdir)/include
AM_CFLAGS=${OBORO_CFLAGS}
AM_CXXFLAGS=${OBORO_CXXFLAGS}
AM_LDFLAGS=${OBORO_LDFLAGS} -L$(top_builddir)/src
# //////////////////////////////////////////////////////////////////////////////
bin_PROGRAMS=
noinst_PROGRAMS=
# ==============================================================================
lib_LTLIBRARIES=
noinst_LTLIBRARIES=
check_LTLIBRARIES=
EXTRA_LTLIBRARIES=
# ==============================================================================
lib_LTLIBRARIES+=liboboro.la
liboboro_la_CPPFLAGS=${AM_CPPFLAGS} -DOBORO_EXPORTS
liboboro_la_SOURCES=\
	@top_srcdir@/include/oboro/oboro.hh \
	oboro.cc
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
@top_builddir@/tools/et-splint/splint.sh: @top_srcdir@/tools/et-splint/splint.sh.in @top_builddir@/Makefile Makefile
	cd @top_builddir@ && /bin/sh ./config.status tools/et-splint/splint.sh
@top_builddir@/tools/et-cpplint/cpplint.sh: @top_srcdir@/tools/et-cpplint/cpplint.sh.in @top_builddir@/Makefile Makefile
	cd @top_builddir@ && /bin/sh ./config.status tools/et-cpplint/cpplint.sh
# ------------------------------------------------------------------------------
check_SCRIPTS+=@top_builddir@/tools/et-splint/splint.sh
check_SCRIPTS+=@top_builddir@/tools/et-cpplint/cpplint.sh
# ------------------------------------------------------------------------------
TESTS+=${check_PROGRAMS} ${check_SCRIPTS}
endif

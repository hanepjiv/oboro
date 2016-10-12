nobase_include_HEADERS=\
	oboro/declspec.h \
	oboro/call.h \
	oboro/begin.h \
	oboro/debug.h \
	oboro/initializer.hpp \
	oboro/oboro.hpp \
	oboro/module.hpp \
	oboro/function.hpp \
	oboro/oboro.hh
# //////////////////////////////////////////////////////////////////////////////
if TEST
check_PROGRAMS=
check_SCRIPTS=
# ------------------------------------------------------------------------------
TESTS_ENVIRONMENT=\
	LD_LIBRARY_PATH=@top_builddir@/src \
	TOP_BUILDDIR=@top_builddir@ \
	BUILDDIR=@builddir@/oboro \
	TOP_SRCDIR=@top_srcdir@ \
	SRCDIR=@srcdir@/oboro \
	SPLINT="${SPLINT}" \
	CPPLINT="${PYTHON} @top_srcdir@/tools/et-cpplint/cpplint.py"
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

AC_INIT([libsirocco], [2.0.2], [mmarco@unizar.es])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall])
AM_PROG_AR
AC_PROG_CXX
LT_INIT([shared win32-dll])
AC_CANONICAL_HOST
AS_CASE([$host_os], [*cygwin* | *mingw*], [SIROCCO_LDFLAGS=-no-undefined])
AC_SUBST(SIROCCO_LDFLAGS)
AC_CONFIG_FILES([Makefile lib/Makefile tests/Makefile])
AC_OUTPUT

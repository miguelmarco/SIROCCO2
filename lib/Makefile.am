lib_LTLIBRARIES = libsirocco.la
libsirocco_la_SOURCES = icomplex.cpp  interval.cpp $(top_srcdir)/include/list.hpp $(top_srcdir)/include/mp_complex.hpp $(top_srcdir)/include/mp_icomplex.hpp $(top_srcdir)/include/mp_interval.hpp $(top_srcdir)/include/polynomial.hpp $(top_srcdir)/include/sirocco.hpp $(top_srcdir)/include/icomplex.hpp $(top_srcdir)/include/interval.hpp mp_complex.cpp mp_icomplex.cpp mp_interval.cpp polynomial.cpp sirocco.cpp
libsirocco_la_LDFLAGS = $(SIROCCO_LDFLAGS) -lm -lmpfr -lgmp
AM_CPPFLAGS = -I$(top_srcdir)/include
include_HEADERS = $(top_srcdir)/include/sirocco.h

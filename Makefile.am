SUBDIRS = lib tests
ACLOCAL_AMFLAGS = -I m4
pkgconfig_DATA = libsirocco.pc
dist-hook:
	cp README.md $(distdir)
	cp ZVK.py $(distdir)
	cp sage-sirocco_interface.pyx $(distdir)
	cp LICENSE $(distdir)

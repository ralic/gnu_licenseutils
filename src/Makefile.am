# Copyright (C) 2013 Ben Asselstine
# 
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.
localedir = $(datadir)/locale
bin_SCRIPTS=lush
bin_PROGRAMS=licensing
pkglibexec_SCRIPTS=preview new-boilerplate
DEFS += -DLOCALEDIR=\"$(localedir)\" -DPROGRAM=\"$(PROGRAM)\" -DPKGLIBEXECDIR=\"$(pkglibexecdir)\" -DINTERPRETER=\"$(INTERPRETER)\" -DINTERPRETER_PATH=\"$(bindir)/$(INTERPRETER)\" @DEFS@
AM_CPPFLAGS = -I$(top_srcdir)/lib -I$(top_builddir)/lib
lib_LTLIBRARIES=liblicenseutils.la 

pkginclude_HEADERS=licensing.h gpl.h lgpl.h agpl.h fdl.h boilerplate.h  help.h \
		   warranty.h welcome.h copyright.h cbb.h comment.h \
		   uncomment.h choose.h top.h project.h apply.h \
		   all-permissive.h bsd.h apache.h mit.h extra.h \ 
		   png-boilerplate.h png-apply.h isc.h prepend.h

liblicenseutils_la_SOURCES=licensing.c gettext-more.h licensing_priv.h \
                     gpl.c lgpl.c agpl.c fdl.c boilerplate.c help.c \
		     warranty.c  welcome.c util.c util.h copyright.c \
		     cbb.c comment.c uncomment.c choose.c top.c project.c \
		     apply.c all-permissive.c bsd.c apache.c mit.c extra.c \
		     png-boilerplate.c png-apply.c isc.c styles.c styles.h \
		     comment-style.h prepend.c
include styles.am

liblicenseutils_la_LIBADD = @LIBINTL@ $(top_builddir)/lib/libgnu.la $(GLIB_LIBS) $(LIBPNG_LIBS)
liblicenseutils_la_LDFLAGS = -version-info 0:0:0 -export-dynamic -no-undefined

licensing_SOURCES=main.c opts.c opts.h 

licensing_LDADD=liblicenseutils.la

LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck

AM_CFLAGS=-Wall $(GLIB_CFLAGS) $(LIBPNG_CFLAGS)
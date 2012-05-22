

AM_CFLAGS = \
	-I$(top_srcdir)/src \
	-I$(top_srcdir)/src/omap4plus \
	-I$(top_builddir)/src/omap4plus

AM_LDFLAGS = $(NODELETE_LDFLAGS)


MODULE_LDFLAGS = $(AM_LDFLAGS) -module -disable-static -avoid-version $(LDFLAGS_NOUNDEFINED)


bin_PROGRAMS = socfw

socfw_SOURCES = socfw.c socfw.h

socfw_CFLAGS = $(AM_CFLAGS) $(CAP_CFLAGS)


modlibexecdir = $(libdir)/plugins

modlibexec_LTLIBRARIES = \
		abe-dl1dl2-twl6040.la


OMAP4CFLAGS = -I $(LINUX_DIR)/sound/soc/omap/abe

abe_dl1dl2_twl6040_la_SOURCES = omap4plus/dapm/abe-dl1dl2-twl6040.c
abe_dl1dl2_twl6040_la_LDFLAGS = $(MODULE_LDFLAGS)
abe_dl1dl2_twl6040_la_LIBADD = $(MODULE_LIBADD)
abe_dl1dl2_twl6040_la_CFLAGS = $(AM_CFLAGS) $(OMAP4CFLAGS)


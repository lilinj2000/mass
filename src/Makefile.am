AUTOMAKE_OPTIONS = foreign

SUBDIRS = mdflow

bin_PROGRAMS = mass
mass_SOURCES = \
	Config.cc \
	Server.cc \
	Main.cc 

mass_CPPFLAGS = -I$(top_srcdir) \
		$(BOOST_CPPFLAGS) \
		$(SOIL_CPPFLAGS) \
		$(CATA_CPPFLAGS) \
		$(ZOD_CPPFLAGS) \
		$(CPPDB_CPPFLAGS)


mass_LDADD = \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(CATA_LIBADD) \
	$(ZOD_LIBADD) \
	$(CPPDB_LIBADD)


mass_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = Config.hh \
		Log.hh \
		Server.hh


EXTRA_DIST = env.sh mass.cfg log.cfg

massdir = $(bindir)
mass_DATA = $(EXTRA_DIST)

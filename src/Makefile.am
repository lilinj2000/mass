AUTOMAKE_OPTIONS = foreign

SUBDIRS = mdflow

bin_PROGRAMS = mass
mass_SOURCES = \
	Options.cc \
	Server.cc \
	Main.cc 

mass_CPPFLAGS = -I$(top_srcdir) \
		$(BOOST_CPPFLAGS) \
		$(SOIL_CPPFLAGS) \
		$(CATA_CPPFLAGS) \
		$(RAPIDJSON_CPPFLAGS) \
		$(FMT_CPPFLAGS) \
		$(SPDLOG_CPPFLAGS) \
		$(ZOD_CPPFLAGS) \
		$(ARGS_CPPFLAGS) \
		$(READERWRITERQUEUE_CPPFLAGS)


mass_LDADD = \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(CATA_LIBADD) \
	$(ZOD_LIBADD)


mass_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = \
		Options.hh \
		Server.hh


EXTRA_DIST = env.sh mass.json

massdir = $(bindir)
mass_DATA = $(EXTRA_DIST)

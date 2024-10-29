AUTOMAKE_OPTIONS = foreign

include_HEADERS = ina219.h

# Shared lib
lib_LTLIBRARIES = libcursensor.la

# Static lib
lib_LIBRARIES = libcursensor.a

SOURCES = \
    ina219.c

libcursensor_la_SOURCES = $(SOURCES)
libcursensor_a_SOURCES = $(SOURCES)

libcursensor_la_CFLAGS = -Wall -Werror -fPIC
libcursensor_la_LDFLAGS = -shared

libcursensor_a_CFLAGS = -Wall -Werror -fPIC
libcursensor_a_LDFLAGS = -static
ACLOCAL_AMFLAGS = -I m4

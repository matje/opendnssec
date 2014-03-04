MAINTAINERCLEANFILES = $(srcdir)/Makefile.in

LIBHSM = ${top_builddir}/libhsm/src/lib/libhsm.a
LIBCOMPAT = ${top_builddir}/common/libcompat.a

AM_CPPFLAGS = \
	-I$(top_srcdir)/common \
	-I$(top_builddir)/common \
	-I$(top_srcdir)/libhsm/src/lib \
	@SSL_INCLUDES@ \
	@XML2_INCLUDES@ \
	@LDNS_INCLUDES@

signzonedir =     @libdir@/opendnssec/signzone

sbin_PROGRAMS = ods-signzone
# man8_MANS =     man/ods-signzone.8

ods_signzone_SOURCES=		ods-signzone.c

ods_signzone_LDADD=		$(LIBHSM)
ods_signzone_LDADD+=		$(LIBCOMPAT)
ods_signzone_LDADD+=		@LDNS_LIBS@ @XML2_LIBS@ @PTHREAD_LIBS@ @RT_LIBS@ @SSL_LIBS@ @C_LIBS@

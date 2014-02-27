#!/usr/bin/env bash

#TEST: Start, sign a single zone with one repository, stop.
#TEST: On redhat, also perform basic validation of the zone with validns

# So we can use validns 0.7 it is installed from source so need to
# specify this path

case "$DISTRIBUTION" in
        redhat )
                append_path /usr/sbin
                ;;
esac

if [ -n "$HAVE_MYSQL" ]; then
        ods_setup_conf conf.xml conf-mysql.xml
fi &&

ods_reset_env &&

ods_start_ods-control &&

syslog_waitfor 60 'ods-signerd: .*\[STATS\] ods' &&
test -f "$INSTALL_ROOT/var/opendnssec/signed/ods" &&
# Testing OPENDNSSEC-549: Deal with Errata 3441 of RFC 5155
grep 'uf2mp408g1lut654h2l08fh1s8a5uq45\.ods\..*300.*IN.*NSEC3.*1.*1.*5.*-.*1o9gk9h0majtcvsj4i0uarbd3q7eq8ia' "$INSTALL_ROOT/var/opendnssec/signed/ods" &&
# Testing OPENDNSSEC-520: Make sure tabs in <character-strings> are not replaces with space
grep 'ods\..*600.*IN.*TXT.*"this		text	has	tabs"' "$INSTALL_ROOT/var/opendnssec/signed/ods" &&

# Validate the output on redhat
case "$DISTRIBUTION" in
        redhat )
                log_this validate-zone-ods validns -s -p all "$INSTALL_ROOT/var/opendnssec/signed/ods" &&
                log_grep validate-zone-ods stdout 'validation errors:   0'
                ;;
esac &&

ods_stop_ods-control &&
return 0

cat "$INSTALL_ROOT/var/opendnssec/signed/ods"
ods_kill
return 1

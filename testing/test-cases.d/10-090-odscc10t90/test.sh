#!/usr/bin/env bash
#
# Use correct PIN plus one additional character, expect failure

if [ -n "$HAVE_MYSQL" ]; then
	ods_setup_conf conf.xml conf-mysql.xml
fi &&

ods_reset_env &&

! log_this ods-hsmutil-purge ods-hsmutil purge SoftHSM  &&
log_grep ods-hsmutil-purge stderr 'Incorrect PIN for repository SoftHSM' &&

! log_this_timeout ods-control-enforcer-start 30 ods-control enforcer start &&
syslog_waitfor 10 'ods-enforcerd: .*Incorrect PIN for repository SoftHSM' &&

! log_this_timeout ods-control-signer-start 30 ods-control signer start &&
syslog_waitfor 10 'ods-signerd: .*\[engine\].*setup failed: HSM error' &&

! pgrep -u `id -u` '(ods-enforcerd|ods-signerd)' >/dev/null 2>/dev/null &&
return 0

ods_kill
return 1

# $Id$

AC_DEFUN([ACX_ENFORCER_DATABASE],[

	AC_ARG_WITH(enforcer-database,
        AC_HELP_STRING([--with-enforcer-database=BACKEND],
        	[Select database backend: sqlite3 (default), mysql]),
		[database_backend="${withval}"],
		[database_backend="sqlite3"])
	
	AC_ARG_WITH([enforcer-database-test-host],
		AC_HELP_STRING([--with-enforcer-database-test-host=HOST],
			[Host to use when testing the Enforcer database backend]),
		[database_host="${withval}"],
		[database_host=""]
		)
		
	AC_ARG_WITH([enforcer-database-test-port],
		AC_HELP_STRING([--with-enforcer-database-test-port=PORT],
			[Port to use when testing the Enforcer database backend]),
		[database_port="${withval}"],
		[database_port="0"]
		)
		
	AC_ARG_WITH([enforcer-database-test-database],
		AC_HELP_STRING([--with-enforcer-database-test-database=DATABASE],
			[Database to use when testing the Enforcer database backend]),
		[database_database="${withval}"],
		[database_database=""]
		)
		
	AC_ARG_WITH([enforcer-database-test-username],
		AC_HELP_STRING([--with-enforcer-database-test-username=USERNAME],
			[Username to use when testing the Enforcer database backend]),
		[database_username="${withval}"],
		[database_username=""]
		)
		
	AC_ARG_WITH([enforcer-database-test-password],
		AC_HELP_STRING([--with-enforcer-database-test-password=PASSWORD],
			[Password to use when testing the Enforcer database backend]),
		[database_password="${withval}"],
		[database_password=""]
		)

	AC_MSG_CHECKING(for database backend)

	if test "x${database_backend}" = "xsqlite3"; then
		AC_MSG_RESULT(SQLite3)

		ACX_SQLITE3

		ENFORCER_DB_INCLUDES=$SQLITE3_INCLUDES
		ENFORCER_DB_LIBS=$SQLITE3_LIBS

		AC_DEFINE_UNQUOTED(ENFORCER_DATABASE_SQLITE3, 1, [Using SQLite3 for database backend])

	elif test "x${database_backend}" = "xmysql"; then
		AC_MSG_RESULT(MySQL)

		AX_LIB_MYSQL(5.0.0)

		if test "$found_mysql" != "yes"; then
			AC_MSG_ERROR([MySQL is missing.])
		fi

		ENFORCER_DB_INCLUDES=$MYSQL_CFLAGS
		ENFORCER_DB_LIBS=$MYSQL_LDFLAGS

		AC_DEFINE_UNQUOTED(ENFORCER_DATABASE_MYSQL, 1, [Using MySQL for database backend])

	else
		AC_MSG_RESULT(Unknown)
		AC_MSG_ERROR([Database backend ${database_backend} not supported.])
	fi

	AC_SUBST(ENFORCER_DB_INCLUDES) 
	AC_SUBST(ENFORCER_DB_LIBS)
	
	AC_DEFINE_UNQUOTED(ENFORCER_DB_HOST, ["$database_host"], [Host to use when testing the Enforcer database backend])
	AC_DEFINE_UNQUOTED(ENFORCER_DB_PORT, [$database_port], [Port to use when testing the Enforcer database backend])
	AC_DEFINE_UNQUOTED(ENFORCER_DB_DATABASE, ["$database_database"], [Database to use when testing the Enforcer database backend])
	AC_DEFINE_UNQUOTED(ENFORCER_DB_USERNAME, ["$database_username"], [Username to use when testing the Enforcer database backend])
	AC_DEFINE_UNQUOTED(ENFORCER_DB_PASSWORD, ["$database_password"], [Password to use when testing the Enforcer database backend])
])

/*
 +----------------------------------------------------------------------+
 |  APM stands for Alternative PHP Monitor                              |
 +----------------------------------------------------------------------+
 | Copyright (c) 2008-2014  Davide Mendolia, Patrick Allaert            |
 +----------------------------------------------------------------------+
 | This source file is subject to version 3.01 of the PHP license,      |
 | that is bundled with this package in the file LICENSE, and is        |
 | available through the world-wide-web at the following url:           |
 | http://www.php.net/license/3_01.txt                                  |
 | If you did not receive a copy of the PHP license and are unable to   |
 | obtain it through the world-wide-web, please send a note to          |
 | license@php.net so we can mail you a copy immediately.               |
 +----------------------------------------------------------------------+
 | Authors: Patrick Allaert <patrickallaert@php.net>                    |
 +----------------------------------------------------------------------+
*/

#ifndef DRIVER_MYSQL_H
#define DRIVER_MYSQL_H

#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"

#define APM_E_mysql APM_E_ALL

#define MYSQL_INSTANCE_INIT_EX(ret) connection = mysql_get_instance(); \
	if (connection == NULL) { \
		return ret; \
	}
#define MYSQL_INSTANCE_INIT MYSQL_INSTANCE_INIT_EX()

apm_driver_entry * apm_driver_mysql_create();
void apm_driver_mysql_insert_request(TSRMLS_D);
void apm_driver_mysql_process_event(PROCESS_EVENT_ARGS);
void apm_driver_mysql_process_stats();
int apm_driver_mysql_minit(int);
int apm_driver_mysql_rinit();
int apm_driver_mysql_mshutdown();
int apm_driver_mysql_rshutdown();

/* Extension globals */
ZEND_BEGIN_MODULE_GLOBALS(apm_mysql)
	/* Boolean controlling whether the driver is active or not */
	zend_bool enabled;
	/* Boolean controlling the collection of stats */
	zend_bool stats_enabled;
	/* Control which exceptions to collect (0: none exceptions collected, 1: collect uncaught exceptions (default), 2: collect ALL exceptions) */
	long exception_mode;
	/* driver error reporting */
	int error_reporting;
	/* MySQL host */
	char *db_host;
	/* MySQL port */
	unsigned int db_port;
	/* MySQL user */
	char *db_user;
	/* MySQL password */
	char *db_pass;
	/* MySQL database */
	char *db_name;
	/* DB handle */
	MYSQL *event_db;
	/* Option to process silenced events */
	zend_bool process_silenced_events;

	/* Boolean to ensure request content is only inserted once */
	zend_bool is_request_created;
ZEND_END_MODULE_GLOBALS(apm_mysql)

#ifdef ZTS
#define APM_MY_G(v) TSRMG(apm_mysql_globals_id, zend_apm_mysql_globals *, v)
#else
#define APM_MY_G(v) (apm_mysql_globals.v)
#endif

#endif

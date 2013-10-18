/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2009 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Israel Ekpo <iekpo@php.net>                                  |
   +----------------------------------------------------------------------+
*/

/* $Id: solr_functions_debug.c 288601 2009-09-23 03:43:20Z iekpo $ */

#include "php_solr.h"

/* {{{ void solr_debug_printf(const char *format, ...) */
PHP_SOLR_API void solr_debug_printf(const char *format, ...)
{
#ifdef SOLR_DEBUG
	va_list args;
	va_start(args,format);
	vprintf(format,args);
	va_end(args);
#endif
}
/* }}} */

/* {{{ void solr_debug_print_fields(const solr_field_list_t *field_list) */
PHP_SOLR_API void solr_debug_print_fields(const solr_field_list_t *field_list)
{
	/* Used to debug field inserted */
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

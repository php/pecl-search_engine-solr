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

/* $Id: php_solr_exception.c 290121 2009-11-01 13:02:10Z iekpo $ */

#include "php_solr.h"

/* {{{ static void solr_prepare_internal_info(zval *objptr, zval *return_value TSRMLS_DC) */
static void solr_prepare_internal_info(zval *objptr, zval *return_value TSRMLS_DC)
{
	zval *line_no = zend_read_property(Z_OBJCE_P(objptr), objptr, SOLR_SOURCELINE_NO_PROPERTY_NAME, sizeof(SOLR_SOURCELINE_NO_PROPERTY_NAME)-1, 0 TSRMLS_CC);
	zval *solr_file = zend_read_property(Z_OBJCE_P(objptr), objptr, SOLR_SOURCEFILE_PROPERTY_NAME, sizeof(SOLR_SOURCEFILE_PROPERTY_NAME)-1, 0 TSRMLS_CC);
	zval *solr_zif_name = zend_read_property(Z_OBJCE_P(objptr), objptr, SOLR_ZIFNAME_PROPERTY_NAME, sizeof(SOLR_ZIFNAME_PROPERTY_NAME)-1, 0 TSRMLS_CC);
	long int source_line = Z_LVAL_P(line_no);
	char *solr_source_file = Z_STRVAL_P(solr_file);
	char *solr_zifname = Z_STRVAL_P(solr_zif_name);

	array_init(return_value);

	add_assoc_long(return_value, SOLR_SOURCELINE_NO_PROPERTY_NAME, source_line);
	add_assoc_string(return_value, SOLR_SOURCEFILE_PROPERTY_NAME, solr_source_file, 1);
	add_assoc_string(return_value, SOLR_ZIFNAME_PROPERTY_NAME, solr_zifname, 1);
}
/* }}} */

/* {{{ void solr_throw_exception_ex(zend_class_entry *exception_ce, long code TSRMLS_DC, const char *filename, int file_line, const char *function_name, char *format, ...) */
PHP_SOLR_API void solr_throw_exception_ex(zend_class_entry *exception_ce, long code TSRMLS_DC, const char *filename, int file_line, const char *function_name, char *format, ...)
{
	char *message = NULL;

	size_t max_buffer_len = 0;

	zval *objptr = NULL;

	va_list args;

	va_start(args,format);

	max_buffer_len = 2048; /* This should be sufficient to hold the buffer */

/* If this is PHP 5.2.x, since ap_php_vasprintf is only present in 5.3 */
#ifdef SOLR_ZEND_ENGINE_2_2

	/* Allocate max_buffer_len bytes to hold the buffer */
	message = (char *) malloc( sizeof(char) * max_buffer_len);

	memset(message, 0, sizeof(char) * max_buffer_len);

	ap_php_vslprintf(message, max_buffer_len, format, args);

#else
	/* Preparing the message string from the format and variable argument list, if any. */
	ap_php_vasprintf(&message, format, args);

#endif

	va_end(args);

	/* Retrieves the thrown object and updates the properties */
	objptr = zend_throw_exception(exception_ce, message, code TSRMLS_CC);

	/* This is the line number in the source file where it was thrown */
	zend_update_property_long(exception_ce, objptr, SOLR_SOURCELINE_NO_PROPERTY_NAME, sizeof(SOLR_SOURCELINE_NO_PROPERTY_NAME)-1, file_line TSRMLS_CC);

	/* This is the line source file where it was thrown */
	zend_update_property_string(exception_ce, objptr, SOLR_SOURCEFILE_PROPERTY_NAME, sizeof(SOLR_SOURCEFILE_PROPERTY_NAME)-1, (char *) filename TSRMLS_CC);

	/* This is the C function where it was thrown */
	zend_update_property_string(exception_ce, objptr, SOLR_ZIFNAME_PROPERTY_NAME, sizeof(SOLR_ZIFNAME_PROPERTY_NAME)-1, (char *) function_name TSRMLS_CC);

	/* message must be freed */
	if (message != NULL) {

		free(message);
	}
}
/* }}} */

/* {{{ void solr_throw_exception(zend_class_entry *exception_ce, char *message, long code TSRMLS_DC, const char *filename, int file_line, const char *function_name) */
PHP_SOLR_API void solr_throw_exception(zend_class_entry *exception_ce, char *message, long code TSRMLS_DC, const char *filename, int file_line, const char *function_name)
{
	/* Retrieves the thrown object and updates the properties */
	zval *objptr = zend_throw_exception(exception_ce, message, code TSRMLS_CC);

	/* This is the line number in the source file where it was thrown */
	zend_update_property_long(exception_ce, objptr, SOLR_SOURCELINE_NO_PROPERTY_NAME, sizeof(SOLR_SOURCELINE_NO_PROPERTY_NAME)-1, file_line TSRMLS_CC);

	/* This is the line source file where it was thrown */
	zend_update_property_string(exception_ce, objptr, SOLR_SOURCEFILE_PROPERTY_NAME, sizeof(SOLR_SOURCEFILE_PROPERTY_NAME)-1, (char *) filename TSRMLS_CC);

	/* This is the C function where it was thrown */
	zend_update_property_string(exception_ce, objptr, SOLR_ZIFNAME_PROPERTY_NAME, sizeof(SOLR_ZIFNAME_PROPERTY_NAME)-1, (char *) function_name TSRMLS_CC);
}
/* }}} */

/* Macro for preparing the return value array */
#define solr_exception_return_internal_info() { \
	if (return_value_used) {	\
		solr_prepare_internal_info(getThis(), return_value TSRMLS_CC);	\
	} else {	\
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Return value requested but output not processed."); \
	} \
}

/* {{{ proto array SolrException::getInternalInfo(void)
   Returns the internal API information where the exception was generated */
PHP_METHOD(SolrException, getInternalInfo)
{
	solr_exception_return_internal_info()
}
/* }}} */

/* {{{ proto array SolrClientException::getInternalInfo(void)
   Returns the internal API information where the exception was generated */
PHP_METHOD(SolrClientException, getInternalInfo)
{
	solr_exception_return_internal_info()
}
/* }}} */

/* {{{ proto array SolrIllegalOperationException::getInternalInfo(void)
   Returns the internal API information where the exception was generated */
PHP_METHOD(SolrIllegalOperationException, getInternalInfo)
{
	solr_exception_return_internal_info()
}
/* }}} */

/* {{{ proto array SolrIllegalArgumentException::getInternalInfo(void)
   Returns the internal API information where the exception was generated */
PHP_METHOD(SolrIllegalArgumentException, getInternalInfo)
{
	solr_exception_return_internal_info()
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

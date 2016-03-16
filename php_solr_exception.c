/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2015 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors:                                                             |
   |          Israel Ekpo <iekpo@php.net>                                 |
   |          Omar Shaban <omars@php.net>                                 |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#include "php_solr.h"

/* {{{ static void solr_prepare_internal_info(zval *object, zval *return_value TSRMLS_DC) */
static void solr_prepare_internal_info(zval *object, zval *return_value TSRMLS_DC)
{
    zval *rv = NULL;
	zval *line_no = zend_read_property(Z_OBJCE_P(object), object, SOLR_SOURCELINE_NO_PROPERTY_NAME, sizeof(SOLR_SOURCELINE_NO_PROPERTY_NAME)-1, 0, rv);
	zval *solr_file = zend_read_property(Z_OBJCE_P(object), object, SOLR_SOURCEFILE_PROPERTY_NAME, sizeof(SOLR_SOURCEFILE_PROPERTY_NAME)-1, 0, rv);
	zval *solr_zif_name = zend_read_property(Z_OBJCE_P(object), object, SOLR_ZIFNAME_PROPERTY_NAME, sizeof(SOLR_ZIFNAME_PROPERTY_NAME)-1, 0, rv);
	long int source_line = Z_LVAL_P(line_no);
	char *solr_source_file = Z_STRVAL_P(solr_file);
	char *solr_zifname = Z_STRVAL_P(solr_zif_name);

	array_init(return_value);

	add_assoc_long(return_value, SOLR_SOURCELINE_NO_PROPERTY_NAME, source_line);
	add_assoc_string(return_value, SOLR_SOURCEFILE_PROPERTY_NAME, solr_source_file);
	add_assoc_string(return_value, SOLR_ZIFNAME_PROPERTY_NAME, solr_zifname);
}
/* }}} */

/* {{{ void solr_throw_exception_ex(zend_class_entry *exception_ce, long code TSRMLS_DC, const char *filename, int file_line, const char *function_name, char *format, ...) */
PHP_SOLR_API void solr_throw_exception_ex(zend_class_entry *exception_ce, long code TSRMLS_DC, const char *filename, int file_line, const char *function_name, char *format, ...)
{
	char *message = NULL;
	zval object;
	zend_object *object_val = NULL;

	va_list args;

	va_start(args,format);

	/* Preparing the message string from the format and variable argument list, if any. */
	ap_php_vasprintf(&message, format, args);

	va_end(args);

	/* Retrieves the thrown object and updates the properties */
	object_val = zend_throw_exception(exception_ce, message, code TSRMLS_CC);

	ZVAL_OBJ(&object, object_val);

	/* This is the line number in the source file where it was thrown */
	zend_update_property_long(exception_ce, &object, SOLR_SOURCELINE_NO_PROPERTY_NAME, sizeof(SOLR_SOURCELINE_NO_PROPERTY_NAME)-1, file_line TSRMLS_CC);

	/* This is the line source file where it was thrown */
	zend_update_property_string(exception_ce, &object, SOLR_SOURCEFILE_PROPERTY_NAME, sizeof(SOLR_SOURCEFILE_PROPERTY_NAME)-1, (char *) filename TSRMLS_CC);

	/* This is the C function where it was thrown */
	zend_update_property_string(exception_ce, &object, SOLR_ZIFNAME_PROPERTY_NAME, sizeof(SOLR_ZIFNAME_PROPERTY_NAME)-1, (char *) function_name TSRMLS_CC);

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
    zend_object *object_val = NULL;
    zval object;

	object_val = zend_throw_exception(exception_ce, message, code);
	ZVAL_OBJ(&object, object_val);

	/* This is the line number in the source file where it was thrown */
	zend_update_property_long(exception_ce, &object, SOLR_SOURCELINE_NO_PROPERTY_NAME, sizeof(SOLR_SOURCELINE_NO_PROPERTY_NAME)-1, file_line);

	/* This is the line source file where it was thrown */
	zend_update_property_string(exception_ce, &object, SOLR_SOURCEFILE_PROPERTY_NAME, sizeof(SOLR_SOURCEFILE_PROPERTY_NAME)-1, (char *) filename);

	/* This is the C function where it was thrown */
	zend_update_property_string(exception_ce, &object, SOLR_ZIFNAME_PROPERTY_NAME, sizeof(SOLR_ZIFNAME_PROPERTY_NAME)-1, (char *) function_name);
}
/* }}} */

/* Macro for preparing the return value array */
#define solr_exception_return_internal_info() { \
    solr_prepare_internal_info(getThis(), return_value TSRMLS_CC); \
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

/* {{{ proto array SolrServerException::getInternalInfo(void)
   Returns the internal API information where the exception was generated */
PHP_METHOD(SolrServerException, getInternalInfo)
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

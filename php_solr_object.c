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

/* $Id: php_solr_object.c 320130 2011-11-28 20:44:55Z pierrick $ */

#include "php_solr.h"

/* {{{ PHP_SOLR_API void solr_object_write_property(zval *object, zval *member, zval *value TSRMLS_DC) */
#if PHP_VERSION_ID < 50399
PHP_SOLR_API void solr_object_write_property(zval *object, zval *member, zval *value TSRMLS_DC)
#else
PHP_SOLR_API void solr_object_write_property(zval *object, zval *member, zval *value, const zend_literal *key TSRMLS_DC)
#endif
{
	solr_throw_exception(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1006_MSG, SOLR_ERROR_1006 TSRMLS_CC, SOLR_FILE_LINE_FUNC);

	if (Z_TYPE_P(member) == IS_STRING)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Attempting to set value for [%s] property in a SolrObject instance", Z_STRVAL_P(member));
	}
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_object_write_dimension(zval *object, zval *offset, zval *value TSRMLS_DC) */
PHP_SOLR_API void solr_object_write_dimension(zval *object, zval *offset, zval *value TSRMLS_DC)
{
	solr_throw_exception(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1006_MSG, SOLR_ERROR_1006 TSRMLS_CC, SOLR_FILE_LINE_FUNC);

	if (Z_TYPE_P(offset) == IS_STRING)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Attempting to set value for [%s] property in a SolrObject instance", Z_STRVAL_P(offset));
	}
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_object_unset_property(zval *object, zval *member TSRMLS_DC) */
#if PHP_VERSION_ID < 50399
PHP_SOLR_API void solr_object_unset_property(zval *object, zval *member TSRMLS_DC)
#else
PHP_SOLR_API void solr_object_unset_property(zval *object, zval *member, const zend_literal *key TSRMLS_DC)
#endif
{
	solr_throw_exception(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1006_MSG, SOLR_ERROR_1006 TSRMLS_CC, SOLR_FILE_LINE_FUNC);

	if (Z_TYPE_P(member) == IS_STRING)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Attempting to remove [%s] property in a SolrObject instance", Z_STRVAL_P(member));
	}
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_object_unset_dimension(zval *object, zval *offset TSRMLS_DC) */
PHP_SOLR_API void solr_object_unset_dimension(zval *object, zval *offset TSRMLS_DC)
{
	solr_throw_exception(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1006_MSG, SOLR_ERROR_1006 TSRMLS_CC, SOLR_FILE_LINE_FUNC);

	if (Z_TYPE_P(offset) == IS_STRING)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Attempting to remove [%s] property in a SolrObject instance", Z_STRVAL_P(offset));
	}
}
/* }}} */

/* {{{ PHP_SOLR_API zval *solr_object_read_property(zval *object, zval *member, int type TSRMLS_DC) */
#if PHP_VERSION_ID < 50399
PHP_SOLR_API zval *solr_object_read_property(zval *object, zval *member, int type TSRMLS_DC)
#else
PHP_SOLR_API zval *solr_object_read_property(zval *object, zval *member, int type, const zend_literal *key TSRMLS_DC)
#endif
{
	zval **value = &EG(uninitialized_zval_ptr);
	char *name = NULL;
	HashTable *properties = NULL;

	/* zend_object *zobject = NULL; */

	if (Z_TYPE_P(member) != IS_STRING)
	{
		return (*value);
	}

	SOLR_HASHTABLE_FOR_LOOP(properties)
	{
		char *property_name = NULL;
		uint  property_name_len = 0U;
		ulong num_index = 0L;

		zend_hash_get_current_key_ex(properties, &property_name, &property_name_len, &num_index, 0, NULL);

		/* If the property name is in the HashTable */
		if (property_name && !strcmp(property_name, name))
		{
			zend_hash_get_current_data_ex(properties, (void **) &value, NULL);
		}
	}

	return (*value);
}
/* }}} */

/* {{{ proto SolrObject::__construct(void)
   Constructor for SolrObject */
PHP_METHOD(SolrObject, __construct)
{
	Z_OBJ_HT_P(getThis()) = &solr_object_handlers;
}
/* }}} */

/* {{{ proto SolrObject::__destruct(void)
   Destructor for SolrObject. */
PHP_METHOD(SolrObject, __destruct)
{

}
/* }}} */

/* {{{ proto void SolrObject::__set(string property_name, mixed value)
   Magic method for setting/updating property values. */
PHP_METHOD(SolrObject, __set)
{

}
/* }}} */

/* {{{ proto mixed SolrObject::__get(string property_name)
   Magic method for retrieving properties. */
PHP_METHOD(SolrObject, __get)
{
	solr_char_t *name = NULL;
	int name_len = 0;
	zval *property = NULL;
	zend_bool copy_value = 1;

	void *dtor = NULL;

	/* Process the parameters passed to the method */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {

		RETURN_FALSE;
	}

	property = zend_read_property(solr_ce_SolrObject, getThis(), name, name_len, 0 TSRMLS_CC);

	if (property)
	{
		RETURN_ZVAL(property, copy_value, dtor);
	}
}
/* }}} */

/* {{{ proto bool SolrObject::__isset(string property_name)
   Magic method for checking if a property exists in the object. */
PHP_METHOD(SolrObject, __isset)
{
	solr_char_t *name = NULL;
	int name_len = 0;
	zend_object *zobject = NULL;
	void **value = NULL;

	/* Process the parameters passed to the method */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {

		RETURN_FALSE;
	}

	zobject = zend_objects_get_address(getThis() TSRMLS_CC);

	zend_hash_find(zobject->properties, name, name_len, (void **) &value);

	if (value)
	{
		RETURN_TRUE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto void SolrObject::__unset(string property_name)
   Magic method for removing the specified property. */
PHP_METHOD(SolrObject, __unset)
{
	solr_char_t *name = NULL;
	int name_len = 0;

	/* Process the parameters passed to the method */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {

		return;
	}

	solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1002 TSRMLS_CC, SOLR_FILE_LINE_FUNC, SOLR_ERROR_1002_MSG, name);

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto void SolrObject::offsetSet(string key, mixed value)
   Sets the specified key to value. */
PHP_METHOD(SolrObject, offsetSet)
{
	solr_char_t *name = NULL;
	int name_len = 0;
	zval *prop = NULL;

	/* Process the parameters passed to the method */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sz", &name, &name_len, &prop) == FAILURE) {

		RETURN_FALSE;
	}

	if (prop && prop->type == IS_NULL)
	{
		solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1002 TSRMLS_CC, SOLR_FILE_LINE_FUNC, SOLR_ERROR_1002_MSG, name);

		return ;
	}

	zend_update_property(Z_OBJCE_P(getThis()), getThis(), name, name_len, prop TSRMLS_CC);
}
/* }}} */

/* {{{ proto mixed SolrObject::offsetGet(string key)
   Retrieves the requested key. */
PHP_METHOD(SolrObject, offsetGet)
{
	solr_char_t *name = NULL;
	int name_len = 0;
	zend_object *zobject = zend_objects_get_address(getThis() TSRMLS_CC);
	HashTable *properties = zobject->properties;
	zval **property_value = NULL;
	zend_bool copy_value = 1;

	void *dtor = NULL;

	/* Process the parameters passed to the method */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {

		RETURN_FALSE;
	}

	SOLR_HASHTABLE_FOR_LOOP(properties)
	{
		char *property_name = NULL;

		uint  property_name_len = 0U;

		ulong num_index = 0L;

		zend_hash_get_current_key_ex(properties, &property_name, &property_name_len, &num_index, 0, NULL);

		/* If the property name is in the HashTable */
		if (property_name && !strcmp(property_name, name))
		{
			zend_hash_get_current_data_ex(properties, (void **) &property_value, NULL);

			goto job_complete;
		}
	}

job_complete :

	zend_hash_internal_pointer_reset(properties);

	if (property_value && (*property_value))
	{
		RETURN_ZVAL((*property_value), copy_value, dtor);
	}
}
/* }}} */

/* {{{ proto bool SolrObject::offsetExists(string key)
   Checks if the key exists. */
PHP_METHOD(SolrObject, offsetExists)
{
	solr_char_t *name = NULL;
	int name_len = 0;
	zend_object *zobject = zend_objects_get_address(getThis() TSRMLS_CC);
	HashTable *properties = zobject->properties;
	zend_bool property_exists = 0;

	/* Process the parameters passed to the method */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {

		RETURN_FALSE;
	}

	SOLR_HASHTABLE_FOR_LOOP(properties)
	{
		char *property_name = NULL;
		uint  property_name_len = 0U;
		ulong num_index = 0L;

		zend_hash_get_current_key_ex(properties, &property_name, &property_name_len, &num_index, 0, NULL);

		/* If the property name is in the HashTable */
		if (property_name && !strcmp(property_name, name))
		{
			property_exists = 1;

			goto job_complete;
		}
	}

job_complete :

	zend_hash_internal_pointer_reset(properties);

	RETURN_BOOL(property_exists);
}
/* }}} */

/* {{{ proto void SolrObject::offsetUnset(string key)
   Removes the specified key. */
PHP_METHOD(SolrObject, offsetUnset)
{
	solr_char_t *name = NULL;
	int name_len = 0;

	/* Process the parameters passed to the method */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {

		return;
	}

	solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1002 TSRMLS_CC, SOLR_FILE_LINE_FUNC, SOLR_ERROR_1002_MSG, name);

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto array SolrObject::getPropertyNames(void)
   Returns an array of all the properties/keys in the object. */
PHP_METHOD(SolrObject, getPropertyNames)
{
	zend_object *zobject = zend_objects_get_address(getThis() TSRMLS_CC);

	HashTable *properties = zobject->properties;

	array_init(return_value);

	SOLR_HASHTABLE_FOR_LOOP(properties)
	{
		char *property_name       = NULL;
		uint property_name_length = 0U;
		ulong num_index           = 0L;

		zend_hash_get_current_key_ex(properties, &property_name, &property_name_length, &num_index, 0, NULL);

		add_next_index_stringl(return_value, property_name, property_name_length, 1);
	}
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


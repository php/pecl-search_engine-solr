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

/* $Id: solr_functions_params.c 289604 2009-10-13 04:32:39Z iekpo $ */

#include "php_solr.h"

/* {{{ PHP_SOLR_API void solr_destroy_params(void *solr_params) */
PHP_SOLR_API void solr_destroy_params(void *solr_params)
{
	solr_params_t *params = (solr_params_t *) solr_params;

	zend_hash_destroy(params->params);

	pefree(params->params, SOLR_PARAMS_PERSISTENT);
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_destroy_param(solr_param_t **param) */
PHP_SOLR_API void solr_destroy_param(solr_param_t **param)
{
	solr_param_value_t *temp_ptr    = NULL;

	solr_param_value_t *current_ptr = (*param)->head;

	while(current_ptr != NULL) {

		temp_ptr = current_ptr->next;

		(*param)->value_free_func(current_ptr);

		current_ptr = temp_ptr;
	}

	(*param)->head = NULL;
	(*param)->last = NULL;

	pefree((*param)->param_name, SOLR_PARAMS_PERSISTENT);

	(*param)->param_name = NULL;

	pefree((*param), SOLR_PARAMS_PERSISTENT);

	(*param) = NULL;
}
/* }}} */

/* {{{ PHP_SOLR_API int solr_params_delete_param_value(solr_param_t *param, const solr_param_value_t *target_value TSRMLS_DC) */
PHP_SOLR_API int solr_params_delete_param_value(solr_param_t *param, const solr_param_value_t *target_value TSRMLS_DC)
{
	solr_param_value_t *curr_value = param->head;
	int match_found = 0;

	if (!target_value)
	{
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Invalid pointer. Submitted target cannot be used for the delete search\n");

		return FAILURE;
	}

	while(!match_found && curr_value != NULL)
	{
		match_found = param->value_equal_func(curr_value, target_value);

		/* If the target was found */
		if (match_found)
		{
			/* If the target is not the head */
			if (curr_value->prev)
			{
				curr_value->prev->next = curr_value->next;

			} else {

				param->head = curr_value->next;
			}

			/* If the target is not the tail */
			if (curr_value->next)
			{
				curr_value->next->prev = curr_value->prev;

			} else {

				param->last = curr_value->prev;
			}

			/* Destroy target value */
			param->value_free_func(curr_value);

			goto dpv_end;
		}

		curr_value = curr_value->next;
	}

dpv_end :

	if (!match_found)
	{
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Target parameter value could not be found in '%s'. No value was deleted ", param->param_name);

		return FAILURE;
	}

	param->count--; /* Reduce the value count by one */

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_SOLR_API int solr_params_insert_param_value(solr_param_t *param, solr_param_value_t *param_value) */
PHP_SOLR_API int solr_params_insert_param_value(solr_param_t *param, solr_param_value_t *param_value)
{
	if (!param_value)
	{

		return FAILURE;
	}

	param_value->next = param_value->prev = NULL;

	if (!param->allow_multiple)
	{
		param->value_free_func(param->head);

		param->head  = param_value;

		param->last  = param_value;

		param->count = 1U;

		return SUCCESS;
	}

	if (param->head == NULL) {

		param->head = param_value;

		param->last = param_value;

	} else {

		param_value->prev = param->last;

		param->last->next = param_value;

		param->last       = param_value;
	}

	param->count++;

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_SOLR_API solr_param_t *solr_create_new_param(const solr_char_t *param_name, size_t param_name_len, solr_param_type_t param_type, solr_bool allow_multiple, solr_param_value_equal_func_t value_equal_func, solr_param_fetch_func_t param_fetch_func, solr_param_value_free_func_t value_free_func, solr_char_t delimiter, solr_char_t arg_separator TSRMLS_DC) */
PHP_SOLR_API solr_param_t *solr_create_new_param(const solr_char_t *param_name, size_t param_name_len, solr_param_type_t param_type, solr_bool allow_multiple, solr_param_value_equal_func_t value_equal_func, solr_param_fetch_func_t param_fetch_func, solr_param_value_free_func_t value_free_func, solr_char_t delimiter, solr_char_t arg_separator TSRMLS_DC)
{
	solr_param_t *query_param = (solr_param_t *) pemalloc(sizeof(solr_param_t), SOLR_PARAMS_PERSISTENT);

	/* Always initialize linked list containers to NULL. */
	/* Member pointers may contain unallocated addresses */
	/* This notice applies to all solr_param_t member pointers here */
	memset(query_param, 0, sizeof(solr_param_t));

	query_param->type  = param_type;

	query_param->count = 0L;

	query_param->param_name = solr_strndup(param_name, param_name_len);

	query_param->param_name_length = param_name_len;

	query_param->allow_multiple = allow_multiple;

	query_param->head = query_param->last = NULL;

	query_param->value_equal_func = value_equal_func;

	query_param->fetch_func = param_fetch_func;

	query_param->value_free_func = value_free_func;

	query_param->delimiter = delimiter;

	query_param->arg_separator = arg_separator;

	return query_param;
}
/* }}} */

/* {{{ PHP_SOLR_API int solr_add_or_set_normal_param(zval *objptr, solr_char_t *pname, int pname_length, solr_char_t *pvalue, int pvalue_length, zend_bool allow_multiple TSRMLS_DC)
parameter value addition functions */
PHP_SOLR_API int solr_add_or_set_normal_param(zval *objptr, solr_char_t *pname, int pname_length, solr_char_t *pvalue, int pvalue_length, zend_bool allow_multiple TSRMLS_DC)
{
	solr_params_t *solr_params = NULL;
	solr_param_t **param_ptr = NULL;
	HashTable *params = NULL;
	solr_param_type_t param_type = SOLR_PARAM_TYPE_NORMAL;
	solr_param_t *param = NULL;
	solr_param_value_t *parameter_value = NULL;


	if (!pname_length)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameter name");

		return FAILURE;
	}

	if (!pvalue_length)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameter value");

		return FAILURE;
	}

	if (solr_fetch_params_entry(objptr, &solr_params TSRMLS_CC) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "SolrParams instance could not be retrieved from HashTable");

		return FAILURE;
	}

	params = solr_params->params;

	if (zend_hash_find(params, (char *) pname, pname_length, (void **) &param_ptr) == SUCCESS)
	{
		parameter_value = (solr_param_value_t *) pemalloc(sizeof(solr_param_value_t), SOLR_PARAMS_PERSISTENT);

		memset(parameter_value, 0, sizeof(solr_param_value_t));

		solr_string_appends(&(parameter_value->contents.normal), pvalue, pvalue_length);

		solr_params_insert_param_value((*param_ptr), parameter_value);

		return SUCCESS;
	}

	param = solr_create_new_param(pname, pname_length, param_type, allow_multiple, solr_normal_param_value_equal, (solr_param_fetch_func_t) solr_normal_param_value_fetch, solr_normal_param_value_free, '&', 0 TSRMLS_CC);
	parameter_value = (solr_param_value_t *) pemalloc(sizeof(solr_param_value_t), SOLR_PARAMS_PERSISTENT);

	memset(parameter_value, 0, sizeof(solr_param_value_t));

	solr_string_appends(&(parameter_value->contents.normal), pvalue, pvalue_length);
	solr_params_insert_param_value(param, parameter_value);

	if (zend_hash_add(params, pname, pname_length, (void *) &param, sizeof(solr_param_t *), (void **) NULL) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error from %s %s=%s", __func__, (char *) pname, pvalue);

		return FAILURE;
	}

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_SOLR_API int solr_add_simple_list_param(zval *objptr, solr_char_t *pname, int pname_length, solr_char_t *pvalue, int pvalue_length TSRMLS_DC) */
PHP_SOLR_API int solr_add_simple_list_param(zval *objptr, solr_char_t *pname, int pname_length, solr_char_t *pvalue, int pvalue_length TSRMLS_DC)
{
	zend_bool allow_multiple = 1; /* This value type by definition allows multiple. add parameters can be added more than once */
	solr_params_t *solr_params = NULL;
	solr_param_t **param_ptr = NULL;
	HashTable *params = NULL;
	solr_param_type_t param_type = SOLR_PARAM_TYPE_SIMPLE_LIST;
	solr_param_t *param = NULL;
	solr_param_value_t *parameter_value = NULL;

	if (!pname_length)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameter name");

		return FAILURE;
	}

	if (!pvalue_length)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameter value");

		return FAILURE;
	}

	if (solr_fetch_params_entry(objptr, &solr_params TSRMLS_CC) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "SolrParams instance could not be retrieved from HashTable");

		return FAILURE;
	}

	params = solr_params->params;

	if (zend_hash_find(params, pname, pname_length, (void **) &param_ptr) == SUCCESS)
	{
		parameter_value = (solr_param_value_t *) pemalloc(sizeof(solr_param_value_t), SOLR_PARAMS_PERSISTENT);

		memset(parameter_value, 0, sizeof(solr_param_value_t));

		solr_string_appends(&(parameter_value->contents.simple_list), pvalue, pvalue_length);

		solr_params_insert_param_value((*param_ptr), parameter_value);

		return SUCCESS;
	}

	param = solr_create_new_param(pname, pname_length, param_type, allow_multiple, solr_simple_list_param_value_equal, (solr_param_fetch_func_t) solr_simple_list_param_value_fetch, solr_simple_list_param_value_free, ',', 0 TSRMLS_CC);
	parameter_value = (solr_param_value_t *) pemalloc(sizeof(solr_param_value_t), SOLR_PARAMS_PERSISTENT);

	memset(parameter_value, 0, sizeof(solr_param_value_t));

	solr_string_appends(&(parameter_value->contents.simple_list), pvalue, pvalue_length);
	solr_params_insert_param_value(param, parameter_value);

	if (zend_hash_add(params, pname, pname_length, (void *) &param, sizeof(solr_param_t *), (void **) NULL) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error from %s %s=%s", __func__, (char *) pname, pvalue);

		return FAILURE;
	}

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_SOLR_API int solr_add_arg_list_param(zval *objptr, solr_char_t *pname, int pname_length, solr_char_t *pvalue, int pvalue_length, solr_char_t *avalue, int avalue_length, solr_char_t delimiter, solr_char_t arg_separator TSRMLS_DC) */
PHP_SOLR_API int solr_add_arg_list_param(zval *objptr, solr_char_t *pname, int pname_length, solr_char_t *pvalue, int pvalue_length, solr_char_t *avalue, int avalue_length, solr_char_t delimiter, solr_char_t arg_separator TSRMLS_DC)
{
	zend_bool allow_multiple = 1; /* This value type by definition allows multiple */
	solr_params_t *solr_params = NULL;
	solr_param_type_t param_type = SOLR_PARAM_TYPE_ARG_LIST;
	solr_param_t *param = NULL;
	solr_param_value_t *parameter_value = NULL;
	HashTable *params = NULL;
	solr_param_t **param_ptr = NULL;

	if (!pname_length)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameter name");

		return FAILURE;
	}

	if (!pvalue_length)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameter value");

		return FAILURE;
	}

	if (!avalue_length)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid argument value");

		return FAILURE;
	}

	if (solr_fetch_params_entry(objptr, &solr_params TSRMLS_CC) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "SolrParams instance could not be retrieved from HashTable");

		return FAILURE;
	}

	params = solr_params->params;

	if (zend_hash_find(params, pname, pname_length, (void **) &param_ptr) == SUCCESS)
	{
		parameter_value = (solr_param_value_t *) pemalloc(sizeof(solr_param_value_t), SOLR_PARAMS_PERSISTENT);

		memset(parameter_value, 0, sizeof(solr_param_value_t));

		solr_string_appends(&(parameter_value->contents.arg_list.value), pvalue, pvalue_length);

		solr_string_appends(&(parameter_value->contents.arg_list.arg), avalue, avalue_length);

		solr_params_insert_param_value((*param_ptr), parameter_value);

		return SUCCESS;
	}

	param = solr_create_new_param(pname, pname_length, param_type, allow_multiple, solr_arg_list_param_value_equal, (solr_param_fetch_func_t) solr_arg_list_param_value_fetch, solr_arg_list_param_value_free, delimiter, arg_separator TSRMLS_CC);
	parameter_value = (solr_param_value_t *) pemalloc(sizeof(solr_param_value_t), SOLR_PARAMS_PERSISTENT);

	memset(parameter_value, 0, sizeof(solr_param_value_t));

	solr_string_appends(&(parameter_value->contents.arg_list.value), pvalue, pvalue_length);
	solr_string_appends(&(parameter_value->contents.arg_list.arg), avalue, avalue_length);
	solr_params_insert_param_value(param, parameter_value);

	if (zend_hash_add(params, pname, pname_length, (void *) &param, sizeof(solr_param_t *), (void **) NULL) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error from %s %s=%s", __func__, (char *) pname, pvalue);

		return FAILURE;
	}

	return SUCCESS;
}
/* }}} */

/* {{{ Parameter value EQUALITY FUNCTIONS */

/* {{{ PHP_SOLR_API int solr_normal_param_value_equal(const solr_param_value_t *a, const solr_param_value_t *b) */
PHP_SOLR_API int solr_normal_param_value_equal(const solr_param_value_t *a, const solr_param_value_t *b)
{
	return solr_string_equal(&(a->contents.normal), &(b->contents.normal));
}
/* }}} */

/* {{{ PHP_SOLR_API int solr_simple_list_param_value_equal(const solr_param_value_t *a, const solr_param_value_t *b) */
PHP_SOLR_API int solr_simple_list_param_value_equal(const solr_param_value_t *a, const solr_param_value_t *b)
{
	return solr_string_equal(&(a->contents.simple_list), &(b->contents.simple_list));
}
/* }}} */

/* {{{ PHP_SOLR_API int solr_arg_list_param_value_equal(const solr_param_value_t *a, const solr_param_value_t *b) */
PHP_SOLR_API int solr_arg_list_param_value_equal(const solr_param_value_t *a, const solr_param_value_t *b)
{
	return solr_string_equal(&(a->contents.arg_list.value), &(b->contents.arg_list.value));
}
/* }}} */

/* }}} */

/* {{{ Parameter values retrieval functions */

/* {{{ PHP_SOLR_API void solr_normal_param_value_fetch(solr_param_t *solr_param, solr_string_t *buffer) */
PHP_SOLR_API void solr_normal_param_value_fetch(solr_param_t *solr_param, solr_string_t *buffer)
{
	solr_param_value_t *current_ptr = solr_param->head;

	solr_char_t glue = '&';

	if (!solr_param->allow_multiple)
	{
		auto int new_pv_length = 0;

		solr_char_t *url_encoded_param_value = (solr_char_t *) php_raw_url_encode((char *) current_ptr->contents.normal.str, current_ptr->contents.normal.len, &new_pv_length);

		solr_string_appends(buffer, solr_param->param_name, solr_param->param_name_length);

		solr_string_appendc(buffer, '=');

		solr_string_appends(buffer, url_encoded_param_value, new_pv_length);

		efree(url_encoded_param_value);

	} else {

		ulong n_loops = solr_param->count - 1;
		auto int new_pv_length = 0;
		solr_char_t *url_encoded_param_value = NULL;

		while(n_loops)
		{
			new_pv_length = 0;

			url_encoded_param_value = php_raw_url_encode(current_ptr->contents.normal.str, current_ptr->contents.normal.len, &new_pv_length);

			solr_string_appends(buffer, solr_param->param_name, solr_param->param_name_length);

			solr_string_appendc(buffer, '=');

			solr_string_appends(buffer, url_encoded_param_value, new_pv_length);

			efree(url_encoded_param_value);

			url_encoded_param_value = NULL;

			solr_string_appendc(buffer, glue);

			n_loops--;

			current_ptr = current_ptr->next;
		}

		url_encoded_param_value = php_raw_url_encode(current_ptr->contents.normal.str, current_ptr->contents.normal.len, &new_pv_length);

		solr_string_appends(buffer, solr_param->param_name, solr_param->param_name_length);
		solr_string_appendc(buffer, '=');
		solr_string_appends(buffer, url_encoded_param_value, new_pv_length);

		efree(url_encoded_param_value);

		url_encoded_param_value = NULL;
	}
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_simple_list_param_value_fetch(solr_param_t *solr_param, solr_string_t *buffer) */
PHP_SOLR_API void solr_simple_list_param_value_fetch(solr_param_t *solr_param, solr_string_t *buffer)
{
	solr_param_value_t *current_ptr = solr_param->head;
	solr_char_t list_delimiter = ','; /* Comma 0x2C */
	ulong n_loops = solr_param->count - 1;
	auto solr_string_t tmp_buffer;
	auto int new_pv_length = 0;
	solr_char_t *url_encoded_list = NULL;

	solr_string_appends(buffer, solr_param->param_name, solr_param->param_name_length);
	solr_string_appendc(buffer, '=');

	memset(&tmp_buffer, 0, sizeof(solr_string_t));

	while(n_loops)
	{
		solr_string_append_solr_string(&tmp_buffer, &(current_ptr->contents.simple_list));

		solr_string_appendc(&tmp_buffer, list_delimiter);

		n_loops--;

		current_ptr = current_ptr->next;
	}

	solr_string_append_solr_string(&tmp_buffer, &(current_ptr->contents.simple_list));

	url_encoded_list = php_raw_url_encode(tmp_buffer.str, tmp_buffer.len, &new_pv_length);

	solr_string_appends(buffer, url_encoded_list, new_pv_length);

	efree(url_encoded_list);

	url_encoded_list = NULL;

	solr_string_free(&tmp_buffer);
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_arg_list_param_value_fetch(solr_param_t *solr_param, solr_string_t *buffer) */
PHP_SOLR_API void solr_arg_list_param_value_fetch(solr_param_t *solr_param, solr_string_t *buffer)
{
	solr_param_value_t *current_ptr = solr_param->head;
	solr_char_t list_delimiter = solr_param->delimiter;
	solr_char_t separator = solr_param->arg_separator;
	ulong n_loops = solr_param->count - 1;
	solr_string_t tmp_buffer;
	int new_pv_length = 0;
	solr_char_t *url_encoded_list = NULL;


	solr_string_appends(buffer, solr_param->param_name, solr_param->param_name_length);
	solr_string_appendc(buffer, '=');

	memset(&tmp_buffer, 0, sizeof(solr_string_t));

	while(n_loops)
	{
		solr_string_append_solr_string(&tmp_buffer, &(current_ptr->contents.arg_list.value));

		solr_string_appendc(&tmp_buffer, separator);

		solr_string_append_solr_string(&tmp_buffer, &(current_ptr->contents.arg_list.arg));

		solr_string_appendc(&tmp_buffer, list_delimiter);

		n_loops--;

		current_ptr = current_ptr->next;
	}

	solr_string_append_solr_string(&tmp_buffer, &(current_ptr->contents.arg_list.value));
	solr_string_appendc(&tmp_buffer, separator);
	solr_string_append_solr_string(&tmp_buffer, &(current_ptr->contents.arg_list.arg));

	url_encoded_list = php_raw_url_encode(tmp_buffer.str, tmp_buffer.len, &new_pv_length);

	solr_string_appends(buffer, url_encoded_list, new_pv_length);

	efree(url_encoded_list);

	url_encoded_list = NULL;

	solr_string_free(&tmp_buffer);
}
/* }}} */

/* }}} */

/* {{{ Parameter retrieval functions. Only used for display. */

/* {{{ PHP_SOLR_API void solr_normal_param_value_display_string(solr_param_t *solr_param, zval *param_value) */
PHP_SOLR_API void solr_normal_param_value_display_string(solr_param_t *solr_param, zval *param_value)
{
	solr_param_value_t *current_ptr = solr_param->head;

	ZVAL_STRINGL(param_value, current_ptr->contents.normal.str, current_ptr->contents.normal.len, 1);
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_normal_param_value_display_integer(solr_param_t *solr_param, zval *param_value) */
PHP_SOLR_API void solr_normal_param_value_display_integer(solr_param_t *solr_param, zval *param_value)
{
	solr_param_value_t *current_ptr = solr_param->head;

	long int return_value = atol(current_ptr->contents.normal.str);

	ZVAL_LONG(param_value, return_value);
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_normal_param_value_display_double(solr_param_t *solr_param, zval *param_value) */
PHP_SOLR_API void solr_normal_param_value_display_double(solr_param_t *solr_param, zval *param_value)
{
	solr_param_value_t *current_ptr = solr_param->head;

	double return_value = atof(current_ptr->contents.normal.str);

	ZVAL_DOUBLE(param_value, return_value);
}
/* }}} */

/* Checks if current_ptr->contents.normal.str matches str_const */
#define solr_npvdb_strcmp(str_const) (0 == strcmp(str_const, current_ptr->contents.normal.str))

/* {{{ PHP_SOLR_API void solr_normal_param_value_display_boolean(solr_param_t *solr_param, zval *param_value) */
PHP_SOLR_API void solr_normal_param_value_display_boolean(solr_param_t *solr_param, zval *param_value)
{
	solr_param_value_t *current_ptr = solr_param->head;

	zend_bool return_value = (zend_bool) (solr_npvdb_strcmp("true") || solr_npvdb_strcmp("on") );

	ZVAL_BOOL(param_value, return_value);
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_normal_param_value_display_sort_type(solr_param_t *solr_param, zval *param_value) */
PHP_SOLR_API void solr_normal_param_value_display_sort_type(solr_param_t *solr_param, zval *param_value)
{
	solr_param_value_t *current_ptr = solr_param->head;

	long int return_value = (long int) (solr_npvdb_strcmp("count"));

	ZVAL_LONG(param_value, return_value);
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_normal_param_value_display(solr_param_t *solr_param, zval *param_value_array) */
PHP_SOLR_API void solr_normal_param_value_display(solr_param_t *solr_param, zval *param_value_array)
{
	solr_param_value_t *current_ptr = solr_param->head;
	register int duplicate = 1;

	while (current_ptr != NULL)
	{
		add_next_index_stringl(param_value_array, current_ptr->contents.normal.str, current_ptr->contents.normal.len, duplicate);

		current_ptr = current_ptr->next;
	}
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_simple_list_param_value_display(solr_param_t *solr_param, zval *param_value_array) */
PHP_SOLR_API void solr_simple_list_param_value_display(solr_param_t *solr_param, zval *param_value_array)
{
	solr_param_value_t *current_ptr = solr_param->head;
	register int duplicate = 1;

	while (current_ptr != NULL)
	{
		add_next_index_stringl(param_value_array, current_ptr->contents.simple_list.str, current_ptr->contents.simple_list.len, duplicate);

		current_ptr = current_ptr->next;
	}
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_arg_list_param_value_display(solr_param_t *solr_param, zval *param_value_array) */
PHP_SOLR_API void solr_arg_list_param_value_display(solr_param_t *solr_param, zval *param_value_array)
{
	solr_param_value_t *current_ptr = solr_param->head;
	register int duplicate = 1;

	while (current_ptr != NULL)
	{
		solr_string_t tmp_buffer;

		memset(&tmp_buffer, 0, sizeof(solr_string_t));

		solr_string_append_solr_string(&tmp_buffer, &(current_ptr->contents.arg_list.value));

		solr_string_appendc(&tmp_buffer, solr_param->arg_separator);

		solr_string_append_solr_string(&tmp_buffer, &(current_ptr->contents.arg_list.arg));

		add_next_index_stringl(param_value_array, tmp_buffer.str, tmp_buffer.len, duplicate);

		solr_string_free(&tmp_buffer);

		current_ptr = current_ptr->next;
	}
}
/* }}} */

/* }}} */

/* {{{ Parameter retrieval functions. Only used for toString() */

/* {{{ PHP_SOLR_API void solr_normal_param_value_tostring(solr_param_t *solr_param, solr_string_t *buffer, zend_bool url_encode) */
PHP_SOLR_API void solr_normal_param_value_tostring(solr_param_t *solr_param, solr_string_t *buffer, zend_bool url_encode)
{
	solr_param_value_t *current_ptr = solr_param->head;

	solr_char_t glue = '&';

	if (!solr_param->allow_multiple)
	{
		auto int new_pv_length = 0;

		solr_char_t *url_encoded_param_value = NULL;

		if (url_encode)
		{
			url_encoded_param_value = (solr_char_t *) php_raw_url_encode((char *) current_ptr->contents.normal.str, current_ptr->contents.normal.len, &new_pv_length);

		} else {

			new_pv_length = current_ptr->contents.normal.len;

			url_encoded_param_value = solr_strndup(current_ptr->contents.normal.str, current_ptr->contents.normal.len);
		}

		solr_string_appends(buffer, solr_param->param_name, solr_param->param_name_length);

		solr_string_appendc(buffer, '=');

		solr_string_appends(buffer, url_encoded_param_value, new_pv_length);

		efree(url_encoded_param_value);

	} else {

		ulong n_loops = solr_param->count - 1;
		auto int new_pv_length = 0;
		solr_char_t *url_encoded_param_value = NULL;

		while(n_loops)
		{
			new_pv_length = 0;

			if (url_encode)
			{
				url_encoded_param_value = php_raw_url_encode(current_ptr->contents.normal.str, current_ptr->contents.normal.len, &new_pv_length);

			} else {

				new_pv_length = current_ptr->contents.normal.len;

				url_encoded_param_value = solr_strndup(current_ptr->contents.normal.str, current_ptr->contents.normal.len);
			}

			solr_string_appends(buffer, solr_param->param_name, solr_param->param_name_length);

			solr_string_appendc(buffer, '=');

			solr_string_appends(buffer, url_encoded_param_value, new_pv_length);

			efree(url_encoded_param_value);

			url_encoded_param_value = NULL;

			solr_string_appendc(buffer, glue);

			n_loops--;

			current_ptr = current_ptr->next;
		}

		if (url_encode)
		{
			url_encoded_param_value = php_raw_url_encode(current_ptr->contents.normal.str, current_ptr->contents.normal.len, &new_pv_length);

		} else {

			new_pv_length = current_ptr->contents.normal.len;

			url_encoded_param_value = solr_strndup(current_ptr->contents.normal.str, current_ptr->contents.normal.len);
		}

		solr_string_appends(buffer, solr_param->param_name, solr_param->param_name_length);
		solr_string_appendc(buffer, '=');
		solr_string_appends(buffer, url_encoded_param_value, new_pv_length);

		efree(url_encoded_param_value);

		url_encoded_param_value = NULL;
	}
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_simple_list_param_value_tostring(solr_param_t *solr_param, solr_string_t *buffer, zend_bool url_encode) */
PHP_SOLR_API void solr_simple_list_param_value_tostring(solr_param_t *solr_param, solr_string_t *buffer, zend_bool url_encode)
{
	solr_param_value_t *current_ptr = solr_param->head;
	solr_char_t list_delimiter = ','; /* Comma 0x2C */
	ulong n_loops = solr_param->count - 1;
	auto solr_string_t tmp_buffer;
	auto int new_pv_length = 0;
	solr_char_t *url_encoded_list = NULL;

	solr_string_appends(buffer, solr_param->param_name, solr_param->param_name_length);
	solr_string_appendc(buffer, '=');

	memset(&tmp_buffer, 0, sizeof(solr_string_t));

	while(n_loops)
	{
		solr_string_append_solr_string(&tmp_buffer, &(current_ptr->contents.simple_list));

		solr_string_appendc(&tmp_buffer, list_delimiter);

		n_loops--;

		current_ptr = current_ptr->next;
	}

	solr_string_append_solr_string(&tmp_buffer, &(current_ptr->contents.simple_list));

	if (url_encode)
	{
		url_encoded_list = php_raw_url_encode(tmp_buffer.str, tmp_buffer.len, &new_pv_length);

	} else {

		new_pv_length = tmp_buffer.len;

		url_encoded_list = solr_strndup(tmp_buffer.str, tmp_buffer.len);
	}

	solr_string_appends(buffer, url_encoded_list, new_pv_length);

	efree(url_encoded_list);

	url_encoded_list = NULL;

	solr_string_free(&tmp_buffer);
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_arg_list_param_value_tostring(solr_param_t *solr_param, solr_string_t *buffer, zend_bool url_encode) */
PHP_SOLR_API void solr_arg_list_param_value_tostring(solr_param_t *solr_param, solr_string_t *buffer, zend_bool url_encode)
{
	solr_param_value_t *current_ptr = solr_param->head;
	solr_char_t list_delimiter = solr_param->delimiter;
	solr_char_t separator = solr_param->arg_separator;
	ulong n_loops = solr_param->count - 1;
	solr_string_t tmp_buffer;
	int new_pv_length = 0;
	solr_char_t *url_encoded_list = NULL;

	solr_string_appends(buffer, solr_param->param_name, solr_param->param_name_length);
	solr_string_appendc(buffer, '=');

	memset(&tmp_buffer, 0, sizeof(solr_string_t));

	while(n_loops)
	{
		solr_string_append_solr_string(&tmp_buffer, &(current_ptr->contents.arg_list.value));

		solr_string_appendc(&tmp_buffer, separator);

		solr_string_append_solr_string(&tmp_buffer, &(current_ptr->contents.arg_list.arg));

		solr_string_appendc(&tmp_buffer, list_delimiter);

		n_loops--;

		current_ptr = current_ptr->next;
	}

	solr_string_append_solr_string(&tmp_buffer, &(current_ptr->contents.arg_list.value));
	solr_string_appendc(&tmp_buffer, separator);
	solr_string_append_solr_string(&tmp_buffer, &(current_ptr->contents.arg_list.arg));

	if (url_encode)
	{
		url_encoded_list = php_raw_url_encode(tmp_buffer.str, tmp_buffer.len, &new_pv_length);

	} else {

		new_pv_length = tmp_buffer.len;

		url_encoded_list = solr_strndup(tmp_buffer.str, tmp_buffer.len);
	}

	solr_string_appends(buffer, url_encoded_list, new_pv_length);

	efree(url_encoded_list);

	url_encoded_list = NULL;

	solr_string_free(&tmp_buffer);
}
/* }}} */

/* }}} */

/* {{{ Memory deallocation functions for parameter values */

/* {{{ PHP_SOLR_API void solr_normal_param_value_free(solr_param_value_t *param_value) */
PHP_SOLR_API void solr_normal_param_value_free(solr_param_value_t *param_value)
{
	if (param_value)
	{
		solr_string_free(&(param_value->contents.normal));

		pefree(param_value, SOLR_PARAMS_PERSISTENT);

		param_value = NULL;
	}
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_simple_list_param_value_free(solr_param_value_t *param_value) */
PHP_SOLR_API void solr_simple_list_param_value_free(solr_param_value_t *param_value)
{
	if (param_value)
	{
		solr_string_free(&(param_value->contents.simple_list));

		pefree(param_value, SOLR_PARAMS_PERSISTENT);

		param_value = NULL;
	}
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_arg_list_param_value_free(solr_param_value_t *param_value) */
PHP_SOLR_API void solr_arg_list_param_value_free(solr_param_value_t *param_value)
{
	if (param_value)
	{
		solr_string_free(&(param_value->contents.arg_list.value));

		solr_string_free(&(param_value->contents.arg_list.arg));

		pefree(param_value, SOLR_PARAMS_PERSISTENT);

		param_value = NULL;
	}
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_set_return_solr_params_object(zval **return_value_ptr, zval *current_objptr TSRMLS_DC) */
PHP_SOLR_API void solr_set_return_solr_params_object(zval **return_value_ptr, zval *current_objptr TSRMLS_DC)
{
	zval_ptr_dtor(return_value_ptr);

	Z_SET_ISREF_P(current_objptr);

	Z_ADDREF_P(current_objptr);

	*return_value_ptr = current_objptr;
}
/* }}} */

/* {{{ PHP_SOLR_API int solr_delete_solr_parameter(zval *objptr, solr_char_t *name, int name_length TSRMLS_DC) */
PHP_SOLR_API int solr_delete_solr_parameter(zval *objptr, solr_char_t *name, int name_length TSRMLS_DC)
{
	solr_params_t *solr_params = NULL;
	HashTable *params_ht = NULL;

	if (solr_fetch_params_entry(objptr, &solr_params TSRMLS_CC) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "SolrParams instance could not be retrieved from HashTable");

		return FAILURE;
	}

	params_ht = solr_params->params;

	if (zend_hash_del(params_ht, name, name_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "parameter '%s' was not set. Attempting to remove an undefined parameter.", name);

		return FAILURE;
	}

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_SOLR_API int solr_delete_normal_param_value(zval *objptr, solr_char_t *pname, int pname_length, solr_char_t *pvalue, int pvalue_length TSRMLS_DC) */
PHP_SOLR_API int solr_delete_normal_param_value(zval *objptr, solr_char_t *pname, int pname_length, solr_char_t *pvalue, int pvalue_length TSRMLS_DC)
{
	solr_params_t *solr_params = NULL;
	HashTable *params_ht = NULL;
	solr_param_t **param_ptr = NULL;
	solr_param_value_t *target_value = NULL;

	if (!pname_length)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameter name");

		return FAILURE;
	}

	if (!pvalue_length)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameter value");

		return FAILURE;
	}

	if (solr_fetch_params_entry(objptr, &solr_params TSRMLS_CC) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "SolrParams instance could not be retrieved from HashTable");

		return FAILURE;
	}

	params_ht = solr_params->params;

	if (zend_hash_find(params_ht, pname, pname_length, (void **) &param_ptr) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "parameter could not be retrieved from HashTable");

		return FAILURE;
	}

	target_value = (solr_param_value_t *) pecalloc(1, sizeof(solr_param_value_t), SOLR_PARAMS_PERSISTENT);

	solr_string_appends(&(target_value->contents.normal), pvalue, pvalue_length);

	solr_params_delete_param_value((*param_ptr), target_value TSRMLS_CC);

	/* We are done with target_value. */
	(*param_ptr)->value_free_func(target_value);

	if ((*param_ptr)->count < 1U)
	{
		zend_hash_del(params_ht, pname, pname_length);

#if SOLR_DEBUG
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Deleted last value from parameter. Removing parameter '%s' from object instance.", pname);
#endif

	}

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_SOLR_API int solr_delete_simple_list_param_value(zval *objptr, solr_char_t *pname, int pname_length, solr_char_t *pvalue, int pvalue_length TSRMLS_DC) */
PHP_SOLR_API int solr_delete_simple_list_param_value(zval *objptr, solr_char_t *pname, int pname_length, solr_char_t *pvalue, int pvalue_length TSRMLS_DC)
{
	solr_params_t *solr_params = NULL;
	solr_param_t **param_ptr = NULL;
	HashTable *params_ht = NULL;
	solr_param_value_t *target_value = NULL;

	if (!pname_length)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameter name");

		return FAILURE;
	}

	if (!pvalue_length)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameter value");

		return FAILURE;
	}

	if (solr_fetch_params_entry(objptr, &solr_params TSRMLS_CC) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "SolrParams instance could not be retrieved from HashTable");

		return FAILURE;
	}

	params_ht = solr_params->params;

	if (zend_hash_find(params_ht, pname, pname_length, (void **) &param_ptr) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "parameter could not be retrieved from HashTable");

		return FAILURE;
	}

	target_value = (solr_param_value_t *) pecalloc(1, sizeof(solr_param_value_t), SOLR_PARAMS_PERSISTENT);

	solr_string_appends(&(target_value->contents.simple_list), pvalue, pvalue_length);

	solr_params_delete_param_value((*param_ptr), target_value TSRMLS_CC);

	/* We are done with target_value. */
	(*param_ptr)->value_free_func(target_value);

	if ((*param_ptr)->count < 1U)
	{
		zend_hash_del(params_ht, pname, pname_length);

#if SOLR_DEBUG
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Deleted last value from parameter. Removing parameter '%s' from object instance.", pname);
#endif

	}

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_SOLR_API int solr_delete_arg_list_param_value(zval *objptr, solr_char_t *pname, int pname_length, solr_char_t *pvalue, int pvalue_length TSRMLS_DC) */
PHP_SOLR_API int solr_delete_arg_list_param_value(zval *objptr, solr_char_t *pname, int pname_length, solr_char_t *pvalue, int pvalue_length TSRMLS_DC)
{
	solr_params_t *solr_params = NULL;
	HashTable *params_ht = NULL;
	solr_param_t **param_ptr = NULL;
	solr_param_value_t *target_value = NULL;

	if (!pname_length)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameter name");

		return FAILURE;
	}

	if (!pvalue_length)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameter value");

		return FAILURE;
	}

	if (solr_fetch_params_entry(objptr, &solr_params TSRMLS_CC) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "SolrParams instance could not be retrieved from HashTable");

		return FAILURE;
	}

	params_ht = solr_params->params;

	if (zend_hash_find(params_ht, pname, pname_length, (void **) &param_ptr) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "parameter could not be retrieved from HashTable");

		return FAILURE;
	}

	target_value = (solr_param_value_t *) pecalloc(1, sizeof(solr_param_value_t), SOLR_PARAMS_PERSISTENT);

	solr_string_appends(&(target_value->contents.arg_list.value), pvalue, pvalue_length);

	solr_params_delete_param_value((*param_ptr), target_value TSRMLS_CC);

	/* We are done with target_value. */
	(*param_ptr)->value_free_func(target_value);

	if ((*param_ptr)->count < 1U)
	{
		zend_hash_del(params_ht, pname, pname_length);

#if SOLR_DEBUG
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Deleted last value from parameter. Removing parameter '%s' from object instance.", pname);
#endif

	}

	return SUCCESS;
}
/* }}} */

/* }}} */

/* {{{ PHP_SOLR_API int solr_param_find(zval *objptr, solr_char_t *pname, int pname_length, solr_param_t **solr_param TSRMLS_DC) */
PHP_SOLR_API int solr_param_find(zval *objptr, solr_char_t *pname, int pname_length, solr_param_t **solr_param TSRMLS_DC)
{
	solr_params_t *solr_params = NULL;
	HashTable *params_ht = NULL;

	solr_param_t **solr_param_tmp = NULL;

	if (!pname_length) {

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameter name");

		return FAILURE;
	}

	if (solr_fetch_params_entry(objptr, &solr_params TSRMLS_CC) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "SolrParams instance could not be retrieved from HashTable");

		return FAILURE;
	}

	params_ht = solr_params->params;

	if (zend_hash_find(params_ht, pname, pname_length, (void **) &solr_param_tmp) == FAILURE) {

		return FAILURE;
	}

	(*solr_param) = (*solr_param_tmp);

	return SUCCESS;
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


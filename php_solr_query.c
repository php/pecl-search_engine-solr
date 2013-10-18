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

/* $Id: php_solr_query.c 289604 2009-10-13 04:32:39Z iekpo $ */

#include "php_solr.h"

/* Outstanding Work/Changes */

/* TODO: Change SolrQuery::getTermsSort() to return integer */
/* TODO: Change SolrQuery::getFacetSort() to return integer */

/**
 * Note about methods implementation:
 *
 * One reason why each SolrQuery has custom code is because each method
 * could require separate tweaking.
 *
 * At this point in time, even though most of the SolrQuery methods share
 * basic features, I still believe that is a better idea to write separate code
 * for each method implementation.
 *
 * This will make the methods easier to maintain because
 *
 * from time to time, Solr modifies the way some of the request parameters are
 * submitted or processed.
 *
 * Hence, it is currently more logical to make each method an independent entity.
 */

/* {{{ proto SolrQuery::__construct([string q])
   Constructor for SolrQuery */
PHP_METHOD(SolrQuery, __construct)
{
	solr_char_t *q = NULL;
	int query_length = 0;
	solr_params_t *solr_params_dest = NULL;
	solr_params_t solr_params;
	long int params_index = SOLR_UNIQUE_PARAMS_INDEX();
	uint nSize = SOLR_INITIAL_HASH_TABLE_SIZE;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &q, &query_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid query parameter");

		return;
	}

	zend_update_property_long(solr_ce_SolrQuery, getThis(), SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, params_index TSRMLS_CC);

	memset(&solr_params, 0, sizeof(solr_params_t));

	if (zend_hash_index_update(SOLR_GLOBAL(params), params_index, (void *) &solr_params, sizeof(solr_params_t), (void **) &solr_params_dest) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error while registering query parameters in HashTable");

		return ;
	}

	solr_params_dest->params_index = params_index;
	solr_params_dest->params_count = 0U;

	/* Allocated memory for the parameters HashTable using fast cache for HashTables */
	ALLOC_HASHTABLE(solr_params_dest->params);

	zend_hash_init(solr_params_dest->params, nSize, NULL, (dtor_func_t) solr_destroy_param, SOLR_PARAMS_PERSISTENT);

	if (query_length) {

		if (solr_set_normal_param(getThis(), (solr_char_t *) "q", sizeof("q")-1, q, query_length) == FAILURE) {

			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error while setting query parameter");

			return;
		}
	}
}
/* }}} */

/* {{{ proto SolrQuery::__destruct()
   Destructor for SolrQuery */
PHP_METHOD(SolrQuery, __destruct)
{
	solr_params_t *solr_params = NULL;

	/* Retrieve the entry for this SolrParams instance */
	if (solr_fetch_params_entry(getThis(), &solr_params TSRMLS_CC) == SUCCESS) 	{

		zend_hash_index_del(SOLR_GLOBAL(params), solr_params->params_index);

		return ;
	}

	/* This would only happen if user attempted an illegal operation */
	php_error_docref(NULL TSRMLS_CC, E_ERROR, SOLR_ERROR_1008_MSG, SOLR_FILE_LINE_FUNC);
}
/* }}} */

/* {{{ CommonQueryParameters */

/* {{{ proto SolrQuery SolrQuery::setQuery(string q)
   Sets the q parameter */
PHP_METHOD(SolrQuery, setQuery)
{
	solr_char_t *param_name = (solr_char_t *) "q";
	int param_name_length = sizeof("q")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE) {

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setStart(int start)
   Sets the start parameter */
PHP_METHOD(SolrQuery, setStart)
{
	solr_char_t *param_name = (solr_char_t *) "start";
	int param_name_length = sizeof("start")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setRows(int rows)
   Sets the rows parameter */
PHP_METHOD(SolrQuery, setRows)
{
	solr_char_t *param_name = (solr_char_t *) "rows";
	int param_name_length = sizeof("rows")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::addField(string fl)
   Adds another fl parameter */
PHP_METHOD(SolrQuery, addField)
{
	solr_char_t *param_name = (solr_char_t *) "fl";
	int param_name_length = sizeof("fl")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_add_simple_list_param(getThis(), param_name, param_name_length, param_value, param_value_length TSRMLS_CC) == FAILURE)
	{
		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::addSortField(string fl [, int sort_direction])
   Adds another sort parameter */
PHP_METHOD(SolrQuery, addSortField)
{
	solr_char_t *param_name = (solr_char_t *) "sort";
	int param_name_length = sizeof("sort")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;
	long int sort_direction = 1L;
	solr_sort_dir_t sort_order = SOLR_SORT_DIR_DESC;
	solr_char_t *avalue = NULL;
	int avalue_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &param_value, &param_value_length, &sort_direction) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	sort_order = (sort_direction < 0L || sort_direction > 1L) ? SOLR_SORT_DIR_DESC : (solr_sort_dir_t) sort_direction;
	avalue = (sort_order) ? "desc" : "asc";
	avalue_length = solr_strlen(avalue);

	if (solr_add_arg_list_param(getThis(), param_name, param_name_length, param_value, param_value_length, avalue, avalue_length, ',', ' ' TSRMLS_CC) == FAILURE)
	{
		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::addFiterQuery(string fq)
   Adds another fq parameter */
PHP_METHOD(SolrQuery, addFilterQuery)
{
	solr_char_t *param_name = (solr_char_t *) "fq";
	int param_name_length = sizeof("fq")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_add_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setShowDebugInfo(bool flag)
   Sets the debugQuery parameter */
PHP_METHOD(SolrQuery, setShowDebugInfo)
{
	solr_char_t *param_name = (solr_char_t *) "debugQuery";
	int param_name_length = sizeof("debugQuery")-1;
	zend_bool show_debug_info = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &show_debug_info) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!show_debug_info)
	{
		solr_delete_solr_parameter(getThis(), param_name, param_name_length TSRMLS_CC);

		solr_return_solr_params_object();

		return;
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, "true", sizeof("true")-1) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error adding debugging info ");

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setExplainOther(string explainOther)
   Sets the explainOther parameter */
PHP_METHOD(SolrQuery, setExplainOther)
{
	solr_char_t *param_name = (solr_char_t *) "explainOther";
	int param_name_length = sizeof("explainOther")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setTimeAllowed(int milliseconds)
   Sets the maximum time in milliseconds allowed for the query */
PHP_METHOD(SolrQuery, setTimeAllowed)
{
	solr_char_t *param_name = (solr_char_t *) "timeAllowed";
	int param_name_length = sizeof("timeAllowed")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setOmitHeader(bool flag)
   Sets the omitHeader parameter */
PHP_METHOD(SolrQuery, setOmitHeader)
{
	solr_char_t *param_name = (solr_char_t *) "omitHeader";
	int param_name_length = sizeof("omitHeader")-1;
	int param_value_length = 0;
	zend_bool omit_header = 0;
	solr_char_t *omit_header_str = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &omit_header) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		RETURN_NULL();
	}

	omit_header_str = (omit_header)? "true" : "false";
	param_value_length = solr_strlen(omit_header_str);

	if (solr_set_normal_param(getThis(), param_name, param_name_length, omit_header_str, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, omit_header_str);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* }}} END OF CommonQueryParameters */

/* {{{ CoreQueryParameters */

/* {{{ proto SolrQuery SolrQuery::setEchoHandler(bool flag)
   Sets the echoHandler parameter */
PHP_METHOD(SolrQuery, setEchoHandler)
{
	solr_char_t *param_name = (solr_char_t *) "echoHandler";
	int param_name_length = sizeof("echoHandler")-1;
	int param_value_length = 0;
	zend_bool echo_handler = 0;
	solr_char_t *echo_handler_str = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &echo_handler) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		RETURN_NULL();
	}

	echo_handler_str = (echo_handler)? "true" : "false";
	param_value_length = solr_strlen(echo_handler_str);

	if (solr_set_normal_param(getThis(), param_name, param_name_length, echo_handler_str, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, echo_handler_str);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */


/* {{{ proto SolrQuery SolrQuery::setEchoParams(string value)
   Sets the echoParams parameter */
PHP_METHOD(SolrQuery, setEchoParams)
{
	solr_char_t *param_name = (solr_char_t *) "echoParams";
	int param_name_length = sizeof("echoParams")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* }}} END OF CoreQueryParameters */

/* {{{ SimpleFacetParameters */

/* {{{ proto SolrQuery SolrQuery::setFacet(bool value)
   Sets the facet parameter */
PHP_METHOD(SolrQuery, setFacet)
{
	solr_char_t *param_name = (solr_char_t *) "facet";
	int param_name_length = sizeof("facet")-1;
	zend_bool bool_flag = 0;
	solr_char_t *bool_flag_str = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &bool_flag) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		RETURN_NULL();
	}

	bool_flag_str = ((bool_flag)? "true" : "false");
	param_value_length  = solr_strlen(bool_flag_str);

	if (solr_set_normal_param(getThis(), param_name, param_name_length, bool_flag_str, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, bool_flag_str);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::addFacetField(string value)
   Sets the facet.field parameter */
PHP_METHOD(SolrQuery, addFacetField)
{
	solr_char_t *param_name = (solr_char_t *) "facet.field";
	int param_name_len = sizeof("facet.field")-1;
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_add_normal_param(getThis(), param_name, param_name_len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to add param value %s to %s ", param_value, param_name);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::addFacetQuery(string value)
   Adds another facet.query parameter */
PHP_METHOD(SolrQuery, addFacetQuery)
{
	solr_char_t *param_name = (solr_char_t *) "facet.query";
	int param_name_length = sizeof("facet.query")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_add_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setFacetPrefix(string value [, string field_override])
   Sets the facet.prefix parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setFacetPrefix)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "facet.prefix");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setFacetSort(int value [, string field_override])
   Sets the facet.sort parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setFacetSort)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	long int sort_type = 0L;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|s", &sort_type, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "facet.sort");

	param_value = ((sort_type)? "count" : "index");
	param_value_len = solr_strlen(param_value);

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setFacetLimit(string value [, string field_override])
   Sets the facet.limit parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setFacetLimit)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "facet.limit");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setFacetOffset(string value [, string field_override])
   Sets the facet.offset parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setFacetOffset)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "facet.offset");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setFacetMinCount(string value [, string field_override])
   Sets the facet.mincount parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setFacetMinCount)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "facet.mincount");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setFacetMissing(bool value [, string field_override])
   Sets the facet.missing parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setFacetMissing)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	zend_bool bool_flag = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b|s", &bool_flag, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "facet.missing");

	param_value = ((bool_flag)? "true" : "false");
	param_value_len = solr_strlen(param_value);

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setFacetMethod(string value [, string field_override])
   Sets the facet.method parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setFacetMethod)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "facet.method");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setFacetEnumCacheMinDefaultFrequency(string value [, string field_override])
   Sets the facet.enum.cache.minDf parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setFacetEnumCacheMinDefaultFrequency)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "facet.enum.cache.minDf");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();

}
/* }}} */

/* {{{ Date facet parameters */

/* {{{ proto SolrQuery SolrQuery::addFacetDateField(string value)
  Adds another facet.date parameter. */
PHP_METHOD(SolrQuery, addFacetDateField)
{
	solr_char_t *param_name = (solr_char_t *) "facet.date";
	int param_name_length = sizeof("facet.date")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_add_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setFacetDateStart(string value [, string field_override])
   Sets the facet.date.start parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setFacetDateStart)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid  parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "facet.date.start");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setFacetDateEnd(string value [, string field_override])
   Sets the facet.date.end parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setFacetDateEnd)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "facet.date.end");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setFacetDateGap(string value [, string field_override])
   Sets the facet.date.gap parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setFacetDateGap)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "facet.date.gap");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setFacetDateHardEnd(bool value [, string field_override])
   Sets the facet.date.hardend parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setFacetDateHardEnd)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	zend_bool bool_flag = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b|s", &bool_flag, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "facet.date.hardend");

	param_value = ((bool_flag)? "true" : "false");
	param_value_len = solr_strlen(param_value);

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::addFacetDateOther(string value [, string field_override])
   Sets the facet.date.other parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, addFacetDateOther)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "facet.date.other");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* }}} End of date facet parameters */

/* }}} End of SimpleFacetParameters */

/* {{{ HighlightingParameters */

/* {{{ proto SolrQuery SolrQuery::setHighlight(bool value)
   Sets the hl parameter. This enables or disables highlighting. */
PHP_METHOD(SolrQuery, setHighlight)
{
	solr_char_t *param_name = (solr_char_t *) "hl";
	int param_name_length = sizeof("hl")-1;
	zend_bool bool_flag = 0;
	solr_char_t *bool_flag_str = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &bool_flag) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		RETURN_NULL();
	}

	bool_flag_str = ((bool_flag)? "true" : "false");
	param_value_length  = solr_strlen(bool_flag_str);

	if (solr_set_normal_param(getThis(), param_name, param_name_length, bool_flag_str, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, bool_flag_str);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::addHighlightField(string value)
   Adds another hl.fl parameter. */
PHP_METHOD(SolrQuery, addHighlightField)
{
	solr_char_t *list_param_name = (solr_char_t *) "hl.fl";
	int list_param_name_len = sizeof("hl.fl")-1;
	solr_char_t *list_param_value = NULL;
	int list_param_value_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &list_param_value, &list_param_value_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_add_simple_list_param(getThis(), list_param_name, list_param_name_len, list_param_value, list_param_value_len TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to add param value %s to %s list ", list_param_value, list_param_name);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightSnippets(string value [, string field_override])
   Sets the hl.snippets parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setHighlightSnippets)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "hl.snippets");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightFragsize(string value [, string field_override])
   Sets the hl.fragsize parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setHighlightFragsize)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "hl.fragsize");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();

}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightMergeContiguous(bool flag [, string field_override])
   Sets the hl.mergeContiguous parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setHighlightMergeContiguous)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	zend_bool bool_flag = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b|s", &bool_flag, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "hl.mergeContiguous");

	param_value = ((bool_flag)? "true" : "false");
	param_value_len = solr_strlen(param_value);

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightRequireFieldMatch(bool flag)
   Sets the hl.requireFieldMatch.  */
PHP_METHOD(SolrQuery, setHighlightRequireFieldMatch)
{
	solr_char_t *param_name = (solr_char_t *) "hl.requireFieldMatch";
	int param_name_length = sizeof("hl.requireFieldMatch")-1;
	zend_bool bool_flag = 0;
	solr_char_t *bool_flag_str = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &bool_flag) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		RETURN_NULL();
	}

	bool_flag_str = ((bool_flag)? "true" : "false");
	param_value_length  = solr_strlen(bool_flag_str);

	if (solr_set_normal_param(getThis(), param_name, param_name_length, bool_flag_str, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, bool_flag_str);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightMaxAnalyzedChars(string value)
   Sets the hl.maxAnalyzedChars parameter */
PHP_METHOD(SolrQuery, setHighlightMaxAnalyzedChars)
{
	solr_char_t *param_name = (solr_char_t *) "hl.maxAnalyzedChars";
	int param_name_length = sizeof("hl.maxAnalyzedChars")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightAlternateField(string value [, string field_override])
   Sets the hl.alternateField parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setHighlightAlternateField)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "hl.alternateField");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightMaxAlternateFieldLength(string value [, string field_override])
   Sets the hl.maxAlternateFieldLength parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setHighlightMaxAlternateFieldLength)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "hl.maxAlternateFieldLength");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightFormatter(string value [, string field_override])
   Sets the hl.formatter parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setHighlightFormatter)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = "simple";
	int param_value_len = sizeof("simple")-1;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "hl.formatter");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightSimplePre(string value [, string field_override])
   Sets the hl.simple.pre parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setHighlightSimplePre)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = "<em>";
	int param_value_len = sizeof("<em>")-1;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "hl.simple.pre");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightSimplePost(string value [, string field_override])
   Sets the hl.simple.post parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setHighlightSimplePost)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = "</em>";
	int param_value_len = sizeof("</em>")-1;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "hl.simple.post");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightFragmenter(string value [, string field_override])
   Sets the hl.fragmenter parameter. Accepts an optional field override. */
PHP_METHOD(SolrQuery, setHighlightFragmenter)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "hl.fragmenter");

	if (solr_set_normal_param(getThis(), fbuf.str, fbuf.len, param_value, param_value_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", fbuf.str, param_value);

		solr_string_free(&fbuf);

		RETURN_NULL();
	}

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightUsePhraseHighlighter(bool flag)
   Sets the hl.usePhraseHighlighter parameter.  */
PHP_METHOD(SolrQuery, setHighlightUsePhraseHighlighter)
{
	solr_char_t *param_name = (solr_char_t *) "hl.usePhraseHighlighter";
	int param_name_length = sizeof("hl.usePhraseHighlighter")-1;
	zend_bool bool_flag = 0;
	solr_char_t *bool_flag_str = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &bool_flag) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		RETURN_NULL();
	}

	bool_flag_str = ((bool_flag)? "true" : "false");

	param_value_length  = solr_strlen(bool_flag_str);

	if (solr_set_normal_param(getThis(), param_name, param_name_length, bool_flag_str, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, bool_flag_str);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightHighlightMultiTerm(bool flag)
   Sets the hl.highlightMultiTerm parameter.  */
PHP_METHOD(SolrQuery, setHighlightHighlightMultiTerm)
{
	solr_char_t *param_name = (solr_char_t *) "hl.highlightMultiTerm";
	int param_name_length = sizeof("hl.highlightMultiTerm")-1;
	zend_bool bool_flag = 0;
	solr_char_t *bool_flag_str = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &bool_flag) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		RETURN_NULL();
	}

	bool_flag_str = ((bool_flag)? "true" : "false");

	param_value_length  = solr_strlen(bool_flag_str);

	if (solr_set_normal_param(getThis(), param_name, param_name_length, bool_flag_str, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, bool_flag_str);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightRegexSlop(string value)
   Sets the hl.regex.slop parameter.  */
PHP_METHOD(SolrQuery, setHighlightRegexSlop)
{
	solr_char_t *param_name = (solr_char_t *) "hl.regex.slop";
	int param_name_length = sizeof("hl.regex.slop")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightRegexPattern(string value)
   Sets the hl.regex.pattern parameter.  */
PHP_METHOD(SolrQuery, setHighlightRegexPattern)
{
	solr_char_t *param_name = (solr_char_t *) "hl.regex.pattern";
	int param_name_length = sizeof("hl.regex.pattern")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setHighlightRegexMaxAnalyzedChars(string value)
   Sets the hl.regex.maxAnalyzedChars parameter.  */
PHP_METHOD(SolrQuery, setHighlightRegexMaxAnalyzedChars)
{
	solr_char_t *param_name = (solr_char_t *) "hl.regex.maxAnalyzedChars";
	int param_name_length = sizeof("hl.regex.maxAnalyzedChars")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* }}} End of HighlightingParameters */

/* {{{ StatsComponent */

/* {{{ proto SolrQuery SolrQuery::setStats(bool flag)
   Sets the stats parameter. Enables or disables stats */
PHP_METHOD(SolrQuery, setStats)
{
	solr_char_t *param_name = (solr_char_t *) "stats";
	int param_name_length = sizeof("stats")-1;
	zend_bool bool_flag = 0;
	solr_char_t *bool_flag_str = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &bool_flag) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		RETURN_NULL();
	}

	bool_flag_str = ((bool_flag)? "true" : "false");

	param_value_length  = solr_strlen(bool_flag_str);

	if (solr_set_normal_param(getThis(), param_name, param_name_length, bool_flag_str, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, bool_flag_str);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::addStatsField(string value)
   Adds another stats.field parameter.  */
PHP_METHOD(SolrQuery, addStatsField)
{
	solr_char_t *param_name = (solr_char_t *) "stats.field";
	int param_name_length = sizeof("stats.field")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_add_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error adding parameter %s=%s ", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::addStatsFacet(string value)
   Adds another stats.facet parameter.  */
PHP_METHOD(SolrQuery, addStatsFacet)
{
	solr_char_t *param_name = (solr_char_t *) "stats.facet";
	int param_name_length = sizeof("stats.facet")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_add_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error adding parameter %s=%s ", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* }}} End of StatsComponent */

/* {{{ MoreLikeThis */

/* {{{ proto SolrQuery SolrQuery::setMlt(bool flag)
   Sets the mlt parameter. Enables or disables the moreLikeThis component */
PHP_METHOD(SolrQuery, setMlt)
{
	solr_char_t *param_name = (solr_char_t *) "mlt";
	int param_name_length = sizeof("mlt")-1;
	zend_bool bool_flag = 0;
	solr_char_t *bool_flag_str = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &bool_flag) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		RETURN_NULL();
	}

	bool_flag_str = ((bool_flag)? "true" : "false");

	param_value_length  = solr_strlen(bool_flag_str);

	if (solr_set_normal_param(getThis(), param_name, param_name_length, bool_flag_str, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, bool_flag_str);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setMltCount(string value)
   Sets the mlt.count parameter. */
PHP_METHOD(SolrQuery, setMltCount)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.count";
	int param_name_length = sizeof("mlt.count")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::addMltField(string field)
   Adds another field name to the mlt.fl parameter. */
PHP_METHOD(SolrQuery, addMltField)
{
	solr_char_t *list_param_name = (solr_char_t *) "mlt.fl";
	int list_param_name_len = sizeof("mlt.fl")-1;
	solr_char_t *list_param_value = NULL;
	int list_param_value_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &list_param_value, &list_param_value_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_add_simple_list_param(getThis(), list_param_name, list_param_name_len, list_param_value, list_param_value_len TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to add param value %s to %s list ", list_param_value, list_param_name);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::addMltQueryField(string value, string boost)
   Adds another query field and boost value to the mlt.qf parameter. */
PHP_METHOD(SolrQuery, addMltQueryField)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.qf";
	int param_name_length = sizeof("mlt.qf")-1;
	solr_char_t *query_field = NULL;
	int query_field_length = 0;
	solr_char_t *boost_value = "1.0";
	int boost_value_length = sizeof("1.0");

	/* TODO: make boost optional parameter. */
	/* If boost is not sent, then the index time boost is used */
	/* This will involve re-doing all the arg_list functions to allow optional args. */
	/* Temporary solution is to use SolrQuery::add("mlt.qf", "value"). This should be documented. */

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &query_field, &query_field_length, &boost_value, &boost_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_add_arg_list_param(getThis(), param_name, param_name_length, query_field, query_field_length, boost_value, boost_value_length, ' ', '^' TSRMLS_CC) == FAILURE)
	{
		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setMltMinTermFrequency(string value)
   Sets the mlt.mintf parameter. */
PHP_METHOD(SolrQuery, setMltMinTermFrequency)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.mintf";
	int param_name_length = sizeof("mlt.mintf")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setMltMinDocFrequency(string value)
   Sets the mlt.mindf parameter. */
PHP_METHOD(SolrQuery, setMltMinDocFrequency)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.mindf";
	int param_name_length = sizeof("mlt.mindf")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setMltMinWordLength(string value)
   Sets the mlt.minwl parameter. */
PHP_METHOD(SolrQuery, setMltMinWordLength)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.minwl";
	int param_name_length = sizeof("mlt.minwl")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setMltMaxWordLength(string value)
   Sets the mlt.maxwl parameter. */
PHP_METHOD(SolrQuery, setMltMaxWordLength)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.maxwl";
	int param_name_length = sizeof("mlt.maxwl")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setMltMaxNumTokens(string value)
   Sets the mlt.maxntp parameter. */
PHP_METHOD(SolrQuery, setMltMaxNumTokens)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.maxntp";
	int param_name_length = sizeof("mlt.maxntp")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setMltMaxNumQueryTerms(string value)
   Sets the mlt.maxqt parameter. */
PHP_METHOD(SolrQuery, setMltMaxNumQueryTerms)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.maxqt";
	int param_name_length = sizeof("mlt.maxqt")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setMltBoost(bool flag)
   Sets the mlt.boost parameter. */
PHP_METHOD(SolrQuery, setMltBoost)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.boost";
	int param_name_length = sizeof("mlt.boost")-1;
	zend_bool bool_flag = 0;
	solr_char_t *bool_flag_str = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &bool_flag) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		RETURN_NULL();
	}

	bool_flag_str = ((bool_flag)? "true" : "false");

	param_value_length  = solr_strlen(bool_flag_str);

	if (solr_set_normal_param(getThis(), param_name, param_name_length, bool_flag_str, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, bool_flag_str);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* }}} End of MoreLikeThis */

/* {{{ TermsComponent */

/* {{{ proto SolrQuery SolrQuery::setTerms(bool flag)
   Sets the terms parameter. This flag enables or disables the TermsComponent */
PHP_METHOD(SolrQuery, setTerms)
{
	solr_char_t *param_name = (solr_char_t *) "terms";
	int param_name_length = sizeof("terms")-1;
	zend_bool bool_flag = 0;
	solr_char_t *bool_flag_str = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &bool_flag) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		RETURN_NULL();
	}

	bool_flag_str = ((bool_flag)? "true" : "false");

	param_value_length = solr_strlen(bool_flag_str);

	if (solr_set_normal_param(getThis(), param_name, param_name_length, bool_flag_str, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, bool_flag_str);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setTermsField(string field)
   Sets the terms.fl parameter. */
PHP_METHOD(SolrQuery, setTermsField)
{
	solr_char_t *param_name = (solr_char_t *) "terms.fl";
	int param_name_length = sizeof("terms.fl")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setTermsLowerBound(string value)
   Sets the terms.lower parameter. */
PHP_METHOD(SolrQuery, setTermsLowerBound)
{
	solr_char_t *param_name = (solr_char_t *) "terms.lower";
	int param_name_length = sizeof("terms.lower")-1;

	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setTermsUpperBound(string value)
   Sets the terms.upper parameter. */
PHP_METHOD(SolrQuery, setTermsUpperBound)
{
	solr_char_t *param_name = (solr_char_t *) "terms.upper";
	int param_name_length = sizeof("terms.upper")-1;

	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setTermsIncludeLowerBound(string value)
   Sets the terms.lower.incl parameter. */
PHP_METHOD(SolrQuery, setTermsIncludeLowerBound)
{
	solr_char_t *param_name = (solr_char_t *) "terms.lower.incl";
	int param_name_length = sizeof("terms.lower.incl")-1;
	zend_bool bool_flag = 0;
	solr_char_t *bool_flag_str = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &bool_flag) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		RETURN_NULL();
	}

	bool_flag_str = ((bool_flag)? "true" : "false");

	param_value_length = solr_strlen(bool_flag_str);

	if (solr_set_normal_param(getThis(), param_name, param_name_length, bool_flag_str, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, bool_flag_str);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setTermsIncludeUpperBound(string value)
   Sets the terms.upper.incl parameter. */
PHP_METHOD(SolrQuery, setTermsIncludeUpperBound)
{
	solr_char_t *param_name = (solr_char_t *) "terms.upper.incl";
	int param_name_length = sizeof("terms.upper.incl")-1;
	zend_bool bool_flag = 0;
	solr_char_t *bool_flag_str = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &bool_flag) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		RETURN_NULL();
	}

	bool_flag_str = ((bool_flag)? "true" : "false");

	param_value_length = solr_strlen(bool_flag_str);

	if (solr_set_normal_param(getThis(), param_name, param_name_length, bool_flag_str, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, bool_flag_str);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setTermsMinCount(string value)
   Sets the terms.mincount parameter. */
PHP_METHOD(SolrQuery, setTermsMinCount)
{
	solr_char_t *param_name  = (solr_char_t *) "terms.mincount";
	int param_name_length    = sizeof("terms.mincount")-1;

	solr_char_t *param_value = NULL;
	int param_value_length   = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setTermsMaxCount(string value)
   Sets the terms.maxcount parameter. */
PHP_METHOD(SolrQuery, setTermsMaxCount)
{
	solr_char_t *param_name  = (solr_char_t *) "terms.maxcount";
	int param_name_length    = sizeof("terms.maxcount")-1;

	solr_char_t *param_value = NULL;
	int param_value_length   = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setTermsPrefix(string value)
   Sets the terms.prefix parameter. */
PHP_METHOD(SolrQuery, setTermsPrefix)
{
	solr_char_t *param_name  = (solr_char_t *) "terms.prefix";
	int param_name_length    = sizeof("terms.prefix")-1;

	solr_char_t *param_value = NULL;
	int param_value_length   = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setTermsLimit(string value)
   Sets the terms.limit parameter. */
PHP_METHOD(SolrQuery, setTermsLimit)
{
	solr_char_t *param_name = (solr_char_t *) "terms.limit";
	int param_name_length = sizeof("terms.limit")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_set_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s", param_name, param_value);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setTermsReturnRaw(bool flag)
   Sets the terms.raw parameter. */
PHP_METHOD(SolrQuery, setTermsReturnRaw)
{
	solr_char_t *param_name = (solr_char_t *) "terms.raw";
	int param_name_length = sizeof("terms.raw")-1;
	zend_bool bool_flag = 0;
	solr_char_t *bool_flag_str = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &bool_flag) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		RETURN_NULL();
	}

	bool_flag_str = ((bool_flag)? "true" : "false");

	param_value_length = solr_strlen(bool_flag_str);

	if (solr_set_normal_param(getThis(), param_name, param_name_length, bool_flag_str, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, bool_flag_str);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery SolrQuery::setTermsSort(int sort)
   Sets the terms.sort parameter. */
PHP_METHOD(SolrQuery, setTermsSort)
{
	solr_char_t *param_name = (solr_char_t *) "terms.sort";
	int param_name_length = sizeof("terms.sort")-1;
	long int sort_type = 0L;
	solr_char_t *sort_type_str = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &sort_type) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		RETURN_NULL();
	}

	sort_type_str = ((sort_type)? "count" : "index");
	param_value_length  = solr_strlen(sort_type_str);

	if (solr_set_normal_param(getThis(), param_name, param_name_length, sort_type_str, param_value_length) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error setting parameter %s=%s ", param_name, sort_type_str);

		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* }}} End of TermsComponent */

/* {{{ Value removal methods */

/* {{{ proto SolrQuery SolrQuery::removeField(string fl)
   Removes a field from the fl parameter */
PHP_METHOD(SolrQuery, removeField)
{
	solr_char_t *pname = (solr_char_t *) "fl";
	int pname_length = sizeof("fl")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_delete_simple_list_param_value(getThis(), pname, pname_length, param_value, param_value_length TSRMLS_CC);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{  proto SolrQuery SolrQuery::removeSortField(string fl)
   Removes a sort field from the sort parameter. */
PHP_METHOD(SolrQuery, removeSortField)
{
	solr_char_t *pname = (solr_char_t *) "sort";
	int pname_length = sizeof("sort")-1;

	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_delete_arg_list_param_value(getThis(), pname, pname_length, param_value, param_value_length TSRMLS_CC);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{  proto SolrQuery SolrQuery::removeFilterQuery(string fq)
   Removes one of the fq parameter. */
PHP_METHOD(SolrQuery, removeFilterQuery)
{
	solr_char_t *pname = (solr_char_t *) "fq";
	int pname_length = sizeof("fq")-1;

	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_delete_normal_param_value(getThis(), pname, pname_length, param_value, param_value_length TSRMLS_CC);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{  proto SolrQuery SolrQuery::removeFacetField(string field)
   Removes one of fields from the facet.field parameter. */
PHP_METHOD(SolrQuery, removeFacetField)
{
	solr_char_t *pname = (solr_char_t *) "facet.field";
	int pname_length = sizeof("facet.field")-1;

	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_delete_normal_param_value(getThis(), pname, pname_length, param_value, param_value_length TSRMLS_CC);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{  proto SolrQuery SolrQuery::removeFacetQuery(string facet_query)
   Removes one of the facet.query parameters. */
PHP_METHOD(SolrQuery, removeFacetQuery)
{
	solr_char_t *pname  = (solr_char_t *) "facet.query";
	int pname_length    = sizeof("facet.query")-1;

	solr_char_t *param_value = NULL;
	int param_value_length   = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_delete_normal_param_value(getThis(), pname, pname_length, param_value, param_value_length TSRMLS_CC);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{  proto SolrQuery SolrQuery::removeFacetDateField(string date_field)
   Removes one of the facet.date parameters. */
PHP_METHOD(SolrQuery, removeFacetDateField)
{
	solr_char_t *pname  = (solr_char_t *) "facet.date";
	int pname_length    = sizeof("facet.date")-1;

	solr_char_t *param_value = NULL;
	int param_value_length   = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_delete_normal_param_value(getThis(), pname, pname_length, param_value, param_value_length TSRMLS_CC);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{  proto SolrQuery SolrQuery::removeFacetDateOther(string value [, string field_override])
   Removes one of the facet.date.other parameters. Also accepts an optional field override. */
PHP_METHOD(SolrQuery, removeFacetDateOther)
{
	solr_string_t fbuf; /* Field name buffer to prepare field override */

	/* Parameter value */
	solr_char_t *param_value = NULL;
	int param_value_len = 0;

	/* Field name override,f if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	memset(&fbuf, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &param_value, &param_value_len, &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_query_field_override(&fbuf, field_name, field_name_len, "facet.date.other");

	solr_delete_normal_param_value(getThis(), fbuf.str, fbuf.len, param_value, param_value_len TSRMLS_CC);

	solr_string_free(&fbuf);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{  proto SolrQuery SolrQuery::removeHighlightField(string field)
   Removes one of the fields from the hl.fl parameter. */
PHP_METHOD(SolrQuery, removeHighlightField)
{
	solr_char_t *pname = (solr_char_t *) "hl.fl";
	int pname_length = sizeof("hl.fl")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_delete_simple_list_param_value(getThis(), pname, pname_length, param_value, param_value_length TSRMLS_CC);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{  proto SolrQuery SolrQuery::removeStatsField(string field)
   Removes one of the stats.field parameters. */
PHP_METHOD(SolrQuery, removeStatsField)
{
	solr_char_t *pname = (solr_char_t *) "stats.field";
	int pname_length = sizeof("stats.field")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_delete_normal_param_value(getThis(), pname, pname_length, param_value, param_value_length TSRMLS_CC);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{  proto SolrQuery SolrQuery::removeStatsFacet(string value)
   Removes one of the stats.facet parameters. */
PHP_METHOD(SolrQuery, removeStatsFacet)
{
	solr_char_t *pname = (solr_char_t *) "stats.facet";
	int pname_length = sizeof("stats.facet")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_delete_normal_param_value(getThis(), pname, pname_length, param_value, param_value_length TSRMLS_CC);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{  proto SolrQuery SolrQuery::removeMltField(string field)
   Removes one of the fields from the mlt.fl parameter. */
PHP_METHOD(SolrQuery, removeMltField)
{
	solr_char_t *pname = (solr_char_t *) "mlt.fl";
	int pname_length = sizeof("mlt.fl")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_delete_simple_list_param_value(getThis(), pname, pname_length, param_value, param_value_length TSRMLS_CC);

	solr_return_solr_params_object();
}
/* }}} */

/* {{{  proto SolrQuery SolrQuery::removeMltQueryField(string field)
   Removes one of the values from the mlt.qf parameter. */
PHP_METHOD(SolrQuery, removeMltQueryField)
{
	solr_char_t *pname = (solr_char_t *) "mlt.qf";
	int pname_length = sizeof("mlt.qf")-1;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	solr_delete_arg_list_param_value(getThis(), pname, pname_length, param_value, param_value_length TSRMLS_CC);

	solr_return_solr_params_object();
}
/* }}} */

/* }}} End of Value removal methods  */

/* {{{ Begin getter methods */

/* {{{ proto string SolrQuery::getQuery()
	 Returns the query */
PHP_METHOD(SolrQuery, getQuery)
{
	solr_char_t *param_name = (solr_char_t *) "q";
	int param_name_length = sizeof("q")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_string(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getStart()
	 Returns the start parameter */
PHP_METHOD(SolrQuery, getStart)
{
	solr_char_t *param_name = (solr_char_t *) "start";
	int param_name_length = sizeof("start")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_integer(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getRows()
	 Returns the rows parameter */
PHP_METHOD(SolrQuery, getRows)
{
	solr_char_t *param_name = (solr_char_t *) "rows";
	int param_name_length = sizeof("rows")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_integer(solr_param, return_value);
}
/* }}} */

/* {{{ proto array SolrQuery::getFields()
	 Returns the fields */
PHP_METHOD(SolrQuery, getFields)
{
	solr_char_t *param_name = (solr_char_t *) "fl";
	int param_name_length = sizeof("fl")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	array_init(return_value);

	solr_simple_list_param_value_display(solr_param, return_value);
}
/* }}} */

/* {{{ proto array SolrQuery::getSortFields()
	 Returns all the sort fields */
PHP_METHOD(SolrQuery, getSortFields)
{
	solr_char_t *param_name = (solr_char_t *) "sort";
	int param_name_length = sizeof("sort")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	array_init(return_value);

	solr_arg_list_param_value_display(solr_param, return_value);

}
/* }}} */

/* {{{ proto string SolrQuery::getFilterQueries()
	 Returns all the filter queries */
PHP_METHOD(SolrQuery, getFilterQueries)
{
	solr_char_t *param_name = (solr_char_t *) "fq";
	int param_name_length = sizeof("fq")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	array_init(return_value);

	solr_normal_param_value_display(solr_param, return_value);
}
/* }}} */

/* {{{ proto string SolrQuery::getTimeAllowed()
	 Returns the maximum time in milliseconds allowed for the search query */
PHP_METHOD(SolrQuery, getTimeAllowed)
{
	solr_char_t *param_name = (solr_char_t *) "timeAllowed";
	int param_name_length = sizeof("timeAllowed")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_integer(solr_param, return_value);
}
/* }}} */

/* {{{ proto bool SolrQuery::getFacet()
	 Returns true is faceting is enabled */
PHP_METHOD(SolrQuery, getFacet)
{
	solr_char_t *param_name = (solr_char_t *) "facet";
	int param_name_length = sizeof("facet")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_boolean(solr_param, return_value);
}
/* }}} */

/* {{{ proto string SolrQuery::getFacetFields()
	 Returns all the facet fields */
PHP_METHOD(SolrQuery, getFacetFields)
{
	solr_char_t *param_name = (solr_char_t *) "facet.field";
	int param_name_length = sizeof("facet.field")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	array_init(return_value);

	solr_normal_param_value_display(solr_param, return_value);
}
/* }}} */

/* {{{ proto string SolrQuery::getFacetQueries()
	 Returns all the facet queries */
PHP_METHOD(SolrQuery, getFacetQueries)
{
	solr_char_t *param_name = (solr_char_t *) "facet.query";
	int param_name_length = sizeof("facet.query")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	array_init(return_value);

	solr_normal_param_value_display(solr_param, return_value);
}
/* }}} */

/* {{{ proto string SolrQuery::getFacetPrefix([string field_override])
	 Returns the prefix for the facet */
PHP_METHOD(SolrQuery, getFacetPrefix)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "facet.prefix");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_string(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto int SolrQuery::getFacetSort([string field_override])
	 Returns the facet sort state (for the field, if it was overridden) */
PHP_METHOD(SolrQuery, getFacetSort)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "facet.sort");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_sort_type(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto int SolrQuery::getFacetLimit([string field_override])
	 Returns the maximum number of items for the facet */
PHP_METHOD(SolrQuery, getFacetLimit)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "facet.limit");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_integer(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto int SolrQuery::getFacetOffset([string field_override])
	 Returns the offset into the list of constraints */
PHP_METHOD(SolrQuery, getFacetOffset)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "facet.offset");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_integer(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto int SolrQuery::getFacetMinCount([string field_override])
	 Returns the minimum count for the facet */
PHP_METHOD(SolrQuery, getFacetMinCount)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "facet.mincount");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_integer(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto bool SolrQuery::getFacetMissing([string field_override])
	 Returns the facet.missing parameter */
PHP_METHOD(SolrQuery, getFacetMissing)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "facet.missing");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_boolean(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto string SolrQuery::getFacetMethod([string field_override])
	 Returns the facet.method parameter */
PHP_METHOD(SolrQuery, getFacetMethod)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "facet.method");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_string(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto array SolrQuery::getFacetDateFields()
	 Returns all the facet.date fields */
PHP_METHOD(SolrQuery, getFacetDateFields)
{
	solr_char_t *param_name = (solr_char_t *) "facet.date";
	int param_name_length = sizeof("facet.date")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	array_init(return_value);

	solr_normal_param_value_display(solr_param, return_value);
}
/* }}} */

/* {{{ proto string SolrQuery::getFacetDateStart([string field_override])
	 Returns the facet.date.start parameter */
PHP_METHOD(SolrQuery, getFacetDateStart)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "facet.date.start");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_string(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto string SolrQuery::getFacetDateEnd([string field_override])
	 Returns the facet.date.end parameter */
PHP_METHOD(SolrQuery, getFacetDateEnd)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "facet.date.end");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_string(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto string SolrQuery::getFacetDateGap([string field_override])
	 Returns the facet.date.gap */
PHP_METHOD(SolrQuery, getFacetDateGap)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "facet.date.gap");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_string(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto bool SolrQuery::getFacetDateHardEnd([string field_override])
	 Returns the facet.date.hardend parameter */
PHP_METHOD(SolrQuery, getFacetDateHardEnd)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "facet.date.hardend");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_boolean(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto string SolrQuery::getFacetDateOther([string field_override])
	 Returns the facet.date.other parameter */
PHP_METHOD(SolrQuery, getFacetDateOther)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "facet.date.other");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		array_init(return_value);

		solr_normal_param_value_display(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto bool SolrQuery::getHighlight()
	 Returns the state of the hl parameter */
PHP_METHOD(SolrQuery, getHighlight)
{
	solr_char_t *param_name = (solr_char_t *) "hl";
	int param_name_length = sizeof("hl")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_boolean(solr_param, return_value);
}
/* }}} */

/* {{{ proto array SolrQuery::getHighlightFields()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightFields)
{
	solr_char_t *param_name = (solr_char_t *) "hl.fl";
	int param_name_length = sizeof("hl.fl")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	array_init(return_value);

	solr_simple_list_param_value_display(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getHighlightSnippets([string field_override])
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightSnippets)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "hl.snippets");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_integer(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto int SolrQuery::getHighlightFragsize([string field_override])
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightFragsize)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "hl.fragsize");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_integer(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto bool SolrQuery::getHighlightMergeContiguous([string field_override])
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightMergeContiguous)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "hl.mergeContiguous");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_boolean(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto bool SolrQuery::getHighlightRequireFieldMatch()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightRequireFieldMatch)
{
	solr_char_t *param_name = (solr_char_t *) "hl.requireFieldMatch";
	int param_name_length = sizeof("hl.requireFieldMatch")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_boolean(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getHighlightMaxAnalyzedChars()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightMaxAnalyzedChars)
{
	solr_char_t *param_name = (solr_char_t *) "hl.maxAnalyzedChars";
	int param_name_length = sizeof("hl.maxAnalyzedChars")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_integer(solr_param, return_value);
}
/* }}} */

/* {{{ proto string SolrQuery::getHighlightAlternateField([string field_override])
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightAlternateField)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "hl.alternateField");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_string(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto int SolrQuery::getHighlightMaxAlternateFieldLength([string field_override])
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightMaxAlternateFieldLength)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "hl.maxAlternateFieldLength");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_integer(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto string SolrQuery::getHighlightFormatter([string field_override])
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightFormatter)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "hl.formatter");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_string(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto string SolrQuery::getHighlightSimplePre([string field_override])
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightSimplePre)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "hl.simple.pre");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_string(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto string SolrQuery::getHighlightSimplePost([string field_override])
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightSimplePost)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "hl.simple.post");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_string(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto string SolrQuery::getHighlightFragmenter([string field_override])
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightFragmenter)
{
	solr_param_t *solr_param = NULL;

	solr_string_t field_override_buffer; /* Field name buffer to prepare field override */

	/* Field name override, if any */
	solr_char_t *field_name = NULL;
	int field_name_len = 0;

	/* Set if the parameter was found in the HashTable and off otherwise */
	zend_bool param_is_set = 1;

	memset(&field_override_buffer, 0, sizeof(solr_string_t));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &field_name, &field_name_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	solr_query_field_override(&field_override_buffer, field_name, field_name_len, "hl.fragmenter");

	if (solr_param_find(getThis(), field_override_buffer.str, field_override_buffer.len, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		param_is_set = 0;
	}

	solr_string_free(&field_override_buffer);

	if (param_is_set) {

		solr_normal_param_value_display_string(solr_param, return_value);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto bool SolrQuery::getHighlightUsePhraseHighlighter()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightUsePhraseHighlighter)
{
	solr_char_t *param_name = (solr_char_t *) "hl.usePhraseHighlighter";
	int param_name_length = sizeof("hl.usePhraseHighlighter")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_boolean(solr_param, return_value);
}
/* }}} */

/* {{{ proto bool SolrQuery::getHighlightHighlightMultiTerm()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightHighlightMultiTerm)
{
	solr_char_t *param_name = (solr_char_t *) "hl.highlightMultiTerm";
	int param_name_length = sizeof("hl.highlightMultiTerm")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_boolean(solr_param, return_value);
}
/* }}} */

/* {{{ proto float SolrQuery::getHighlightRegexSlop()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightRegexSlop)
{
	solr_char_t *param_name = (solr_char_t *) "hl.regex.slop";
	int param_name_length = sizeof("hl.regex.slop")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_double(solr_param, return_value);
}
/* }}} */

/* {{{ proto string SolrQuery::getHighlightRegexPattern()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightRegexPattern)
{
	solr_char_t *param_name = (solr_char_t *) "hl.regex.pattern";
	int param_name_length = sizeof("hl.regex.pattern")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_string(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getHighlightRegexMaxAnalyzedChars()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getHighlightRegexMaxAnalyzedChars)
{
	solr_char_t *param_name = (solr_char_t *) "hl.regex.maxAnalyzedChars";
	int param_name_length = sizeof("hl.regex.maxAnalyzedChars")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_integer(solr_param, return_value);
}
/* }}} */

/* {{{ proto bool SolrQuery::getStats()
	 Returns the status of the stats parameter */
PHP_METHOD(SolrQuery, getStats)
{
	solr_char_t *param_name = (solr_char_t *) "stats";
	int param_name_length = sizeof("stats")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_boolean(solr_param, return_value);
}
/* }}} */

/* {{{ proto array SolrQuery::getStatsFields()
	 Returns the stats.field parameters */
PHP_METHOD(SolrQuery, getStatsFields)
{
	solr_char_t *param_name = (solr_char_t *) "stats.field";
	int param_name_length = sizeof("stats.field")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	array_init(return_value);

	solr_normal_param_value_display(solr_param, return_value);
}
/* }}} */

/* {{{ proto string SolrQuery::getStatsFacets()
	 Returns all the stats facets */
PHP_METHOD(SolrQuery, getStatsFacets)
{
	solr_char_t *param_name = (solr_char_t *) "stats.facet";
	int param_name_length = sizeof("stats.facet")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	array_init(return_value);

	solr_normal_param_value_display(solr_param, return_value);
}
/* }}} */

/* {{{ proto bool SolrQuery::getMlt()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getMlt)
{
	solr_char_t *param_name = (solr_char_t *) "mlt";
	int param_name_length = sizeof("mlt")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_boolean(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getMltCount()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getMltCount)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.count";
	int param_name_length = sizeof("mlt.count")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_integer(solr_param, return_value);
}
/* }}} */

/* {{{ proto array SolrQuery::getMltFields()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getMltFields)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.fl";
	int param_name_length = sizeof("mlt.fl")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	array_init(return_value);

	solr_simple_list_param_value_display(solr_param, return_value);
}
/* }}} */

/* {{{ proto array SolrQuery::getMltQueryFields()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getMltQueryFields)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.qf";
	int param_name_length = sizeof("mlt.qf")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	array_init(return_value);

	solr_arg_list_param_value_display(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getMltMinTermFrequency()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getMltMinTermFrequency)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.mintf";
	int param_name_length = sizeof("mlt.mintf")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_integer(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getMltMinDocFrequency()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getMltMinDocFrequency)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.mindf";
	int param_name_length = sizeof("mlt.mindf")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_integer(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getMltMinWordLength()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getMltMinWordLength)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.minwl";
	int param_name_length = sizeof("mlt.minwl")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_integer(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getMltMaxWordLength()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getMltMaxWordLength)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.maxwl";
	int param_name_length = sizeof("mlt.maxwl")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_integer(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getMltMaxNumTokens()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getMltMaxNumTokens)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.maxntp";
	int param_name_length = sizeof("mlt.maxntp")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_integer(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getMltMaxNumQueryTerms()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getMltMaxNumQueryTerms)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.maxqt";
	int param_name_length = sizeof("mlt.maxqt")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_integer(solr_param, return_value);
}
/* }}} */

/* {{{ proto bool SolrQuery::getMltBoost()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getMltBoost)
{
	solr_char_t *param_name = (solr_char_t *) "mlt.boost";
	int param_name_length = sizeof("mlt.boost")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_boolean(solr_param, return_value);
}
/* }}} */

/* {{{ proto bool SolrQuery::getTerms()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getTerms)
{
	solr_char_t *param_name = (solr_char_t *) "terms";
	int param_name_length = sizeof("terms")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_boolean(solr_param, return_value);
}
/* }}} */

/* {{{ proto string SolrQuery::getTermsField()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getTermsField)
{
	solr_char_t *param_name = (solr_char_t *) "terms.fl";
	int param_name_length = sizeof("terms.fl")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_string(solr_param, return_value);
}
/* }}} */

/* {{{ proto string SolrQuery::getTermsLowerBound()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getTermsLowerBound)
{
	solr_char_t *param_name = (solr_char_t *) "terms.lower";
	int param_name_length = sizeof("terms.lower")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_string(solr_param, return_value);
}
/* }}} */

/* {{{ proto string SolrQuery::getTermsUpperBound()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getTermsUpperBound)
{
	solr_char_t *param_name = (solr_char_t *) "terms.upper";
	int param_name_length = sizeof("terms.upper")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_string(solr_param, return_value);
}
/* }}} */

/* {{{ proto bool SolrQuery::getTermsIncludeLowerBound()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getTermsIncludeLowerBound)
{
	solr_char_t *param_name = (solr_char_t *) "terms.lower.incl";
	int param_name_length = sizeof("terms.lower.incl")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_boolean(solr_param, return_value);
}
/* }}} */

/* {{{ proto bool SolrQuery::getTermsIncludeUpperBound()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getTermsIncludeUpperBound)
{
	solr_char_t *param_name = (solr_char_t *) "terms.upper.incl";
	int param_name_length = sizeof("terms.upper.incl")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_boolean(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getTermsMinCount()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getTermsMinCount)
{
	solr_char_t *param_name = (solr_char_t *) "terms.mincount";
	int param_name_length = sizeof("terms.mincount")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_integer(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getTermsMaxCount()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getTermsMaxCount)
{
	solr_char_t *param_name = (solr_char_t *) "terms.maxcount";
	int param_name_length = sizeof("terms.maxcount")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_integer(solr_param, return_value);
}
/* }}} */

/* {{{ proto string SolrQuery::getTermsPrefix()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getTermsPrefix)
{
	solr_char_t *param_name = (solr_char_t *) "terms.prefix";
	int param_name_length = sizeof("terms.prefix")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_string(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getTermsLimit()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getTermsLimit)
{
	solr_char_t *param_name = (solr_char_t *) "terms.limit";
	int param_name_length = sizeof("terms.limit")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_integer(solr_param, return_value);
}
/* }}} */

/* {{{ proto bool SolrQuery::getTermsReturnRaw()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getTermsReturnRaw)
{
	solr_char_t *param_name = (solr_char_t *) "terms.raw";
	int param_name_length = sizeof("terms.raw")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_boolean(solr_param, return_value);
}
/* }}} */

/* {{{ proto int SolrQuery::getTermsSort()
	 Returns the parameter */
PHP_METHOD(SolrQuery, getTermsSort)
{
	solr_char_t *param_name = (solr_char_t *) "terms.sort";
	int param_name_length = sizeof("terms.sort")-1;
	solr_param_t *solr_param = NULL;

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, SOLR_ERROR_4002_MSG);

		return;
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	solr_normal_param_value_display_sort_type(solr_param, return_value);
}
/* }}} */

/* }}} End of getter methods */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

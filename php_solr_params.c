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

/* $Id: php_solr_params.c 293375 2010-01-11 01:34:16Z iekpo $ */

#include "php_solr.h"

/* {{{ static void solr_serialize_xml_set_param_props(xmlNode *xml_param_node, solr_param_t *param) */
static void solr_serialize_xml_set_param_props(xmlNode *xml_param_node, solr_param_t *param)
{
	char tmp_buffer[32]; /* This should be enough to hold any value */

	memset(tmp_buffer, 0, sizeof(tmp_buffer));

	/* Set the name attribute on the param node */
	xmlNewProp(xml_param_node, (xmlChar *) "name", (xmlChar *) param->param_name);

	php_sprintf(tmp_buffer, "%d", param->type);

	/* Set the type attribute on the param node */
	xmlNewProp(xml_param_node, (xmlChar *) "type", (xmlChar *) tmp_buffer);

	php_sprintf(tmp_buffer, "%d", param->allow_multiple);

	/* Set the allow_multiple attribute on the param node */
	xmlNewProp(xml_param_node, (xmlChar *) "allow_multiple", (xmlChar *) tmp_buffer);

	php_sprintf(tmp_buffer, "%u", param->count);

	/* Set the count attribute on the param node */
	xmlNewProp(xml_param_node, (xmlChar *) "count", (xmlChar *) tmp_buffer);

	php_sprintf(tmp_buffer, "%d", param->delimiter);

	/* Set the delimiter attribute on the param node */
	xmlNewProp(xml_param_node, (xmlChar *) "delimiter", (xmlChar *) tmp_buffer);

	php_sprintf(tmp_buffer, "%d", param->arg_separator);

	/* Set the arg_separator attribute on the param node */
	xmlNewProp(xml_param_node, (xmlChar *) "arg_separator", (xmlChar *) tmp_buffer);
}
/* }}} */

/* {{{ static void solr_serialize_normal_param_value(xmlNode *xml_params_node, solr_param_t *param) */
static void solr_serialize_normal_param_value(xmlNode *xml_params_node, solr_param_t *param)
{
	xmlNode *xml_param_node = xmlNewChild(xml_params_node, NULL, (xmlChar *) "param", NULL);

	solr_param_value_t *curr_value = param->head;

	solr_serialize_xml_set_param_props(xml_param_node, param);

	while(curr_value != NULL)
	{
		xmlChar *param_value_txt = xmlEncodeEntitiesReentrant(xml_params_node->doc, (xmlChar *) curr_value->contents.normal.str);

		xmlNewChild(xml_param_node, NULL, (xmlChar *) "param_value", param_value_txt);

		xmlFree(param_value_txt);

		curr_value = curr_value->next; /* Go to the next value in the list */
	}
}
/* }}} */

/* {{{ static void solr_serialize_simple_list_param_value(xmlNode *xml_params_node, solr_param_t *param) */
static void solr_serialize_simple_list_param_value(xmlNode *xml_params_node, solr_param_t *param)
{
	xmlNode *xml_param_node = xmlNewChild(xml_params_node, NULL, (xmlChar *) "param", NULL);

	solr_param_value_t *curr_value = param->head;

	solr_serialize_xml_set_param_props(xml_param_node, param);

	while(curr_value != NULL)
	{
		xmlChar *param_value_txt = xmlEncodeEntitiesReentrant(xml_params_node->doc, (xmlChar *) curr_value->contents.simple_list.str);

		xmlNewChild(xml_param_node, NULL, (xmlChar *) "param_value", param_value_txt);

		xmlFree(param_value_txt);

		curr_value = curr_value->next; /* Go to the next value in the list */
	}
}
/* }}} */

/* {{{ static void solr_serialize_arg_list_param_value(xmlNode *xml_params_node, solr_param_t *param)  */
static void solr_serialize_arg_list_param_value(xmlNode *xml_params_node, solr_param_t *param)
{
	xmlNode *xml_param_node = xmlNewChild(xml_params_node, NULL, (xmlChar *) "param", NULL);

	solr_param_value_t *curr_value = param->head;

	solr_serialize_xml_set_param_props(xml_param_node, param);

	while(curr_value != NULL)
	{
		xmlChar *param_value_txt = xmlEncodeEntitiesReentrant(xml_params_node->doc, (xmlChar *) curr_value->contents.arg_list.value.str);

		xmlChar *arg_value_txt = xmlEncodeEntitiesReentrant(xml_params_node->doc, (xmlChar *) curr_value->contents.arg_list.arg.str);

		xmlNode *xml_param_value = xmlNewChild(xml_param_node, NULL, (xmlChar *) "param_value", param_value_txt);

		xmlNewProp(xml_param_value, (xmlChar *) "argument", arg_value_txt);

		xmlFree(param_value_txt);

		xmlFree(arg_value_txt);

		curr_value = curr_value->next; /* Go to the next value in the list */
	}
}
/* }}} */

/* {{{ static int solr_serialize_solr_params_object(xmlChar **serialized, int *size, zval *objptr TSRMLS_DC) */
static int solr_serialize_solr_params_object(xmlChar **serialized, int *size, zval *objptr TSRMLS_DC)
{
	solr_params_t *solr_params = NULL;
	xmlNode *xml_solr_params = NULL, *xml_params = NULL;
	xmlDoc *doc_ptr = NULL;
	HashTable *params = NULL;
	int format = 1;

	if (solr_fetch_params_entry(objptr, &solr_params TSRMLS_CC) == FAILURE) {

		return FAILURE;
	}

	if (!serialized || !size || !objptr)
	{
		return FAILURE;
	}

	doc_ptr = solr_xml_create_xml_doc((xmlChar *) "solr_params", &xml_solr_params);
	xml_params = xmlNewChild(xml_solr_params, NULL, (xmlChar *) "params", NULL);

	params = solr_params->params;

	SOLR_HASHTABLE_FOR_LOOP(params)
	{
		solr_param_t **solr_param_ptr = NULL;

		zend_hash_get_current_data_ex(params, (void **) &solr_param_ptr, ((HashPosition *)0));

		switch((*solr_param_ptr)->type)
		{
			case SOLR_PARAM_TYPE_NORMAL :
			{
				solr_serialize_normal_param_value(xml_params, (*solr_param_ptr));
			}
			break;

			case SOLR_PARAM_TYPE_SIMPLE_LIST :
			{
				solr_serialize_simple_list_param_value(xml_params, (*solr_param_ptr));
			}
			break;

			case SOLR_PARAM_TYPE_ARG_LIST :
			{
				solr_serialize_arg_list_param_value(xml_params, (*solr_param_ptr));
			}
			break;

			default :
			{
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid Solr Param Type %d", (*solr_param_ptr)->type);
			}
		}
	}

	xmlIndentTreeOutput = 1;

	xmlDocDumpFormatMemoryEnc(doc_ptr, serialized, size, "UTF-8", format);
	xmlFreeDoc(doc_ptr);

	return SUCCESS;
}
/* }}} */

/* {{{ static void solr_unserialize_get_param_normal(xmlNode *normal_param, HashTable *params_ht TSRMLS_DC) */
static void solr_unserialize_get_param_normal(xmlNode *normal_param, HashTable *params_ht TSRMLS_DC)
{
	solr_char_t *param_name = NULL;
	size_t param_name_len   = 0U;
	solr_bool allow_multiple = 0;
	solr_param_type_t param_type = SOLR_PARAM_TYPE_NORMAL;
	xmlAttr *currAttr = normal_param->properties;
	solr_param_t *param = NULL;
	xmlNode *currNode = normal_param->children;

	solr_param_value_equal_func_t equal_func = solr_normal_param_value_equal;
	solr_param_fetch_func_t fetch_func = (solr_param_fetch_func_t) solr_normal_param_value_fetch;
	solr_param_value_free_func_t free_func = solr_normal_param_value_free;

	/* Grab the name and setting for this parameter */
	while(currAttr != NULL)
	{
		if (solr_xml_match_node(currAttr, "name"))
		{
			param_name = (solr_char_t *) solr_xml_get_node_contents(currAttr);

			param_name_len = solr_strlen(param_name);
		}

		if (solr_xml_match_node(currAttr, "allow_multiple"))
		{
			allow_multiple = solr_xml_get_node_contents_int(currAttr);
		}

		currAttr = currAttr->next;
	}

	param = solr_create_new_param(param_name, param_name_len, param_type, allow_multiple, equal_func, fetch_func, free_func, '&', 0 TSRMLS_CC);

	/* Retrieve all the values for this parameter */
	while(currNode != NULL)
	{
		if (solr_xml_match_node(currNode, "param_value"))
		{
			xmlChar *pvalue = solr_xml_get_node_contents(currNode);

			size_t pvalue_length = solr_strlen((char *)pvalue);

			solr_param_value_t *parameter_value = (solr_param_value_t *) pemalloc(sizeof(solr_param_value_t), SOLR_PARAMS_PERSISTENT);

			memset(parameter_value, 0, sizeof(solr_param_value_t));

			solr_string_appends(&(parameter_value->contents.normal), (solr_char_t *) pvalue, pvalue_length);

			solr_params_insert_param_value(param, parameter_value);
		}

		currNode = currNode->next;
	}

	/* Add this parameter to the hash table */
	if (zend_hash_add(params_ht, (char *) param_name, param_name_len, (void *) &param, sizeof(solr_param_t *), (void **) NULL) == FAILURE) {

		/* Release all the memory allocated to this paramter */
		solr_destroy_param(&param);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error from %s %s", __func__, (char *) param_name);

		return;
	}
}
/* }}} */

/* {{{ static void solr_unserialize_get_param_simple_list(xmlNode *list_param, HashTable *params_ht TSRMLS_DC) */
static void solr_unserialize_get_param_simple_list(xmlNode *list_param, HashTable *params_ht TSRMLS_DC)
{
	solr_char_t *param_name = NULL;
	size_t param_name_len = 0U;
	solr_bool allow_multiple = 0;
	solr_param_type_t param_type = SOLR_PARAM_TYPE_SIMPLE_LIST;
	solr_param_t *param = NULL;
	xmlNode *currNode = list_param->children;
	xmlAttr *currAttr = list_param->properties;

	solr_param_value_equal_func_t equal_func = solr_simple_list_param_value_equal;
	solr_param_fetch_func_t fetch_func = (solr_param_fetch_func_t) solr_simple_list_param_value_fetch;
	solr_param_value_free_func_t free_func = solr_simple_list_param_value_free;

	/* Grab the name and setting for this parameter */
	while(currAttr != NULL)
	{
		if (solr_xml_match_node(currAttr, "name"))
		{
			param_name = (solr_char_t *) solr_xml_get_node_contents(currAttr);

			param_name_len = solr_strlen(param_name);
		}

		if (solr_xml_match_node(currAttr, "allow_multiple"))
		{
			allow_multiple = solr_xml_get_node_contents_int(currAttr);
		}

		currAttr = currAttr->next;
	}

	param = solr_create_new_param(param_name, param_name_len, param_type, allow_multiple, equal_func, fetch_func, free_func, ',', 0 TSRMLS_CC);

	/* Retrieve all the values for this parameter */
	while(currNode != NULL)
	{
		if (solr_xml_match_node(currNode, "param_value"))
		{
			solr_char_t *pvalue = (solr_char_t *) solr_xml_get_node_contents(currNode);
			size_t pvalue_length = solr_strlen(pvalue);
			solr_param_value_t *parameter_value = (solr_param_value_t *) pemalloc(sizeof(solr_param_value_t), SOLR_PARAMS_PERSISTENT);

			memset(parameter_value, 0, sizeof(solr_param_value_t));

			solr_string_appends(&(parameter_value->contents.simple_list), pvalue, pvalue_length);

			solr_params_insert_param_value(param, parameter_value);
		}

		currNode = currNode->next;
	}

	/* Add this parameter to the hash table */
	if (zend_hash_add(params_ht, (char *) param_name, param_name_len, (void *) &param, sizeof(solr_param_t *), (void **) NULL) == FAILURE) {

		/* Release all the memory allocated to this paramter */
		solr_destroy_param(&param);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error from %s %s", __func__, (char *) param_name);

		return;
	}
}
/* }}} */

/* {{{ static void solr_unserialize_get_param_arg_list(xmlNode *sort_param, HashTable *params_ht TSRMLS_DC) */
static void solr_unserialize_get_param_arg_list(xmlNode *sort_param, HashTable *params_ht TSRMLS_DC)
{
	solr_char_t *param_name = NULL;
	size_t param_name_len = 0U;
	solr_bool allow_multiple = 0;
	solr_char_t delimiter = 0;
	solr_char_t separator = 0;
	xmlAttr *currAttr = sort_param->properties;
	solr_param_type_t param_type = SOLR_PARAM_TYPE_ARG_LIST;
	solr_param_t *param = NULL;
	xmlNode *currNode = sort_param->children;

	solr_param_value_equal_func_t equal_func = solr_arg_list_param_value_equal;
	solr_param_fetch_func_t fetch_func = (solr_param_fetch_func_t) solr_arg_list_param_value_fetch;
	solr_param_value_free_func_t free_func = solr_arg_list_param_value_free;

	/* Grab the name and setting for this parameter */
	while(currAttr != NULL)
	{
		if (solr_xml_match_node(currAttr, "name"))
		{
			param_name = (solr_char_t *) solr_xml_get_node_contents(currAttr);

			param_name_len = solr_strlen(param_name);
		}

		if (solr_xml_match_node(currAttr, "allow_multiple"))
		{
			allow_multiple = solr_xml_get_node_contents_int(currAttr);
		}

		if (solr_xml_match_node(currAttr, "delimiter"))
		{
			delimiter = solr_xml_get_node_contents_int(currAttr);
		}

		if (solr_xml_match_node(currAttr, "arg_separator"))
		{
			separator = solr_xml_get_node_contents_int(currAttr);
		}

		currAttr = currAttr->next;
	}

	param = solr_create_new_param(param_name, param_name_len, param_type, allow_multiple, equal_func, fetch_func, free_func, delimiter, separator TSRMLS_CC);

	/* Retrieve all the values for this parameter */
	while(currNode != NULL)
	{
		if (solr_xml_match_node(currNode, "param_value"))
		{
			solr_char_t *pvalue = (solr_char_t *) solr_xml_get_node_contents(currNode);

			xmlAttr *argument = currNode->properties; /* the argument is the only property */

			solr_char_t *avalue = (solr_char_t *) solr_xml_get_node_contents(argument);

			size_t pvalue_length = solr_strlen(pvalue);
			size_t avalue_length = solr_strlen(avalue);

			solr_param_value_t *parameter_value = (solr_param_value_t *) pemalloc(sizeof(solr_param_value_t), SOLR_PARAMS_PERSISTENT);

			memset(parameter_value, 0, sizeof(solr_param_value_t));

			solr_string_appends(&(parameter_value->contents.arg_list.value), pvalue, pvalue_length);

			solr_string_appends(&(parameter_value->contents.arg_list.arg), avalue, avalue_length);

			solr_params_insert_param_value(param, parameter_value);
		}

		currNode = currNode->next;
	}

	/* Add this parameter to the hash table */
	if (zend_hash_add(params_ht, (char *) param_name, param_name_len, (void *) &param, sizeof(solr_param_t *), (void **) NULL) == FAILURE) {

		/* Release all the memory allocated to this paramter */
		solr_destroy_param(&param);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error from %s %s", __func__, (char *) param_name);

		return;
	}
}
/* }}} */

/* {{{ static int solr_unserialize_solr_params_object(const char *serialized, int size, zval *objptr TSRMLS_DC) */
static int solr_unserialize_solr_params_object(const char *serialized, int size, zval *objptr TSRMLS_DC)
{
	solr_params_t *solr_params = NULL;
	long int params_index = SOLR_UNIQUE_PARAMS_INDEX();
	solr_params_t tmp_solr_params;
	uint nSize = SOLR_INITIAL_HASH_TABLE_SIZE;
	HashTable *params_ht = NULL;
	xmlDoc *doc = NULL;
	xmlXPathContext *xpathctxt;
	const xmlChar *xpath_expression = (xmlChar *) "/solr_params/params/param/@type";
	xmlXPathObject *xpathObj;
	xmlNodeSet *result = NULL;
	register size_t num_nodes;
	register size_t i = 0U;
	int return_status = SUCCESS;

	zend_update_property_long(Z_OBJCE_P(objptr), objptr, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, params_index TSRMLS_CC);

	memset(&tmp_solr_params, 0, sizeof(solr_params_t));

	if (zend_hash_index_update(SOLR_GLOBAL(params), params_index, (void *) &tmp_solr_params, sizeof(solr_params_t), (void **) &solr_params) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error while registering SolrParam object in HashTable");

		return FAILURE;
	}

	solr_params->params_index = params_index;

	/* Allocate memory for the parameters HashTable using fast cache for HashTables */
	ALLOC_HASHTABLE(solr_params->params);

	zend_hash_init(solr_params->params, nSize, NULL, (dtor_func_t) solr_destroy_param, SOLR_PARAMS_PERSISTENT);

	params_ht = solr_params->params;

	doc = xmlReadMemory(serialized, size, NULL, "UTF-8", 0);

	if (doc == NULL)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error while parsing serialized XML string");

		return FAILURE;
	}

	xpathctxt = xmlXPathNewContext(doc);

	if (xpathctxt == NULL)
	{
		xmlFreeDoc(doc);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error while creating XML Xpath context");

		return FAILURE;
	}

	xpathObj = xmlXPathEval(xpath_expression, xpathctxt);

	if (xpathObj == NULL)
	{
		xmlXPathFreeContext(xpathctxt);

		xmlFreeDoc(doc);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error while evaluation XML Xpath expression");

		return FAILURE;
	}

	result = xpathObj->nodesetval;

	if (result == NULL)
	{
		xmlXPathFreeObject(xpathObj);

		xmlXPathFreeContext(xpathctxt);

		xmlFreeDoc(doc);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error while extracting result from XML xpath object during unserialization");

		return FAILURE;
	}

	num_nodes = result->nodeNr; /* Number of parameter nodes matches in the xmlDocument */

	/* Loop through all the parameter nodes and create an entry in the HashTable for each one */
	for (i = 0U; i < num_nodes; i++)
	{
		xmlNode *currNode = result->nodeTab[i];

		/* Absolutely No assumptions. I have to make sure that this is an attribute node */
		if (currNode->type == XML_ATTRIBUTE_NODE)
		{
			/* Find out what type of parameter this is */
			const solr_param_type_t param_type = solr_xml_get_node_contents_int(currNode);

			/* Get the /solr_params/params/param node */
			xmlNode *param_xml_node = currNode->parent;

			/* Handle each parameter type separately */
			switch(param_type)
			{
				case SOLR_PARAM_TYPE_NORMAL :
				{
					solr_unserialize_get_param_normal(param_xml_node, params_ht TSRMLS_CC);
				}
				break;

				case SOLR_PARAM_TYPE_SIMPLE_LIST :
				{
					solr_unserialize_get_param_simple_list(param_xml_node, params_ht TSRMLS_CC);
				}
				break;

				case SOLR_PARAM_TYPE_ARG_LIST :
				{
					solr_unserialize_get_param_arg_list(param_xml_node, params_ht TSRMLS_CC);
				}
				break;

				default :
				{
					php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter type");

					return_status = FAILURE;

					goto loop_complete;
				}

			} /* End switch */

		} /* End if (currNode->type == XML_ATTRIBUTE_NODE) */

	} /* End for */

loop_complete:

	xmlXPathFreeObject(xpathObj);

	xmlXPathFreeContext(xpathctxt);

	xmlFreeDoc(doc);

	return return_status;
}
/* }}} */

/* {{{ proto SolrParams::__clone(void)
   Should never be called directly. Throws exceptions whenever there is an attempt to clone a SolrParams instance */
PHP_METHOD(SolrParams, __clone)
{
	solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_4001 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Cloning of SolrParams object instances is currently not supported");
}
/* }}} */

/* {{{ proto SolrParams::setParam(string param_name, string param_value)
   Sets the parameter to the specified value */
PHP_METHOD(SolrParams, setParam)
{
	solr_char_t *param_name = NULL;
	int   param_name_length = 0;

	solr_char_t *param_value = NULL;
	int   param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &param_name, &param_name_length, &param_value, &param_value_length) == FAILURE) {

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

/* {{{ proto SolrParams::addParam(string param_name, string param_value)
   Adds another param_name to the object. */
PHP_METHOD(SolrParams, addParam)
{
	solr_char_t *param_name = NULL;
	int param_name_length = 0;
	solr_char_t *param_value = NULL;
	int param_value_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &param_name, &param_name_length, &param_value, &param_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_add_normal_param(getThis(), param_name, param_name_length, param_value, param_value_length) == FAILURE)
	{
		RETURN_NULL();
	}

	solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrParams::getParam(string param_name)
   Retrieves a parameter value */
PHP_METHOD(SolrParams, getParam)
{
	solr_char_t *param_name = NULL;
	int param_name_length = 0;

	solr_param_t *solr_param = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &param_name, &param_name_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_FALSE;
	}

	if (!return_value_used) {

		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "return value requested without processing output.");

		return;
	}

	if (!param_name_length) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter name");

		RETURN_NULL();
	}

	if (solr_param_find(getThis(), param_name, param_name_length, (solr_param_t **) &solr_param TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}

	if (!solr_param) {

		/* This should never happen unless there is a logic error in solr_param_find() */
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Very severe internal error while fetching (solr_param_t **) from solr_param_find() %s", __func__);

		return;
	}

	switch(solr_param->type)
	{
		case SOLR_PARAM_TYPE_NORMAL :
		{
			if (solr_param->allow_multiple) {

				array_init(return_value);

				solr_normal_param_value_display(solr_param, return_value);

				return;

			} else {

				solr_normal_param_value_display_string(solr_param, return_value);

				return;
			}
		}
		break;

		case SOLR_PARAM_TYPE_SIMPLE_LIST :
		{
			array_init(return_value);

			solr_simple_list_param_value_display(solr_param, return_value);

			return;
		}
		break;

		case SOLR_PARAM_TYPE_ARG_LIST :
		{
			array_init(return_value);

			solr_arg_list_param_value_display(solr_param, return_value);

			return;
		}
		break;

		default :
		{
			/* This should never happen. However, never say never! */
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameter type in switch case %s", __func__);
		}

	} /* END switch(solr_param->type) */

}
/* }}} */

/* {{{ proto array SolrParams::getPreparedParams(void)
   Returns an array of all the parameters (url-encoded) as they will be sent in the name-value pair POST request. */
PHP_METHOD(SolrParams, getPreparedParams)
{
	solr_params_t *solr_params = NULL;

	if (!return_value_used)
	{
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Return value requested but output not processed.");

		return;
	}

	array_init(return_value);

	/* Retrieve the document entry for this SolrDocument */
	if (solr_fetch_params_entry(getThis(), &solr_params TSRMLS_CC) == SUCCESS) {

		HashTable *params = solr_params->params;

		SOLR_HASHTABLE_FOR_LOOP(params)
		{
			solr_param_t **solr_param_ptr = NULL;
			solr_param_t *solr_param;
			solr_string_t tmp_buffer;

			zend_hash_get_current_data_ex(params, (void **) &solr_param_ptr, NULL);

			solr_param = (*solr_param_ptr);

			memset(&tmp_buffer, 0, sizeof(solr_string_t));

			solr_param->fetch_func(solr_param, &tmp_buffer);

			add_assoc_stringl(return_value, (*solr_param_ptr)->param_name, tmp_buffer.str, tmp_buffer.len, 1);
			solr_string_free(&tmp_buffer);
		}

		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_WARNING, "SolrParams instance could not be retrieved from HashTable");

	RETURN_NULL();
}
/* }}} */

/* {{{ proto array SolrParams::getParams(void)
   Returns an array of the parameters in the object. The values are not url-encoded. */
PHP_METHOD(SolrParams, getParams)
{
	solr_params_t *solr_params = NULL;

	if (!return_value_used)
	{
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Return value requested but output not processed.");

		return;
	}

	array_init(return_value);

	/* Retrieve the document entry for this SolrDocument */
	if (solr_fetch_params_entry(getThis(), &solr_params TSRMLS_CC) == SUCCESS) {

		HashTable *params = solr_params->params;

		SOLR_HASHTABLE_FOR_LOOP(params)
		{
			solr_param_t **solr_param_ptr = NULL;
			solr_param_display_func_t display_func = NULL;
			zval *current_param = NULL;

			zend_hash_get_current_data_ex(params, (void **) &solr_param_ptr, NULL);

			switch((*solr_param_ptr)->type)
			{
				case SOLR_PARAM_TYPE_NORMAL :
				{
					display_func = solr_normal_param_value_display;
				}
				break;

				case SOLR_PARAM_TYPE_SIMPLE_LIST :
				{
					display_func = solr_simple_list_param_value_display;
				}
				break;

				case SOLR_PARAM_TYPE_ARG_LIST :
				{
					display_func = solr_arg_list_param_value_display;
				}
				break;

				default :
				{
					php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter type");
				}
			}

			MAKE_STD_ZVAL(current_param);
			array_init(current_param);
			add_assoc_zval(return_value, (*solr_param_ptr)->param_name, current_param);

			display_func((*solr_param_ptr), current_param);
		}

		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_WARNING, "SolrParams instance could not be retrieved from HashTable");

	RETURN_NULL();
}
/* }}} */

/* {{{ proto string SolrParams::__toString(void)
   Returns a string representation of the object */
PHP_METHOD(SolrParams, __toString)
{
	solr_params_t *solr_params = NULL;

	register zend_bool url_encode = 0;

	/* Retrieve the document entry for this SolrDocument */
	if (solr_fetch_params_entry(getThis(), &solr_params TSRMLS_CC) == SUCCESS) {

		HashTable *params = solr_params->params;

		solr_string_t tmp_buffer;

		memset(&tmp_buffer, 0, sizeof(solr_string_t));

		SOLR_HASHTABLE_FOR_LOOP(params)
		{
			solr_param_t **solr_param_ptr = NULL;
			solr_param_tostring_func_t tostring_func = NULL;

			zend_hash_get_current_data_ex(params, (void **) &solr_param_ptr, NULL);

			switch((*solr_param_ptr)->type)
			{
				case SOLR_PARAM_TYPE_NORMAL :
				{
					tostring_func = solr_normal_param_value_tostring;
				}
				break;

				case SOLR_PARAM_TYPE_SIMPLE_LIST :
				{
					tostring_func = solr_simple_list_param_value_tostring;
				}
				break;

				case SOLR_PARAM_TYPE_ARG_LIST :
				{
					tostring_func = solr_arg_list_param_value_tostring;
				}
				break;

				default :
				{
					php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter type");
				}
			}

			tostring_func((*solr_param_ptr), &(tmp_buffer), url_encode);

			solr_string_appendc(&(tmp_buffer), '&');
		}

		if (tmp_buffer.str && tmp_buffer.len)
		{
			solr_string_remove_last_char(&(tmp_buffer));

			RETVAL_STRINGL((char *) tmp_buffer.str, tmp_buffer.len, 1);

			solr_string_free(&(tmp_buffer));

			return;
		}
	}

	RETVAL_STRINGL(SOLR_SPACE_STRING, sizeof(SOLR_SPACE_STRING)-1, 1);
}
/* }}} */

/* {{{ proto string SolrParams::toString(void)
   Returns a string representation of the object */
PHP_METHOD(SolrParams, toString)
{
	solr_params_t *solr_params = NULL;

	zend_bool url_encode = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|b", &url_encode) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		return;
	}

	if (!return_value_used)
	{
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Return value requested but output not processed.");

		return;
	}

	/* Retrieve the document entry for this SolrDocument */
	if (solr_fetch_params_entry(getThis(), &solr_params TSRMLS_CC) == SUCCESS) {

		HashTable *params = solr_params->params;

		solr_string_t tmp_buffer;

		memset(&tmp_buffer, 0, sizeof(solr_string_t));

		SOLR_HASHTABLE_FOR_LOOP(params)
		{
			solr_param_t **solr_param_ptr = NULL;
			solr_param_tostring_func_t tostring_func = NULL;

			zend_hash_get_current_data_ex(params, (void **) &solr_param_ptr, NULL);

			switch((*solr_param_ptr)->type)
			{
				case SOLR_PARAM_TYPE_NORMAL :
				{
					tostring_func = solr_normal_param_value_tostring;
				}
				break;

				case SOLR_PARAM_TYPE_SIMPLE_LIST :
				{
					tostring_func = solr_simple_list_param_value_tostring;
				}
				break;

				case SOLR_PARAM_TYPE_ARG_LIST :
				{
					tostring_func = solr_arg_list_param_value_tostring;
				}
				break;

				default :
				{
					php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter type");
				}
			}

			tostring_func((*solr_param_ptr), &(tmp_buffer), url_encode);

			solr_string_appendc(&(tmp_buffer), '&');
		}

		if (tmp_buffer.str && tmp_buffer.len)
		{
			solr_string_remove_last_char(&(tmp_buffer));

			RETVAL_STRINGL((char *) tmp_buffer.str, tmp_buffer.len, 1);

			solr_string_free(&(tmp_buffer));

			return;
		}
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto string SolrParams::serialize(void)
   Returns a string representation of the object. Used for custom serialization. */
PHP_METHOD(SolrParams, serialize)
{
	xmlChar *serialized = NULL;
	int size = 0;

	if (solr_serialize_solr_params_object(&serialized, &size, getThis() TSRMLS_CC) == FAILURE || !serialized || !size)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to serialize object");

		RETURN_NULL();
	}

	RETVAL_STRINGL((char *) serialized, size, 1);

	xmlFree(serialized);
}
/* }}} */

/* {{{ proto void SolrParams::unserialize(string serialized)
   Brings the serialized object back to life. */
PHP_METHOD(SolrParams, unserialize)
{
	char *serialized_object = NULL;
	int serialized_object_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &serialized_object, &serialized_object_len) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if(serialized_object_len == 0)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");

		RETURN_NULL();
	}

	if (solr_unserialize_solr_params_object(serialized_object, serialized_object_len, getThis() TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error during unserialization");
	}
}
/* }}} */

/* {{{ proto void SolrModifiableParams::__construct(void)
   Constructor. */
PHP_METHOD(SolrModifiableParams, __construct)
{
	long int params_index = SOLR_UNIQUE_PARAMS_INDEX();
	uint nSize = SOLR_INITIAL_HASH_TABLE_SIZE;
	solr_params_t *solr_params_dest = NULL;
	solr_params_t solr_params;

	zend_update_property_long(solr_ce_SolrModifiableParams, getThis(), SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, params_index TSRMLS_CC);

	memset(&solr_params, 0, sizeof(solr_params_t));

	if (zend_hash_index_update(SOLR_GLOBAL(params), params_index, (void *) &solr_params, sizeof(solr_params_t), (void **) &solr_params_dest) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error while registering query parameters in HashTable");

		return ;
	}

	solr_params_dest->params_index = params_index;
	solr_params_dest->params_count = 1U;

	/* Allocated memory for the parameters HashTable using fast cache for HashTables */
	ALLOC_HASHTABLE(solr_params_dest->params);

	zend_hash_init(solr_params_dest->params, nSize, NULL, (dtor_func_t) solr_destroy_param, SOLR_PARAMS_PERSISTENT);
}
/* }}} */

/* {{{ proto void SolrModifiableParams::__destruct(void)
   Destructor. */
PHP_METHOD(SolrModifiableParams, __destruct)
{
	solr_params_t *solr_params = NULL;

	/* Retrieve the document entry for this SolrDocument */
	if (solr_fetch_params_entry(getThis(), &solr_params TSRMLS_CC) == SUCCESS) 	{

		zend_hash_index_del(SOLR_GLOBAL(params), solr_params->params_index);

		return ;
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

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

/* $Id$ */

#include "php_solr.h"

/* {{{ Macros */
/* Used to release the (solr_document_t **) pointers */
#define SOLR_FREE_DOC_ENTRIES(ptr) { \
	if ((ptr) != NULL)\
	{ \
		pefree(ptr, SOLR_DOCUMENT_PERSISTENT); \
		ptr = NULL; \
	} \
}
/* }}} */

/* {{{ static void solr_client_init_urls(solr_client_t *solr_client) */
static void solr_client_init_urls(solr_client_t *solr_client)
{
	solr_string_t url_prefix;

	solr_client_options_t *options = &(solr_client->options);

	memset(&url_prefix, 0, sizeof(solr_string_t));

	/* Release all previously allocated URL values, if any */
	solr_string_free(&(options->update_url));
	solr_string_free(&(options->search_url));
	solr_string_free(&(options->thread_url));
	solr_string_free(&(options->ping_url));
	solr_string_free(&(options->terms_url));

	/* Making http://hostname:host_port/path/ */
	solr_string_append_const(&url_prefix, "http://");
	solr_string_append_solr_string(&url_prefix, &(options->hostname));
	solr_string_appendc(&url_prefix, ':');
	solr_string_append_long(&url_prefix, options->host_port);
	solr_string_appendc(&url_prefix, '/');
	solr_string_append_solr_string(&url_prefix, &(options->path));
	solr_string_appendc(&url_prefix, '/');

	/* Copying over the prefixes */
	solr_string_append_solr_string(&(options->update_url), &url_prefix);
	solr_string_append_solr_string(&(options->search_url), &url_prefix);
	solr_string_append_solr_string(&(options->thread_url), &url_prefix);
	solr_string_append_solr_string(&(options->ping_url),   &url_prefix);
	solr_string_append_solr_string(&(options->terms_url),   &url_prefix);

	/* Making http://hostname:host_port/path/servlet/ */
	solr_string_append_solr_string(&(options->update_url), &(options->update_servlet));
	solr_string_append_solr_string(&(options->search_url), &(options->search_servlet));
	solr_string_append_solr_string(&(options->thread_url), &(options->thread_servlet));
	solr_string_append_solr_string(&(options->ping_url),   &(options->ping_servlet));
	solr_string_append_solr_string(&(options->terms_url),   &(options->terms_servlet));

	solr_string_append_const(&(options->update_url), "/?wt=xml&version=2.2&indent=on");
	solr_string_append_const(&(options->search_url), "/?wt=xml&version=2.2&indent=on");
	solr_string_append_const(&(options->thread_url), "/?wt=xml&version=2.2&indent=on");
	solr_string_append_const(&(options->ping_url),   "/?wt=xml&version=2.2&indent=on");
	solr_string_append_const(&(options->terms_url),  "/?wt=xml&version=2.2&indent=on");

	solr_string_free(&url_prefix);
}
/* }}} */

/* {{{ static int solr_http_build_query(solr_string_t *buffer, zval *params_objptr, const solr_char_t *delimiter, int delimiter_length TSRMLS_DC) */
static int solr_http_build_query(solr_string_t *buffer, zval *params_objptr, const solr_char_t *delimiter, int delimiter_length TSRMLS_DC)
{
	solr_params_t *solr_params = NULL;
	register zend_bool duplicate = 0;
	HashTable *params;

	if (solr_fetch_params_entry(params_objptr, &solr_params TSRMLS_CC) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve solr_params_t");

		return FAILURE;
	}

	params = solr_params->params;

	SOLR_HASHTABLE_FOR_LOOP(params)
	{
		solr_param_t **solr_param_ptr = NULL;
		solr_param_t *solr_param = NULL;
		solr_string_t tmp_values_buffer;

		char *str_index = NULL;
		uint str_length = 0U;
		ulong num_index = 0L;

		zend_hash_get_current_key_ex(params, &str_index, &str_length, &num_index, duplicate, ((HashPosition *)0));
		zend_hash_get_current_data_ex(params, (void **) &solr_param_ptr, ((HashPosition *)0));

		memset(&tmp_values_buffer, 0, sizeof(solr_string_t));

		solr_param = (*solr_param_ptr);

		solr_param->fetch_func(solr_param, &tmp_values_buffer);

		solr_string_append_solr_string(buffer, &tmp_values_buffer);
		solr_string_appends(buffer, delimiter, delimiter_length);
		solr_string_free(&tmp_values_buffer);

	} /* SOLR_HASHTABLE_FOR_LOOP(params) */

	solr_string_remove_last_char(buffer);

	return SUCCESS;
}
/* }}} */

/* {{{ static void solr_generate_document_xml_from_fields(xmlNode *solr_doc_node, HashTable *document_fields) */
static void solr_generate_document_xml_from_fields(xmlNode *solr_doc_node, HashTable *document_fields)
{
	xmlDoc *doc_ptr = solr_doc_node->doc;

	SOLR_HASHTABLE_FOR_LOOP(document_fields)
	{
		solr_char_t *doc_field_name;
		solr_field_value_t *doc_field_value;
		solr_field_list_t **field = NULL;
		zend_bool is_first_value = 1; /* Turn on first value flag */

		zend_hash_get_current_data_ex(document_fields, (void **) &field, ((HashPosition *)0));

		doc_field_name = (*field)->field_name;
		doc_field_value = (*field)->head;

		/* Loop through all the values for this field */
		while(doc_field_value != NULL)
		{
			xmlChar *escaped_field_value = xmlEncodeEntitiesReentrant(doc_ptr, (xmlChar *) doc_field_value->field_value);

			xmlNode *solr_field_node = xmlNewChild(solr_doc_node, NULL, (xmlChar *) "field", escaped_field_value);

			xmlNewProp(solr_field_node, (xmlChar *) "name", (xmlChar *) doc_field_name);

			/* Set the boost attribute if this is the first value */
			if (is_first_value && (*field)->field_boost > 0.0f)
			{
				auto char tmp_boost_value_buffer[256];

				memset(tmp_boost_value_buffer, 0, sizeof(tmp_boost_value_buffer));

				php_sprintf(tmp_boost_value_buffer, "%0.1f", (*field)->field_boost);

				xmlNewProp(solr_field_node, (xmlChar *) "boost", (xmlChar *) tmp_boost_value_buffer);

				is_first_value = 0; /* Turn off the flag */
			}

			/* Release the memory allocated by xmlEncodeEntitiesReentrant */
			xmlFree(escaped_field_value);

			/* Grab the next value for this field if any */
			doc_field_value = doc_field_value->next;

		} /* while(doc_field_value != NULL) */

	} /* SOLR_HASHTABLE_FOR_LOOP(document_fields) */
}
/* }}} */

/******************************************************************************/
/** DEFINITIONS FOR SOLR CLIENT METHODS                                      **/
/******************************************************************************/

/* {{{ proto SolrClient::__construct(array options )
   Constructor for SolrClient */
PHP_METHOD(SolrClient, __construct)
{
	zval *options = NULL;
	zval *objptr  = getThis();
	HashTable *options_ht;
	long int client_index = 0L;
	zval **tmp1 = NULL, **tmp2 = NULL;
	solr_client_t *solr_client = NULL;
	solr_client_t *solr_client_dest = NULL;
	solr_client_options_t *client_options;
	solr_curl_t *handle;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &options) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter. The client options array is required for a SolrClient instance. It must also be passed as the only parameter");

		return;
	}

	client_index = SOLR_UNIQUE_CLIENT_INDEX();

	zend_update_property_long(solr_ce_SolrClient, objptr, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, client_index TSRMLS_CC);

	options_ht = Z_ARRVAL_P(options);

	solr_client = (solr_client_t *) pemalloc(sizeof(solr_client_t), SOLR_CLIENT_PERSISTENT);

	memset(solr_client, 0, sizeof(solr_client_t));

	solr_client->client_index = client_index;

	if (zend_hash_index_update(SOLR_GLOBAL(clients), client_index, (void *) solr_client, sizeof(solr_client_t), (void **) &solr_client_dest) == FAILURE) {

		pefree(solr_client, SOLR_CLIENT_PERSISTENT);

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error while registering client in HashTable");

		return;
	}

	/* Release the original pointer */
	pefree(solr_client, SOLR_CLIENT_PERSISTENT);

	client_options = &(solr_client_dest->options);
	handle = &(solr_client_dest->handle);

	solr_init_options(client_options TSRMLS_CC);

	solr_string_append_const(&(client_options->response_writer), SOLR_PHP_SERIALIZED_RESPONSE_WRITER);

	solr_string_append_const(&(client_options->update_servlet), SOLR_DEFAULT_UPDATE_SERVLET);
	solr_string_append_const(&(client_options->search_servlet), SOLR_DEFAULT_SEARCH_SERVLET);
	solr_string_append_const(&(client_options->thread_servlet), SOLR_DEFAULT_THREADS_SERVLET);
	solr_string_append_const(&(client_options->ping_servlet),   SOLR_DEFAULT_PING_SERVLET);
	solr_string_append_const(&(client_options->terms_servlet),  SOLR_DEFAULT_TERMS_SERVLET);

	if (zend_hash_find(options_ht, "hostname", sizeof("hostname"), (void**) &tmp1) == SUCCESS && Z_TYPE_PP(tmp1) == IS_STRING && Z_STRLEN_PP(tmp1))
	{
		solr_string_appends(&(client_options->hostname), (solr_char_t *) Z_STRVAL_PP(tmp1), Z_STRLEN_PP(tmp1));

	} else {

		solr_string_append_const(&(client_options->hostname), SOLR_REQUEST_DEFAULT_HOST);
	}

	if (zend_hash_find(options_ht, "port", sizeof("port"), (void**) &tmp1) == SUCCESS && Z_TYPE_PP(tmp1) == IS_LONG)
	{
		client_options->host_port = Z_LVAL_PP(tmp1);

	} else {

		client_options->host_port = SOLR_REQUEST_DEFAULT_PORT;
	}

	if (zend_hash_find(options_ht, "path", sizeof("path"), (void**) &tmp1) == SUCCESS && Z_TYPE_PP(tmp1) == IS_STRING)
	{
		char *path_to_solr = Z_STRVAL_PP(tmp1);

		size_t path_to_solr_start = 0;

		size_t length_adjustment  = 0;

		if (path_to_solr[0] == '/')
		{
			path_to_solr_start = length_adjustment = 1;
		}

		if (path_to_solr[Z_STRLEN_PP(tmp1)] == '/')
		{
			length_adjustment++;
		}

		solr_string_appends(&(client_options->path), Z_STRVAL_PP(tmp1) + path_to_solr_start, Z_STRLEN_PP(tmp1) - length_adjustment);

	} else {

		solr_string_append_const(&(client_options->path), SOLR_REQUEST_DEFAULT_PATH);
	}

	if (zend_hash_find(options_ht, "query_string_delimiter", sizeof("query_string_delimiter"), (void**) &tmp1) == SUCCESS && Z_TYPE_PP(tmp1) == IS_STRING)
	{
		solr_string_appends(&(client_options->qs_delimiter), Z_STRVAL_PP(tmp1), Z_STRLEN_PP(tmp1));

	} else {

		solr_string_append_const(&(client_options->qs_delimiter), SOLR_REQUEST_DEFAULT_QS_DELIMITER);
	}

	if (zend_hash_find(options_ht, "login", sizeof("login"), (void**) &tmp1) == SUCCESS && Z_TYPE_PP(tmp1) == IS_STRING

	&& zend_hash_find(options_ht, "password", sizeof("password"), (void**) &tmp2) == SUCCESS && Z_TYPE_PP(tmp2) == IS_STRING)

	{
		solr_string_appends(&(client_options->http_auth_credentials), Z_STRVAL_PP(tmp1), Z_STRLEN_PP(tmp1));
		solr_string_appendc(&(client_options->http_auth_credentials), ':');
		solr_string_appends(&(client_options->http_auth_credentials), Z_STRVAL_PP(tmp2), Z_STRLEN_PP(tmp2));
	}

	if (zend_hash_find(options_ht, "proxy_host", sizeof("proxy_host"), (void**) &tmp1) == SUCCESS && Z_TYPE_PP(tmp1) == IS_STRING)
	{
		solr_string_appends(&(client_options->proxy_hostname), Z_STRVAL_PP(tmp1), Z_STRLEN_PP(tmp1));
	}

	if (zend_hash_find(options_ht, "proxy_port", sizeof("proxy_port"), (void**) &tmp1) == SUCCESS && Z_TYPE_PP(tmp1) == IS_LONG)
	{
		client_options->proxy_port = Z_LVAL_PP(tmp1);
	}

	if (zend_hash_find(options_ht, "proxy_login", sizeof("proxy_login"), (void**)&tmp1) == SUCCESS && Z_TYPE_PP(tmp1) == IS_STRING

	&& zend_hash_find(options_ht, "proxy_password", sizeof("proxy_password"), (void**)&tmp2) == SUCCESS && Z_TYPE_PP(tmp2) == IS_STRING)

	{
		solr_string_appends(&(client_options->proxy_auth_credentials), Z_STRVAL_PP(tmp1), Z_STRLEN_PP(tmp1));
		solr_string_appendc(&(client_options->proxy_auth_credentials), ':');
		solr_string_appends(&(client_options->proxy_auth_credentials), Z_STRVAL_PP(tmp2), Z_STRLEN_PP(tmp2));
	}

	solr_init_handle(handle, client_options TSRMLS_CC);

	SOLR_GLOBAL(client_count)++;
}
/* }}} */

/* {{{ proto SolrClient::__destruct(void)
   Destructor for SolrClient */
PHP_METHOD(SolrClient, __destruct)
{
	solr_client_t *solr_client = NULL;

	if (solr_fetch_client_entry(getThis(), &solr_client TSRMLS_CC) == SUCCESS) 	{

		zend_hash_index_del(SOLR_GLOBAL(clients), solr_client->client_index);

		/* Keep track of how many SolrClient instances we have. */
		SOLR_GLOBAL(client_count)--;

		return ;
	}
}
/* }}} */

/* {{{ proto SolrClient::__sleep(void)
   Should not be called directly. Serialization is not supported. */
PHP_METHOD(SolrClient, __sleep)
{
	solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1001 TSRMLS_CC, SOLR_FILE_LINE_FUNC, SOLR_ERROR_1001_MSG);
}
/* }}} */

/* {{{ proto SolrClient::__wakeup(void)
   Should not be called directly. Serialization is not supported. */
PHP_METHOD(SolrClient, __wakeup)
{
	solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1001 TSRMLS_CC, SOLR_FILE_LINE_FUNC, SOLR_ERROR_1001_MSG);
}
/* }}} */

/* {{{ proto bool SolrClient::setServelet(int servlet_type, string new_value)
   Changes the specified servlet type to a new value */
PHP_METHOD(SolrClient, setServlet)
{
	long int servlet_type_value = 0L;
	solr_char_t *new_servlet_value = NULL;
	int new_servlet_value_length = 0;
	solr_client_t *client = NULL;
	solr_servlet_type_t servlet_type;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ls", &servlet_type_value, &new_servlet_value, &new_servlet_value_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter.");

		RETURN_FALSE;
	}

	if (!new_servlet_value_length)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid servlet value.");

		RETURN_FALSE;
	}

	/* Retrieve the client entry */
	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client");

		RETURN_FALSE;
	}

	servlet_type = (solr_servlet_type_t) servlet_type_value;

	switch(servlet_type)
	{
		case SOLR_SERVLET_TYPE_SEARCH :
		{
			solr_string_set(&(client->options.search_servlet), new_servlet_value, new_servlet_value_length);
		}
		break;

		case SOLR_SERVLET_TYPE_TERMS :
		{
			solr_string_set(&(client->options.terms_servlet), new_servlet_value, new_servlet_value_length);
		}
		break;

		case SOLR_SERVLET_TYPE_UPDATE :
		{
			solr_string_set(&(client->options.update_servlet), new_servlet_value, new_servlet_value_length);
		}
		break;

		case SOLR_SERVLET_TYPE_THREADS :
		{
			solr_string_set(&(client->options.thread_servlet), new_servlet_value, new_servlet_value_length);
		}
		break;

		case SOLR_SERVLET_TYPE_PING :
		{
			solr_string_set(&(client->options.ping_servlet), new_servlet_value, new_servlet_value_length);
		}
		break;

		default :
		{
			solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Invalid Servlet type %ld specified. Value discarded.", servlet_type_value);

			RETURN_FALSE;
		}
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto SolrQueryResponse SolrClient::query(SolrParams query)
   Sends a name-value pair request to the Solr server. */
PHP_METHOD(SolrClient, query)
{
	zval *solr_params_obj = NULL;
	solr_client_t *client = NULL;
	solr_params_t *solr_params = NULL;
	solr_string_t *buffer = NULL;
	solr_char_t *delimiter;
	int delimiter_length;
	zend_bool success = 1;
	solr_request_type_t solr_request_type = SOLR_REQUEST_SEARCH;

	if (!return_value_used)
	{
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Return value requested but output not processed.");

		return;
	}

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &solr_params_obj, solr_ce_SolrParams) == FAILURE) {

		solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, SOLR_ERROR_4000_MSG);

		return;
	}

	/* Retrieve the client entry */
	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client");

		return;
	}

	/* Make sure the SolrParams object passed is a valid one */
	if (solr_fetch_params_entry(solr_params_obj, &solr_params TSRMLS_CC) == FAILURE) {

		solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "SolrParams parameter passed is not a valid one.");

		return ;
	}

	/* The SolrParams instance must contain at least one parameter */
	if (zend_hash_num_elements(solr_params->params) < 1)
	{
		solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "SolrParams parameter passed contains no parameters.");

		return ;
	}

	buffer = &(client->handle.request_body.buffer);

	delimiter = client->options.qs_delimiter.str;
	delimiter_length = client->options.qs_delimiter.len;

	/* Remove wt if any */
	zend_hash_del(solr_params->params, "wt", sizeof("wt")-1);

	if (solr_http_build_query(buffer, solr_params_obj, delimiter, delimiter_length TSRMLS_CC) == FAILURE)
	{
		solr_throw_exception_ex(solr_ce_SolrException, SOLR_ERROR_1003 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Error building HTTP query from parameters");

		return;
	}

	/* Always reset the URLs before making any request */
	solr_client_init_urls(client);

	/* terms.fl is a required parameter for the TermsComponent */
	if (zend_hash_exists(solr_params->params, "terms.fl", sizeof("terms.fl")-1))
	{
		/* Change the request type to a TermsComponent request */
		solr_request_type = SOLR_REQUEST_TERMS;
	}

	/* Make the HTTP request to the Solr instance */
	if (solr_make_request(client, solr_request_type TSRMLS_CC) == FAILURE)
	{
		success = 0;

		solr_throw_exception_ex(solr_ce_SolrClientException, SOLR_ERROR_1004 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Unsuccessful query request.");
	}

	object_init_ex(return_value, solr_ce_SolrQueryResponse);

	solr_set_response_object_properties(solr_ce_SolrQueryResponse, return_value, client, &(client->options.search_url), success TSRMLS_CC);
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::addDocument(SolrInputDocument doc [, bool allowDups [, int commitWithin]])
   Adds a document to the Solr server. */
PHP_METHOD(SolrClient, addDocument)
{
	zval *solr_input_doc = NULL;
	zend_bool allowDups = 0;
	long int commitWithin = 0L;
	solr_document_t *doc_entry = NULL;
	solr_client_t *client = NULL;
	HashTable *document_fields;
	xmlNode *root_node = NULL;
	xmlDoc *doc_ptr = NULL;
	char *allowDupsValue = NULL;
	int format = 1;
	int size   = 0;
	xmlChar *request_string = NULL;
	xmlNode *solr_doc_node = NULL;
	zend_bool success = 1;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O|bl", &solr_input_doc, solr_ce_SolrInputDocument, &allowDups, &commitWithin) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter.");

		return;
	}

	if (solr_fetch_document_entry(solr_input_doc, &doc_entry TSRMLS_CC) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "SolrInputDocument is not valid. Object not present in HashTable");

		return;
	}

	document_fields = doc_entry->fields;

	/* Document must contain at least one field */
	if (0 == zend_hash_num_elements(document_fields)) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "SolrInputDocument has no fields");

		return;
	}

	/* Retrieve the client entry */
	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client");

		return;
	}

	doc_ptr = solr_xml_create_xml_doc((xmlChar *) "add", &root_node);
	allowDupsValue = (allowDups)? "true" : "false";

	xmlNewProp(root_node, (xmlChar *) "allowDups", (xmlChar *) allowDupsValue);

	if (commitWithin > 0L)
	{
		auto char commitWithinBuffer[32];

		memset(commitWithinBuffer, 0, sizeof(commitWithinBuffer));

		php_sprintf(commitWithinBuffer, "%ld", commitWithin);

		xmlNewProp(root_node, (xmlChar *) "commitWithin", (xmlChar *) commitWithinBuffer);
	}

	solr_doc_node = xmlNewChild(root_node, NULL, (xmlChar *) "doc", NULL);

	if (doc_entry->document_boost > 0.0f)
	{
		auto char tmp_buffer[256]; /* Scratch pad for converting numeric values to strings */

		memset(tmp_buffer, 0, sizeof(tmp_buffer));

		php_sprintf(tmp_buffer, "%0.1f", doc_entry->document_boost);

		xmlNewProp(solr_doc_node, (xmlChar *) "boost", (xmlChar *) tmp_buffer);
	}

	solr_generate_document_xml_from_fields(solr_doc_node, document_fields);

	xmlIndentTreeOutput = 1;
	xmlDocDumpFormatMemoryEnc(doc_ptr, &request_string, &size, "UTF-8", format);

	/* The XML request we are sending to Solr */
	solr_string_set(&(client->handle.request_body.buffer), (solr_char_t *) request_string, size);

	xmlFree(request_string);
	xmlFreeDoc(doc_ptr);

	/* Always reset the URLs before making any request */
	solr_client_init_urls(client);

	/* Make the HTTP request to the Solr instance */
	if (solr_make_request(client, SOLR_REQUEST_UPDATE TSRMLS_CC) == FAILURE)
	{
		success = 0;

		solr_throw_exception_ex(solr_ce_SolrClientException, SOLR_ERROR_1004 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Unsuccessful update request.");
	}

	if (return_value_used)
	{
		object_init_ex(return_value, solr_ce_SolrUpdateResponse);

		solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
	}
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::addDocuments(array docs [, bool allowDups [, int commitWithin]])
   Adds an array of SolrInputDocuments to the Solr server. */
PHP_METHOD(SolrClient, addDocuments)
{
	zval *docs_array = NULL;
	zend_bool allowDups = 0;
	long int commitWithin = 0L;
	HashTable *solr_input_docs;
	size_t num_input_docs = 0;
	solr_client_t *client = NULL;
	solr_document_t **doc_entries = NULL;
	size_t curr_pos = 0U;
	zend_bool all_docs_are_valid = 1;
	xmlNode *root_node = NULL;
	xmlDoc *doc_ptr = NULL;
	const xmlChar *allowDupsValue;
	size_t pos = 0U;
	solr_document_t *current_doc_entry = NULL;
	int format = 1;
	int size = 0;
	zend_bool success = 1;
	xmlChar *request_string = NULL;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a|bl", &docs_array, &allowDups, &commitWithin) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		return;
	}

	solr_input_docs = Z_ARRVAL_P(docs_array);
	num_input_docs = zend_hash_num_elements(solr_input_docs);

	if(!num_input_docs)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "The array parameter passed is empty");

		return;
	}

	/* This should be released if there is an error */
	doc_entries = (solr_document_t **) pemalloc((sizeof(solr_document_t *) * (num_input_docs + 1)), SOLR_DOCUMENT_PERSISTENT);

	memset(doc_entries, 0, sizeof(solr_document_t *) * (num_input_docs + 1));

	/* Please check all the SolrInputDocument instances passed via the array */
	SOLR_HASHTABLE_FOR_LOOP(solr_input_docs)
	{
		zval **solr_input_doc = NULL;
		solr_document_t *doc_entry = NULL;
		HashTable *document_fields;

		zend_hash_get_current_data_ex(solr_input_docs, (void **) &solr_input_doc, ((HashPosition *)0));

		if (Z_TYPE_PP(solr_input_doc) != IS_OBJECT || !instanceof_function(Z_OBJCE_PP(solr_input_doc), solr_ce_SolrInputDocument TSRMLS_CC))
		{
			SOLR_FREE_DOC_ENTRIES(doc_entries);

			all_docs_are_valid = 0;

			solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "SolrInputDocument number %u is not a valid SolrInputDocument instance", (curr_pos + 1U));

			return;
		}

		if (solr_fetch_document_entry((*solr_input_doc), &doc_entry TSRMLS_CC) == FAILURE) {

			SOLR_FREE_DOC_ENTRIES(doc_entries);

			all_docs_are_valid = 0;

			solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "SolrInputDocument number %u is not valid. Object not present in HashTable", (curr_pos + 1U));

			return;
		}

		document_fields = doc_entry->fields;

		/* SolrInputDocument must contain at least one field */
		if (0 == zend_hash_num_elements(document_fields)) {

			SOLR_FREE_DOC_ENTRIES(doc_entries);

			all_docs_are_valid = 0;

			solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "SolrInputDocument number %u has no fields", (curr_pos + 1U));

			return;
		}

		doc_entries[curr_pos] = doc_entry;

		curr_pos++;
	}

	/* Mark the end of the list */
	doc_entries[curr_pos] = NULL;

	/* All the input documents have been validated. We can now retrieve the client entry */
	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		SOLR_FREE_DOC_ENTRIES(doc_entries);

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client from HashTable");

		return;
	}

	doc_ptr = solr_xml_create_xml_doc((xmlChar *) "add", &root_node);
	allowDupsValue = (allowDups) ? (xmlChar *) "true" : (xmlChar *) "false";

	xmlNewProp(root_node, (xmlChar *) "allowDups", allowDupsValue);

	if (commitWithin > 0L)
	{
		auto char commitWithinBuffer[32];

		memset(commitWithinBuffer, 0, sizeof(commitWithinBuffer));

		php_sprintf(commitWithinBuffer, "%ld", commitWithin);

		xmlNewProp(root_node, (xmlChar *) "commitWithin", (xmlChar *) commitWithinBuffer);
	}

	/* Grab the first (solr_document_t *) pointer */
	current_doc_entry = doc_entries[pos];

	while(current_doc_entry != NULL)
	{
		HashTable *document_fields = NULL;
		xmlNode *solr_doc_node = xmlNewChild(root_node, NULL, (xmlChar *) "doc", NULL);

		if (current_doc_entry->document_boost > 0.0f)
		{
			auto char tmp_buffer[256]; /* Scratch pad for converting numeric values to strings */

			memset(tmp_buffer, 0, sizeof(tmp_buffer));

			php_sprintf(tmp_buffer, "%0.1f", current_doc_entry->document_boost);

			xmlNewProp(solr_doc_node, (xmlChar *) "boost", (xmlChar *) tmp_buffer);
		}

		document_fields = current_doc_entry->fields;

		solr_generate_document_xml_from_fields(solr_doc_node, document_fields);

		pos++;

		/* Grab the next (solr_document_t *) pointer */
		current_doc_entry = doc_entries[pos];
	}

	/* We are done with the doc_entries pointer */
	SOLR_FREE_DOC_ENTRIES(doc_entries);

	xmlIndentTreeOutput = 1;

	xmlDocDumpFormatMemoryEnc(doc_ptr, &request_string, &size, "UTF-8", format);

	/* The XML request we are sending to Solr */
	solr_string_set(&(client->handle.request_body.buffer), (solr_char_t *) request_string, size);

	xmlFree(request_string);
	xmlFreeDoc(doc_ptr);

	/* Always reset the URLs before making any request */
	solr_client_init_urls(client);

	/* Make the HTTP request to the Solr instance */
	if (solr_make_request(client, SOLR_REQUEST_UPDATE TSRMLS_CC) == FAILURE)
	{
		success = 0;

		solr_throw_exception_ex(solr_ce_SolrClientException, SOLR_ERROR_1004 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Unsuccessful update request.");
	}

	if (return_value_used)
	{
		object_init_ex(return_value, solr_ce_SolrUpdateResponse);

		solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
	}
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::request(string request_string)
   Allows the user to send a manual XML update request */
PHP_METHOD(SolrClient, request)
{
	solr_char_t *request_string = NULL;
	int request_length = 0;
	solr_client_t *client = NULL;
	zend_bool success = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &request_string, &request_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		return;
	}

	if (!request_length)
	{
		solr_throw_exception(solr_ce_SolrIllegalArgumentException, "Invalid request length. Request string is empty.", SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC);

		return;
	}

	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client from HashTable");

		return;
	}

	/* The update request we are sending to Solr */
	solr_string_set(&(client->handle.request_body.buffer), request_string, request_length);

	/* Always reset the URLs before making any request */
	solr_client_init_urls(client);

	/* Make the HTTP request to the Solr instance */
	if (solr_make_request(client, SOLR_REQUEST_UPDATE TSRMLS_CC) == FAILURE)
	{
		success = 0;

		solr_throw_exception_ex(solr_ce_SolrClientException, SOLR_ERROR_1004 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Unsuccessful update request.");
	}

	if (return_value_used)
	{
		object_init_ex(return_value, solr_ce_SolrUpdateResponse);

		solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
	}
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::deleteById(string id)
   Allows the user to delete a document by id */
PHP_METHOD(SolrClient, deleteById)
{
	solr_char_t *id = NULL;
	long int id_length = 0L;
	solr_client_t *client = NULL;
	xmlNode *root_node = NULL;
	xmlDoc *doc_ptr = NULL;
	xmlChar *escaped_id_value = NULL;
	int format = 1;
	int size = 0;
	xmlChar *request_string = NULL;
	zend_bool success = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &id, &id_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		return;
	}

	if (!id_length)
	{
		solr_throw_exception(solr_ce_SolrIllegalArgumentException, "Invalid id parameter", SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC);

		return;
	}

	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client from HashTable");

		return;
	}

	doc_ptr = solr_xml_create_xml_doc((xmlChar *) "delete", &root_node);
	escaped_id_value = xmlEncodeEntitiesReentrant(doc_ptr, (xmlChar *) id);

	xmlNewChild(root_node, NULL, (xmlChar *) "id", escaped_id_value);
	xmlFree(escaped_id_value);

	xmlIndentTreeOutput = 1;

	xmlDocDumpFormatMemoryEnc(doc_ptr, &request_string, &size, "UTF-8", format);

	/* The XML request we are sending to Solr */
	solr_string_set(&(client->handle.request_body.buffer), (solr_char_t *) request_string, size);

	xmlFree(request_string);
	xmlFreeDoc(doc_ptr);

	/* Always reset the URLs before making any request */
	solr_client_init_urls(client);

	/* Make the HTTP request to the Solr instance */
	if (solr_make_request(client, SOLR_REQUEST_UPDATE TSRMLS_CC) == FAILURE)
	{
		success = 0;

		solr_throw_exception_ex(solr_ce_SolrClientException, SOLR_ERROR_1004 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Unsuccessful update request.");
	}

	if (return_value_used)
	{
		object_init_ex(return_value, solr_ce_SolrUpdateResponse);

		solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
	}
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::request(array ids)
   Allows the user to delete a set of documents by ids. This should be an array of strings */
PHP_METHOD(SolrClient, deleteByIds)
{
	zval *ids_array = NULL;
	HashTable *doc_ids = NULL;
	size_t num_ids;
	xmlNode *root_node = NULL;
	xmlDoc *doc_ptr = NULL;
	zend_bool invalid_param = 0;
	size_t error_pos = 1, current_position = 1;
	solr_client_t *client = NULL;
	int format = 1;
	int size = 0;
	xmlChar *request_string = NULL;
	zend_bool success = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &ids_array) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		return;
	}

	doc_ids = Z_ARRVAL_P(ids_array);
	num_ids = zend_hash_num_elements(doc_ids);

	if(!num_ids)
	{
		solr_throw_exception(solr_ce_SolrIllegalArgumentException, "The array parameter passed is empty", SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC);

		return;
	}

	doc_ptr = solr_xml_create_xml_doc((xmlChar *) "delete", &root_node);

	SOLR_HASHTABLE_FOR_LOOP(doc_ids)
	{
		zval **id_zval = NULL;

		zend_hash_get_current_data_ex(doc_ids, (void **) &id_zval, ((HashPosition *)0));

		if (Z_TYPE_PP(id_zval) == IS_STRING && Z_STRLEN_PP(id_zval))
		{
			xmlChar *escaped_id_value = xmlEncodeEntitiesReentrant(doc_ptr, (xmlChar *) Z_STRVAL_PP(id_zval));

			xmlNewChild(root_node, NULL, (xmlChar *) "id", escaped_id_value);

			xmlFree(escaped_id_value);

		} else {

			invalid_param = 1; /* This id is not a valid string */

			error_pos = current_position;

			goto end_doc_ids_loop;
		}

		current_position++;
	}

end_doc_ids_loop :

	if (invalid_param)
	{
		xmlFreeDoc(doc_ptr);

		solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Id number %u is not a valid string", error_pos);

		return;
	}

	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client from HashTable");

		return;
	}

	xmlIndentTreeOutput = 1;

	xmlDocDumpFormatMemoryEnc(doc_ptr, &request_string, &size, "UTF-8", format);

	/* The XML request we are sending to Solr */
	solr_string_set(&(client->handle.request_body.buffer), (solr_char_t *) request_string, size);

	xmlFree(request_string);
	xmlFreeDoc(doc_ptr);

	/* Always reset the URLs before making any request */
	solr_client_init_urls(client);

	/* Make the HTTP request to the Solr instance */
	if (solr_make_request(client, SOLR_REQUEST_UPDATE TSRMLS_CC) == FAILURE)
	{
		success = 0;

		solr_throw_exception_ex(solr_ce_SolrClientException, SOLR_ERROR_1004 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Unsuccessful update request.");
	}

	if (return_value_used)
	{
		object_init_ex(return_value, solr_ce_SolrUpdateResponse);

		solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
	}
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::deleteByQuery(string query)
   Allows the user to delete a set of documents matching the query */
PHP_METHOD(SolrClient, deleteByQuery)
{
	solr_char_t *query = NULL;
	long int query_length = 0L;
	solr_client_t *client = NULL;
	xmlNode *root_node = NULL;
	xmlDoc *doc_ptr = NULL;
	xmlChar *escaped_query_value = NULL;
	int format = 1;
	int size = 0;
	xmlChar *request_string = NULL;
	zend_bool success = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &query, &query_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		return;
	}

	if (!query_length)
	{
		solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "The query parameter is not a valid id");

		return;
	}

	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client from HashTable");

		return;
	}

	doc_ptr = solr_xml_create_xml_doc((xmlChar *) "delete", &root_node);
	escaped_query_value = xmlEncodeEntitiesReentrant(doc_ptr, (xmlChar *) query);

	xmlNewChild(root_node, NULL, (xmlChar *) "query", escaped_query_value);
	xmlFree(escaped_query_value);

	xmlIndentTreeOutput = 1;

	xmlDocDumpFormatMemoryEnc(doc_ptr, &request_string, &size, "UTF-8", format);

	/* The XML request we are sending to Solr */
	solr_string_set(&(client->handle.request_body.buffer), (solr_char_t *) request_string, size);

	xmlFree(request_string);
	xmlFreeDoc(doc_ptr);

	/* Always reset the URLs before making any request */
	solr_client_init_urls(client);

	/* Make the HTTP request to the Solr instance */
	if (solr_make_request(client, SOLR_REQUEST_UPDATE TSRMLS_CC) == FAILURE)
	{
		success = 0;

		solr_throw_exception_ex(solr_ce_SolrClientException, SOLR_ERROR_1004 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Unsuccessful update request.");
	}

	if (return_value_used)
	{
		object_init_ex(return_value, solr_ce_SolrUpdateResponse);

		solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
	}
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::deleteByQueries(array queries)
   Allows the user to delete a set of documents matching the queries specified */
PHP_METHOD(SolrClient, deleteByQueries)
{
	zval *queries_array = NULL;
	HashTable *doc_queries = NULL;
	size_t num_queries;
	xmlNode *root_node = NULL;
	xmlDoc *doc_ptr = NULL;
	zend_bool invalid_param = 0;
	size_t error_pos, current_position = 1;
	solr_client_t *client = NULL;
	int format = 1;
	int size = 0;
	xmlChar *request_string = NULL;
	zend_bool success = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &queries_array) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		return;
	}

	doc_queries = Z_ARRVAL_P(queries_array);
	num_queries = zend_hash_num_elements(doc_queries);

	if(!num_queries)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "The array parameter passed is empty");

		return;
	}

	doc_ptr = solr_xml_create_xml_doc((xmlChar *) "delete", &root_node);

	SOLR_HASHTABLE_FOR_LOOP(doc_queries)
	{
		zval **query_zval = NULL;

		zend_hash_get_current_data_ex(doc_queries, (void **) &query_zval, ((HashPosition *)0));

		if (Z_TYPE_PP(query_zval) == IS_STRING && Z_STRLEN_PP(query_zval))
		{
			xmlChar *escaped_query_value = xmlEncodeEntitiesReentrant(doc_ptr, (xmlChar *) Z_STRVAL_PP(query_zval));

			xmlNewChild(root_node, NULL, (xmlChar *) "query", escaped_query_value);

			xmlFree(escaped_query_value);

		} else {

			invalid_param = 1; /* This query is not a valid string */

			error_pos = current_position;

			goto end_doc_queries_loop;
		}

		current_position++;
	}

end_doc_queries_loop :

	if (invalid_param)
	{
		xmlFreeDoc(doc_ptr);

		solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Query number %u is not a valid query string", error_pos);

		return;
	}

	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client from HashTable");

		return;
	}

	xmlIndentTreeOutput = 1;

	xmlDocDumpFormatMemoryEnc(doc_ptr, &request_string, &size, "UTF-8", format);

	/* The XML request we are sending to Solr */
	solr_string_set(&(client->handle.request_body.buffer), (solr_char_t *) request_string, size);

	xmlFree(request_string);
	xmlFreeDoc(doc_ptr);

	/* Always reset the URLs before making any request */
	solr_client_init_urls(client);

	/* Make the HTTP request to the Solr instance */
	if (solr_make_request(client, SOLR_REQUEST_UPDATE TSRMLS_CC) == FAILURE)
	{
		success = 0;

		solr_throw_exception_ex(solr_ce_SolrClientException, SOLR_ERROR_1004 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Unsuccessful update request.");
	}

	if (return_value_used)
	{
		object_init_ex(return_value, solr_ce_SolrUpdateResponse);

		solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
	}
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::optimize([string maxSegments [, bool waitFlush [, bool waitSearcher]])
   Sends an optimize XML request to the server. */
PHP_METHOD(SolrClient, optimize)
{
	zend_bool waitFlush = 1, waitSearcher = 1;
	char *maxSegments = "1";
	int maxSegmentsLen = sizeof("1")-1;
	char *waitFlushValue, *waitSearcherValue;
	xmlNode *root_node = NULL;
	xmlDoc *doc_ptr = NULL;
	solr_client_t *client = NULL;
	int format = 1;
	int size = 0;
	xmlChar *request_string = NULL;
	zend_bool success = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|sbb", &maxSegments, &maxSegmentsLen, &waitFlush, &waitSearcher) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		return;
	}

	waitFlushValue = (waitFlush)? "true" : "false";
	waitSearcherValue = (waitSearcher)? "true" : "false";

	doc_ptr = solr_xml_create_xml_doc((xmlChar *) "optimize", &root_node);

	xmlNewProp(root_node, (xmlChar *) "maxSegments", (xmlChar *) maxSegments);
	xmlNewProp(root_node, (xmlChar *) "waitFlush", (xmlChar *) waitFlushValue);
	xmlNewProp(root_node, (xmlChar *) "waitSearcher", (xmlChar *) waitSearcherValue);

	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client from HashTable");

		return;
	}

	xmlIndentTreeOutput = 1;

	xmlDocDumpFormatMemoryEnc(doc_ptr, &request_string, &size, "UTF-8", format);

	/* The XML request we are sending to Solr */
	solr_string_set(&(client->handle.request_body.buffer), (solr_char_t *) request_string, size);

	xmlFree(request_string);
	xmlFreeDoc(doc_ptr);

	/* Always reset the URLs before making any request */
	solr_client_init_urls(client);

	/* Make the HTTP request to the Solr instance */
	if (solr_make_request(client, SOLR_REQUEST_UPDATE TSRMLS_CC) == FAILURE)
	{
		success = 0;

		solr_throw_exception_ex(solr_ce_SolrClientException, SOLR_ERROR_1004 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Unsuccessful update request.");
	}

	if (return_value_used)
	{
		object_init_ex(return_value, solr_ce_SolrUpdateResponse);

		solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
	}
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::commit([string maxSegments [, bool waitFlush [, bool waitSearcher]])
   Sends a commit XML request to the server. */
PHP_METHOD(SolrClient, commit)
{
	zend_bool waitFlush = 1, waitSearcher = 1;
	char *maxSegments = "1";
	int maxSegmentsLen = sizeof("1")-1;
	char *waitFlushValue, *waitSearcherValue;
	xmlNode *root_node = NULL;
	xmlDoc *doc_ptr = NULL;
	solr_client_t *client = NULL;
	int format = 1;
	int size = 0;
	xmlChar *request_string = NULL;
	zend_bool success = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|sbb", &maxSegments, &maxSegmentsLen, &waitFlush, &waitSearcher) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		return;
	}

	waitFlushValue = (waitFlush)? "true" : "false";
	waitSearcherValue = (waitSearcher)? "true" : "false";

	doc_ptr = solr_xml_create_xml_doc((xmlChar *) "commit", &root_node);

	xmlNewProp(root_node, (xmlChar *) "maxSegments", (xmlChar *) maxSegments);
	xmlNewProp(root_node, (xmlChar *) "waitFlush", (xmlChar *) waitFlushValue);
	xmlNewProp(root_node, (xmlChar *) "waitSearcher", (xmlChar *) waitSearcherValue);

	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client from HashTable");

		return;
	}

	xmlIndentTreeOutput = 1;

	xmlDocDumpFormatMemoryEnc(doc_ptr, &request_string, &size, "UTF-8", format);

	/* The XML request we are sending to Solr */
	solr_string_set(&(client->handle.request_body.buffer), (solr_char_t *) request_string, size);

	xmlFree(request_string);
	xmlFreeDoc(doc_ptr);

	/* Always reset the URLs before making any request */
	solr_client_init_urls(client);

	/* Make the HTTP request to the Solr instance */
	if (solr_make_request(client, SOLR_REQUEST_UPDATE TSRMLS_CC) == FAILURE)
	{
		success = 0;

		solr_throw_exception_ex(solr_ce_SolrClientException, SOLR_ERROR_1004 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Unsuccessful update request.");
	}

	if (return_value_used)
	{
		object_init_ex(return_value, solr_ce_SolrUpdateResponse);

		solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
	}
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::rollback(void)
   Sends a rollback XML request to the server. */
PHP_METHOD(SolrClient, rollback)
{
	xmlNode *root_node = NULL;
	zend_bool success = 1;
	xmlDoc *doc_ptr = NULL;
	solr_client_t *client = NULL;
	int format = 1;
	int size = 0;
	xmlChar *request_string = NULL;

	doc_ptr = solr_xml_create_xml_doc((xmlChar *) "rollback", &root_node);

	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client from HashTable");

		return;
	}

	xmlIndentTreeOutput = 1;

	xmlDocDumpFormatMemoryEnc(doc_ptr, &request_string, &size, "UTF-8", format);

	/* The XML request we are sending to Solr */
	solr_string_set(&(client->handle.request_body.buffer), (solr_char_t *) request_string, size);

	xmlFree(request_string);
	xmlFreeDoc(doc_ptr);

	/* Always reset the URLs before making any request */
	solr_client_init_urls(client);

	/* Make the HTTP request to the Solr instance */
	if (solr_make_request(client, SOLR_REQUEST_UPDATE TSRMLS_CC) == FAILURE)
	{
		success = 0;

		solr_throw_exception_ex(solr_ce_SolrClientException, SOLR_ERROR_1004 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Unsuccessful update request.");
	}

	if (return_value_used)
	{
		object_init_ex(return_value, solr_ce_SolrUpdateResponse);

		solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
	}
}
/* }}} */

/* {{{ proto SolrPingResponse SolrClient::ping()
   Sends a HEAD request to check if the server is still up and running. */
PHP_METHOD(SolrClient, ping)
{
	solr_client_t *client = NULL;
	zend_bool success = 1;

	/* Retrieve the client entry */
	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client");

		return;
	}

	/* Always reset the URLs before making any request */
	solr_client_init_urls(client);

	/* Make the HTTP request to the Solr instance */
	if (solr_make_request(client, SOLR_REQUEST_PING TSRMLS_CC) == FAILURE)
	{
		success = 0;

		solr_throw_exception_ex(solr_ce_SolrClientException, SOLR_ERROR_1004 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Failed ping request");
	}

	if (return_value_used)
	{
		object_init_ex(return_value, solr_ce_SolrPingResponse);

		solr_set_response_object_properties(solr_ce_SolrPingResponse, return_value, client, &(client->options.ping_url), success TSRMLS_CC);
	}
}
/* }}} */

/* {{{ proto SolrGenericResponse SolrClient::threads()
   Sends a request to get info about threads. */
PHP_METHOD(SolrClient, threads)
{
	zend_bool success = 1;
	solr_client_t *client = NULL;

	if (!return_value_used)
	{
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Return value requested but output not processed.");

		return;
	}

	/* Retrieve the client entry */
	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client");

		return;
	}

	/* Always reset the URLs before making any request */
	solr_client_init_urls(client);

	/* Make the HTTP request to the Solr instance */
	if (solr_make_request(client, SOLR_REQUEST_THREADS TSRMLS_CC) == FAILURE)
	{
		solr_throw_exception_ex(solr_ce_SolrClientException, SOLR_ERROR_1004 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Failed threads request");

		success = 0;
	}

	object_init_ex(return_value, solr_ce_SolrGenericResponse);

	solr_set_response_object_properties(solr_ce_SolrGenericResponse, return_value, client, &(client->options.thread_url), success TSRMLS_CC);
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

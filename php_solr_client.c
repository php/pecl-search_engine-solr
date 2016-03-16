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

/* {{{ Macros */


/* resets the key_str with key and tries to find the zv */
static inline int solr_opt_check(HashTable *options_ht, const char * key, zend_string * key_str, zval ** zv)
{
    int result = 0;
    key_str = zend_string_init(key, strlen (key), 0);
    result = (*zv = zend_hash_find(options_ht, key_str)) != NULL;
    zend_string_release(key_str);
    return result;
}

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
	solr_string_free(&(options->system_url));
	solr_string_free(&(options->get_url));

	/* Making http://hostname:host_port/path/ */

	if (options->secure)
	{
		solr_string_append_const(&url_prefix, "https://");

	} else {

		solr_string_append_const(&url_prefix, "http://");
	}

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
	solr_string_append_solr_string(&(options->terms_url),  &url_prefix);
	solr_string_append_solr_string(&(options->system_url),  &url_prefix);
	solr_string_append_solr_string(&(options->get_url),  &url_prefix);

	/* Making http://hostname:host_port/path/servlet/ */
	solr_string_append_solr_string(&(options->update_url), &(options->update_servlet));
	solr_string_append_solr_string(&(options->search_url), &(options->search_servlet));
	solr_string_append_solr_string(&(options->thread_url), &(options->thread_servlet));
	solr_string_append_solr_string(&(options->ping_url),   &(options->ping_servlet));
	solr_string_append_solr_string(&(options->terms_url),  &(options->terms_servlet));
	solr_string_append_solr_string(&(options->system_url),  &(options->system_servlet));
	solr_string_append_solr_string(&(options->get_url), &(options->get_servlet));

	solr_string_append_const(&(options->update_url), "/?version=2.2&indent=on&wt=");
	solr_string_append_const(&(options->search_url), "/?version=2.2&indent=on&wt=");
	solr_string_append_const(&(options->thread_url), "/?version=2.2&indent=on&wt=");
	solr_string_append_const(&(options->ping_url),   "/?version=2.2&indent=on&wt=");
	solr_string_append_const(&(options->terms_url),  "/?version=2.2&indent=on&wt=");
	solr_string_append_const(&(options->system_url),  "/?version=2.2&indent=on&wt=");
	solr_string_append_const(&(options->get_url),  "/?version=2.2&indent=on&wt=");

	solr_string_append_solr_string(&(options->update_url), &(options->response_writer));
	solr_string_append_solr_string(&(options->search_url), &(options->response_writer));
	solr_string_append_solr_string(&(options->thread_url), &(options->response_writer));
	solr_string_append_solr_string(&(options->ping_url),   &(options->response_writer));
	solr_string_append_solr_string(&(options->terms_url),  &(options->response_writer));
	solr_string_append_solr_string(&(options->system_url),  &(options->response_writer));
	solr_string_append_solr_string(&(options->get_url),  &(options->response_writer));

	solr_string_free(&url_prefix);
}
/* }}} */

/* {{{ static int solr_http_build_query(solr_string_t *buffer, zval *params_objptr, const solr_char_t *delimiter, int delimiter_length TSRMLS_DC) */
static int solr_http_build_query(solr_string_t *buffer, zval *params_objptr, const solr_char_t *delimiter, int delimiter_length TSRMLS_DC)
{
	solr_params_t *solr_params = NULL;
	HashTable *params = NULL;
	solr_param_t *solr_param = NULL;

	if (solr_fetch_params_entry(params_objptr, &solr_params TSRMLS_CC) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve solr_params_t");

		return FAILURE;
	}

	params = solr_params->params;


	ZEND_HASH_FOREACH_PTR(params, solr_param)
	{

		solr_string_t tmp_values_buffer;

		memset(&tmp_values_buffer, 0, sizeof(solr_string_t));

		solr_param->fetch_func(solr_param, &tmp_values_buffer);

		solr_string_append_solr_string(buffer, &tmp_values_buffer);
		solr_string_appends(buffer, delimiter, delimiter_length);
		solr_string_free(&tmp_values_buffer);
	} ZEND_HASH_FOREACH_END();


	solr_string_remove_last_char(buffer);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_SOLR_API solr_client_t* solr_init_client(zval * objptr TSRMLS_DC)
  inititialize solr_client_t and update zval's index
 */
PHP_SOLR_API solr_client_t *solr_init_client(zval *objptr TSRMLS_DC)
{
    long int client_index = SOLR_UNIQUE_CLIENT_INDEX();
    solr_client_t *solr_client = NULL;

    zend_update_property_long(solr_ce_SolrClient, objptr, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, client_index TSRMLS_CC);

    solr_client = (solr_client_t *) pemalloc(sizeof(solr_client_t), SOLR_CLIENT_PERSISTENT);

    memset(solr_client, 0, sizeof(solr_client_t));

    solr_client->client_index = client_index;
    if ((solr_client = zend_hash_index_update_ptr(SOLR_GLOBAL(clients), client_index, (void *)solr_client)) == NULL) {
        pefree(solr_client, SOLR_CLIENT_PERSISTENT);
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error while registering client in HashTable");
        return NULL;
    }
    return solr_client;
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
	HashTable *options_ht = NULL;
	zval *tmp1 = NULL, *tmp2 = NULL;
	solr_client_t *solr_client_dest = NULL;
	solr_client_options_t *client_options = NULL;
	solr_curl_t *handle = NULL;
	zend_string *key_str; /* tmp storage to use with zend_hash_find */
	key_str = zend_string_init("", 0, 0);

	size_t num_options = 0;

	long int secure = 0L;
	long int verify_peer = 0L;
	long int verify_host = 2L;
	long int timeout = 30L;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &options) == FAILURE) {
	    zend_string_release(key_str);
		solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Invalid parameter. The client options array is required for a SolrClient instance. It must also be passed as the only parameter");
		return;
	}

	options_ht = Z_ARRVAL_P(options);

	num_options = zend_hash_num_elements(options_ht);

	if (!num_options) {
	    zend_string_release(key_str);
		solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "The SolrClient options cannot be an empty array");
		return;
	}

	solr_client_dest = solr_init_client(objptr TSRMLS_CC);
	if (!solr_client_dest) {
	    zend_string_release(key_str);
	    solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Unable to initialize solr_client_t ");
	    return;
	}

	/* Release the original pointer */

	client_options = &(solr_client_dest->options);
	handle = &(solr_client_dest->handle);

	solr_init_options(client_options TSRMLS_CC);

	solr_string_append_const(&(client_options->response_writer), SOLR_XML_RESPONSE_WRITER);

	solr_string_append_const(&(client_options->update_servlet), SOLR_DEFAULT_UPDATE_SERVLET);
	solr_string_append_const(&(client_options->search_servlet), SOLR_DEFAULT_SEARCH_SERVLET);
	solr_string_append_const(&(client_options->thread_servlet), SOLR_DEFAULT_THREADS_SERVLET);
	solr_string_append_const(&(client_options->ping_servlet),   SOLR_DEFAULT_PING_SERVLET);
	solr_string_append_const(&(client_options->terms_servlet),  SOLR_DEFAULT_TERMS_SERVLET);
	solr_string_append_const(&(client_options->system_servlet),  SOLR_DEFAULT_SYSTEM_SERVLET);
	solr_string_append_const(&(client_options->get_servlet), SOLR_DEFAULT_GET_SERVLET);

	if ( solr_opt_check(options_ht, "wt", key_str, &tmp1) && Z_TYPE_P(tmp1) == IS_STRING && Z_STRLEN_P(tmp1))
	{
		if (solr_is_supported_response_writer((solr_char_t *)Z_STRVAL_P(tmp1), Z_STRLEN_P(tmp1))) {
			solr_string_set(&(client_options->response_writer), (const solr_char_t *) Z_STRVAL_P(tmp1), Z_STRLEN_P(tmp1));
		} else {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unsupported response writer %s. This value will be ignored", Z_STRVAL_P(tmp1));
		}
	}

	if (solr_opt_check(options_ht, "secure", key_str, &tmp1))
	{
		if (Z_TYPE_P(tmp1) == IS_TRUE)
		{
			secure = (long int) 1L;
		} else if (Z_TYPE_P(tmp1) == IS_LONG) {
			secure = Z_LVAL_P(tmp1);
		}
	}

	client_options->secure = secure;

/**
 * FOR NOW LET'S LEAVE IT AT 2 : This will force and require a match on the common name
 *
	if (secure && zend_hash_find(options_ht, "ssl_verifyhost", sizeof("ssl_verifyhost"), (void**) &tmp1) == SUCCESS && Z_TYPE_P(tmp1) == IS_LONG)
	{
		verify_host = ((Z_LVAL_P(tmp1) > 0L && Z_LVAL_P(tmp1) < 3L) ? Z_LVAL_P(tmp1) : verify_host);
	}
*/
	client_options->ssl_verify_host = verify_host;

	if (secure && solr_opt_check(options_ht, "ssl_cert", key_str, &tmp1) && Z_TYPE_P(tmp1) == IS_STRING && Z_STRLEN_P(tmp1))
	{
		verify_peer = 1L;

		solr_string_appends(&(client_options->ssl_cert), Z_STRVAL_P(tmp1), Z_STRLEN_P(tmp1));
	}

	if (secure && solr_opt_check(options_ht, "ssl_key", key_str, &tmp1) && Z_TYPE_P(tmp1) == IS_STRING && Z_STRLEN_P(tmp1))
	{
		verify_peer = 1L;
		solr_string_appends(&(client_options->ssl_key), (solr_char_t *) Z_STRVAL_P(tmp1), Z_STRLEN_P(tmp1));
	}

	if (secure && solr_opt_check(options_ht, "ssl_keypassword", key_str, &tmp1) && Z_TYPE_P(tmp1) == IS_STRING && Z_STRLEN_P(tmp1))
	{
		verify_peer = 1L;

		solr_string_appends(&(client_options->ssl_keypassword), (solr_char_t *) Z_STRVAL_P(tmp1), Z_STRLEN_P(tmp1));
	}
	// ssl_cainfo
	if (secure && solr_opt_check(options_ht, "ssl_cainfo", key_str, &tmp1) && Z_TYPE_P(tmp1) == IS_STRING && Z_STRLEN_P(tmp1))
	{
		verify_peer = 1L;

		solr_string_appends(&(client_options->ssl_cainfo), (solr_char_t *) Z_STRVAL_P(tmp1), Z_STRLEN_P(tmp1));
	}
	// ssl_capath
	if (secure && solr_opt_check(options_ht, "ssl_capath", key_str, &tmp1) && Z_TYPE_P(tmp1) == IS_STRING && Z_STRLEN_P(tmp1))
	{
		verify_peer = 1L;

		solr_string_appends(&(client_options->ssl_capath), (solr_char_t *) Z_STRVAL_P(tmp1), Z_STRLEN_P(tmp1));
	}

	client_options->ssl_verify_peer = verify_peer;
	// hostname
	if (solr_opt_check(options_ht, "hostname", key_str, &tmp1) && Z_TYPE_P(tmp1) == IS_STRING && Z_STRLEN_P(tmp1))
	{
		solr_string_appends(&(client_options->hostname), (solr_char_t *) Z_STRVAL_P(tmp1), Z_STRLEN_P(tmp1));
	} else {
		solr_string_append_const(&(client_options->hostname), SOLR_REQUEST_DEFAULT_HOST);
	}

	// port
	if (solr_opt_check(options_ht, "port", key_str, &tmp1) && Z_TYPE_P(tmp1) == IS_LONG)
	{
		client_options->host_port = Z_LVAL_P(tmp1);
	} else if (solr_opt_check(options_ht, "port", key_str, &tmp1) && Z_TYPE_P(tmp1) == IS_STRING && Z_STRLEN_P(tmp1)) {

		long int host_port = atol(Z_STRVAL_P(tmp1));

		if (host_port) {
			client_options->host_port = host_port;
		} else {
			client_options->host_port = SOLR_REQUEST_DEFAULT_PORT;
		}

	} else {
		client_options->host_port = SOLR_REQUEST_DEFAULT_PORT;
	}

	if (solr_opt_check(options_ht, "timeout", key_str, &tmp1))
	{
		long int timeout_value = 30L;

		if (Z_TYPE_P(tmp1) == IS_LONG)
		{
			timeout_value = Z_LVAL_P(tmp1);

		} else if (Z_TYPE_P(tmp1) == IS_STRING && Z_STRLEN_P(tmp1)) {

			timeout_value = atol(Z_STRVAL_P(tmp1));
		}

		timeout = ((timeout_value > 0L) ? timeout_value : timeout);
	}

	client_options->timeout = timeout;

	if (solr_opt_check(options_ht, "path", key_str, &tmp1) && Z_TYPE_P(tmp1) == IS_STRING && Z_STRLEN_P(tmp1))
	{
		char *path_to_solr = Z_STRVAL_P(tmp1);

		size_t path_to_solr_start = 0;

		size_t length_adjustment  = 0;

		if (path_to_solr[0] == '/')
		{
			path_to_solr_start = length_adjustment = 1;
		}

		if (path_to_solr[Z_STRLEN_P(tmp1)] == '/')
		{
			length_adjustment++;
		}

		solr_string_appends(&(client_options->path), Z_STRVAL_P(tmp1) + path_to_solr_start, Z_STRLEN_P(tmp1) - length_adjustment);

	} else {
		solr_string_append_const(&(client_options->path), SOLR_REQUEST_DEFAULT_PATH);
	}

	if (
	        solr_opt_check(options_ht, "query_string_delimiter", key_str, &tmp1)
	        && Z_TYPE_P(tmp1) == IS_STRING)
	{
		solr_string_appends(&(client_options->qs_delimiter), Z_STRVAL_P(tmp1), Z_STRLEN_P(tmp1));
	} else {
		solr_string_append_const(&(client_options->qs_delimiter), SOLR_REQUEST_DEFAULT_QS_DELIMITER);
	}

	if (
	        solr_opt_check(options_ht, "login", key_str, &tmp1) && Z_TYPE_P(tmp1) == IS_STRING
	        && solr_opt_check(options_ht, "password", key_str, &tmp2) && Z_TYPE_P(tmp2) == IS_STRING)
	{
		solr_string_appends(&(client_options->http_auth_credentials), Z_STRVAL_P(tmp1), Z_STRLEN_P(tmp1));
		solr_string_appendc(&(client_options->http_auth_credentials), ':');
		solr_string_appends(&(client_options->http_auth_credentials), Z_STRVAL_P(tmp2), Z_STRLEN_P(tmp2));
	}

	if (solr_opt_check(options_ht, "proxy_host", key_str, &tmp1) && Z_TYPE_P(tmp1) == IS_STRING)
	{
		solr_string_appends(&(client_options->proxy_hostname), Z_STRVAL_P(tmp1), Z_STRLEN_P(tmp1));
	}

	if (solr_opt_check(options_ht, "proxy_port", key_str, &tmp1))
	{
		long int proxy_port_value = 0L;

		if (Z_TYPE_P(tmp1) == IS_LONG)
		{
			proxy_port_value = Z_LVAL_P(tmp1);
		} else if (Z_TYPE_P(tmp1) == IS_STRING && Z_STRLEN_P(tmp1)) {
			proxy_port_value = atol(Z_STRVAL_P(tmp1));
		}

		if (proxy_port_value > 0L)
		{
			client_options->proxy_port = proxy_port_value;
		}
	}

	if (solr_opt_check(options_ht, "proxy_login", key_str, &tmp1) && Z_TYPE_P(tmp1) == IS_STRING
	        && solr_opt_check(options_ht, "proxy_password", key_str, &tmp2) && Z_TYPE_P(tmp2) == IS_STRING)
	{
		solr_string_appends(&(client_options->proxy_auth_credentials), Z_STRVAL_P(tmp1), Z_STRLEN_P(tmp1));
		solr_string_appendc(&(client_options->proxy_auth_credentials), ':');
		solr_string_appends(&(client_options->proxy_auth_credentials), Z_STRVAL_P(tmp2), Z_STRLEN_P(tmp2));
	}

	solr_init_handle(handle, client_options TSRMLS_CC);
	zend_string_free(key_str);

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
    solr_init_client(getThis() TSRMLS_CC);
    solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1001 TSRMLS_CC, SOLR_FILE_LINE_FUNC, SOLR_ERROR_1001_MSG);
}
/* }}} */

/* {{{ proto SolrClient::__wakeup(void)
   Should not be called directly. Serialization is not supported. */
PHP_METHOD(SolrClient, __wakeup)
{
    solr_init_client(getThis() TSRMLS_CC);
    solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1001 TSRMLS_CC, SOLR_FILE_LINE_FUNC, SOLR_ERROR_1001_MSG);
}
/* }}} */

/* {{{ proto SolrClient::__clone(void)
   Should not be called directly. Cloning is not supported. */
PHP_METHOD(SolrClient, __clone)
{
    solr_init_client(getThis() TSRMLS_CC);
    solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_4001 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Cloning of SolrClient objects is currently not supported");
}
/* }}} */

/* {{{ proto bool SolrClient::setServelet(int servlet_type, string new_value)
   Changes the specified servlet type to a new value */
PHP_METHOD(SolrClient, setServlet)
{
	long int servlet_type_value = 0L;
	solr_char_t *new_servlet_value = NULL;
	COMPAT_ARG_SIZE_T new_servlet_value_length = 0;
	solr_client_t *client = NULL;
	solr_servlet_type_t servlet_type = SOLR_SERVLET_TYPE_BEGIN;

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
		case SOLR_SERVLET_TYPE_SYSTEM :
				{
					solr_string_set(&(client->options.system_servlet), new_servlet_value, new_servlet_value_length);
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

// client->handle.err.str client->handle.request_body_debug.buffer.str

/* {{{ proto SolrQueryResponse SolrClient::query(SolrParams query)
   Sends a name-value pair request to the Solr server. */
PHP_METHOD(SolrClient, query)
{
	zval *solr_params_obj = NULL;
	solr_client_t *client = NULL;
	solr_params_t *solr_params = NULL;
	solr_string_t *buffer = NULL;
	solr_char_t *delimiter = NULL;
	COMPAT_ARG_SIZE_T delimiter_length = 0;
	zend_bool success = 1;
	solr_request_type_t solr_request_type = SOLR_REQUEST_SEARCH;
	solr_string_t *request_url = NULL;

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

	/* Get rid of all the data from the previous request */
	solr_string_free(buffer);

	delimiter = client->options.qs_delimiter.str;

	delimiter_length = client->options.qs_delimiter.len;

	/* Remove wt if any */
	zend_hash_str_del(solr_params->params, "wt", sizeof("wt")-1);

	if (solr_http_build_query(buffer, solr_params_obj, delimiter, delimiter_length TSRMLS_CC) == FAILURE)
	{
		solr_throw_exception_ex(solr_ce_SolrException, SOLR_ERROR_1003 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Error building HTTP query from parameters");

		return;
	}

	/* Always reset the URLs before making any request */
	solr_client_init_urls(client);

	request_url = &(client->options.search_url);
	/* terms.fl is a required parameter for the TermsComponent */
	if (zend_hash_str_exists(solr_params->params, "terms.fl", sizeof("terms.fl")-1))
	{
		/* Change the request type to a TermsComponent request */
		solr_request_type = SOLR_REQUEST_TERMS;
		request_url =&(client->options.terms_url);
	}

	/* Make the HTTP request to the Solr instance */
	if (solr_make_request(client, solr_request_type TSRMLS_CC) == FAILURE)
	{

		success = 0;
		/* if there was an error with the http request solr_make_request throws an exception by itself
		 * if it wasn't a curl connection error, throw exception (omars)
		 */
		HANDLE_SOLR_SERVER_ERROR(client,"query");

		/* SOLR_SHOW_CURL_WARNING; commented by: omars <omars@php.net> */
	}

	object_init_ex(return_value, solr_ce_SolrQueryResponse);

	solr_set_response_object_properties(solr_ce_SolrQueryResponse, return_value, client, request_url, success TSRMLS_CC);
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::addDocument(SolrInputDocument doc [, bool overwrite [, int commitWithin]])
   Adds a document to the Solr server. */
PHP_METHOD(SolrClient, addDocument)
{
	zval *solr_input_doc = NULL;
	zend_bool overwrite = 1;
	long int commitWithin = 0L;
	solr_document_t *doc_entry = NULL;
	solr_client_t *client = NULL;
	HashTable *document_fields;
	xmlNode *root_node = NULL;
	xmlDoc *doc_ptr = NULL;
	char *overwriteValue = NULL;
	int format = 1;
	int size   = 0;
	xmlChar *request_string = NULL;
	zend_bool success = 1;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O|bl", &solr_input_doc, solr_ce_SolrInputDocument, &overwrite, &commitWithin) == FAILURE) {

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
	overwriteValue = (overwrite)? "true" : "false";

	xmlNewProp(root_node, (xmlChar *) "overwrite", (xmlChar *) overwriteValue);

	if (commitWithin > 0L)
	{
		auto char commitWithinBuffer[32];

		memset(commitWithinBuffer, 0, sizeof(commitWithinBuffer));

		php_sprintf(commitWithinBuffer, "%ld", commitWithin);

		xmlNewProp(root_node, (xmlChar *) "commitWithin", (xmlChar *) commitWithinBuffer);
	}

	solr_add_doc_node(root_node, doc_entry TSRMLS_CC);

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

		/* if there was an error with the http request solr_make_request throws an exception by itself
		 * if it wasn't a curl connection error, throw exception (omars)
		 */
		HANDLE_SOLR_SERVER_ERROR(client,"update");

		/* SOLR_SHOW_CURL_WARNING; commented by: omars <omars@php.net> */
	}

	object_init_ex(return_value, solr_ce_SolrUpdateResponse);

	solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::addDocuments(array docs [, bool overwrite [, int commitWithin]])
   Adds an array of SolrInputDocuments to the Solr server. */
PHP_METHOD(SolrClient, addDocuments)
{
	zval *docs_array = NULL;
	zend_bool overwrite = 1;
	long int commitWithin = 0L;
	HashTable *solr_input_docs;
	size_t num_input_docs = 0;
	solr_client_t *client = NULL;
	solr_document_t **doc_entries = NULL;
	size_t curr_pos = 0U;
	xmlNode *root_node = NULL;
	xmlDoc *doc_ptr = NULL;
	xmlChar *overwriteValue = NULL;
	size_t pos = 0U;
	solr_document_t *current_doc_entry = NULL;
	int format = 1;
	int size = 0;
	zend_bool success = 1;
	xmlChar *request_string = NULL;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a|bl", &docs_array, &overwrite, &commitWithin) == FAILURE) {

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
		zval *solr_input_doc = NULL;
		solr_document_t *doc_entry = NULL;
		HashTable *document_fields;

		solr_input_doc = zend_hash_get_current_data(solr_input_docs);

		if (Z_TYPE_P(solr_input_doc) != IS_OBJECT || !instanceof_function(Z_OBJCE_P(solr_input_doc), solr_ce_SolrInputDocument TSRMLS_CC))
		{
			SOLR_FREE_DOC_ENTRIES(doc_entries);

			solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "SolrInputDocument number %u is not a valid SolrInputDocument instance", (curr_pos + 1U));

			return;
		}

		if (solr_fetch_document_entry((solr_input_doc), &doc_entry TSRMLS_CC) == FAILURE) {

			SOLR_FREE_DOC_ENTRIES(doc_entries);

			solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "SolrInputDocument number %u is not valid. Object not present in HashTable", (curr_pos + 1U));

			return;
		}

		document_fields = doc_entry->fields;

		/* SolrInputDocument must contain at least one field */
		if (0 == zend_hash_num_elements(document_fields)) {

			SOLR_FREE_DOC_ENTRIES(doc_entries);

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
	overwriteValue = (overwrite) ? (xmlChar *) "true" : (xmlChar *) "false";

	xmlNewProp(root_node, (xmlChar *) "overwrite", overwriteValue);

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
		solr_add_doc_node(root_node, current_doc_entry TSRMLS_CC);

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

		/* if there was an error with the http request solr_make_request throws an exception by itself
		 * if it wasn't a curl connection error, throw exception (omars)
		 */
		HANDLE_SOLR_SERVER_ERROR(client,"update");

		/* SOLR_SHOW_CURL_WARNING; commented by: omars <omars@php.net> */
	}

	object_init_ex(return_value, solr_ce_SolrUpdateResponse);

	solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::request(string request_string)
   Allows the user to send a manual XML update request */
PHP_METHOD(SolrClient, request)
{
	solr_char_t *request_string = NULL;
	COMPAT_ARG_SIZE_T request_length = 0;
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

		/* if there was an error with the http request solr_make_request throws an exception by itself
		 * if it wasn't a curl connection error, throw exception (omars)
		 */
		HANDLE_SOLR_SERVER_ERROR(client,"update");

		/* SOLR_SHOW_CURL_WARNING; commented by: omars <omars@php.net> */
	}

	object_init_ex(return_value, solr_ce_SolrUpdateResponse);

	solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::deleteById(string id)
   Allows the user to delete a document by id */
PHP_METHOD(SolrClient, deleteById)
{
	solr_char_t *id = NULL;
	COMPAT_ARG_SIZE_T id_length = 0L;
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

		/* if there was an error with the http request solr_make_request throws an exception by itself
		 * if it wasn't a curl connection error, throw exception (omars)
		 */
		HANDLE_SOLR_SERVER_ERROR(client,"update");

		/* SOLR_SHOW_CURL_WARNING; commented by: omars <omars@php.net> */
	}

	object_init_ex(return_value, solr_ce_SolrUpdateResponse);
	solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::request(array ids)
   Allows the user to delete a set of documents by ids. This should be an array of strings */
PHP_METHOD(SolrClient, deleteByIds)
{
	zval *ids_array = NULL;
	HashTable *doc_ids = NULL;
	size_t num_ids = 0;
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
		zval *id_zval = NULL;

		id_zval = zend_hash_get_current_data(doc_ids);

		if (Z_TYPE_P(id_zval) == IS_STRING && Z_STRLEN_P(id_zval))
		{
			xmlChar *escaped_id_value = xmlEncodeEntitiesReentrant(doc_ptr, (xmlChar *) Z_STRVAL_P(id_zval));
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

		/* if there was an error with the http request solr_make_request throws an exception by itself
		 * if it wasn't a curl connection error, throw exception (omars)
		 */
		HANDLE_SOLR_SERVER_ERROR(client,"update");
	}

	object_init_ex(return_value, solr_ce_SolrUpdateResponse);
	solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::deleteByQuery(string query)
   Allows the user to delete a set of documents matching the query */
PHP_METHOD(SolrClient, deleteByQuery)
{
	solr_char_t *query = NULL;
	COMPAT_ARG_SIZE_T query_length = 0L;
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

		/* if there was an error with the http request solr_make_request throws an exception by itself
		 * if it wasn't a curl connection error, throw exception (omars)
		 */
		HANDLE_SOLR_SERVER_ERROR(client,"update");

		/* SOLR_SHOW_CURL_WARNING; commented by: omars <omars@php.net> */
	}

	object_init_ex(return_value, solr_ce_SolrUpdateResponse);
	solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
}
/* }}} */

/* {{{ proto SolrQueryResponse SolrClient::getById(string id)
   Get Document By Id. Utilizes Solr Realtime Get (RTG) */
PHP_METHOD(SolrClient, getById)
{
    solr_client_t *client;
    solr_char_t *id;
    COMPAT_ARG_SIZE_T id_len = 0;
    solr_string_t query_string;
    int success = 1;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &id, &id_len) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");
        return;
    }

    if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");
        return;
    }
    /* Always reset the URLs before making any request */
    solr_client_init_urls(client);

    solr_string_init(&query_string);
    solr_string_appends(&query_string, "id=", sizeof("id=")-1);
    solr_string_appends(&query_string, id, id_len);

    solr_string_append_solr_string(&(client->handle.request_body.buffer), &query_string);
    if (solr_make_request(client, SOLR_REQUEST_GET TSRMLS_CC) == FAILURE)
    {
        /* if there was an error with the http request solr_make_request throws an exception by itself
         * if it wasn't a curl connection error, throw exception (omars)
         */
        HANDLE_SOLR_SERVER_ERROR(client,"get");
        success = 0;
    }

    object_init_ex(return_value, solr_ce_SolrQueryResponse);
    solr_set_response_object_properties(solr_ce_SolrQueryResponse, return_value, client, &(client->options.get_url), success TSRMLS_CC);
    solr_string_free(&query_string);
}
/* }}} */

/* {{{ proto SolrQueryResponse SolrClient::getByIds(array ids)
   Get Documents by their Ids. Utilizes Solr Realtime Get (RTG) */
PHP_METHOD(SolrClient, getByIds)
{
    solr_client_t *client;
    HashTable *ids = NULL;
    zval *ids_z = NULL;
    zend_bool invalid_param = 0;
    solr_string_t query_string;
    size_t current_position = 0;
    int success = 1;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &ids_z) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");
        return;
    }

    if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Internal Error: Cannot fetch client object");
        return;
    }
    ids = Z_ARRVAL_P(ids_z);
    if (ids->nNumOfElements < 1)
    {
        solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, 4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Invalid parameter: at least 1 ID is required. Passed an empty array.", current_position);
    }
    /* Always reset the URLs before making any request */
    solr_client_init_urls(client);

    solr_string_init(&query_string);
    solr_string_appends(&query_string, "ids=", sizeof("ids=")-1);
    SOLR_HASHTABLE_FOR_LOOP(ids)
    {
        zval *id_zv = NULL;
        id_zv = zend_hash_get_current_data(ids);
        if (Z_TYPE_P(id_zv) == IS_STRING && Z_STRLEN_P(id_zv)) {
            solr_string_appends(&query_string, Z_STRVAL_P(id_zv), Z_STRLEN_P(id_zv));
            solr_string_appendc(&query_string, ',');
        } else {
            invalid_param = 1;
            goto solr_getbyids_exit;
        }
        current_position++;
    }



solr_getbyids_exit:
    if (invalid_param) {
        solr_string_free(&query_string);
        solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, 4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "Invalid id at position %ld", current_position);
        return;
    }
    solr_string_remove_last_char(&query_string);

    solr_string_append_solr_string(&(client->handle.request_body.buffer), &query_string);
    if (solr_make_request(client, SOLR_REQUEST_GET TSRMLS_CC) == FAILURE)
    {
        /* if there was an error with the http request solr_make_request throws an exception by itself
         * if it wasn't a curl connection error, throw exception (omars)
         */

        HANDLE_SOLR_SERVER_ERROR(client,"get");
        success = 0;
    }

    object_init_ex(return_value, solr_ce_SolrQueryResponse);
    solr_set_response_object_properties(solr_ce_SolrQueryResponse, return_value, client, &(client->options.get_url), success TSRMLS_CC);

    solr_string_set_ex(&(client->handle.request_body.buffer),(solr_char_t *)0x00, 0);
    solr_string_free(&query_string);
}
/* }}} */

/* {{{ proto void SolrClient::setResponseWriter(string responseWriter)
   Allows the user to specify which response writer to use */
PHP_METHOD(SolrClient, setResponseWriter)
{
	solr_char_t *wt = NULL;
	COMPAT_ARG_SIZE_T wt_length = 0L;
	solr_client_t *client = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &wt, &wt_length) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		return;
	}

	if (!wt_length)
	{
		solr_throw_exception_ex(solr_ce_SolrIllegalArgumentException, SOLR_ERROR_4000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, "The response writer is not a valid string");

		return;
	}

	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client from HashTable");

		return;
	}

	if (solr_is_supported_response_writer((const solr_char_t *) wt, wt_length)) {

		/* The response writer used to present the response from Solr */
		solr_string_set(&(client->options.response_writer), (solr_char_t *) wt, wt_length);

	} else {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unsupported response writer %s. This value will be ignored", wt);
	}
}
/* }}} */


/* {{{ proto SolrUpdateResponse SolrClient::deleteByQueries(array queries)
   Allows the user to delete a set of documents matching the queries specified */
PHP_METHOD(SolrClient, deleteByQueries)
{
	zval *queries_array = NULL;
	HashTable *doc_queries = NULL;
	size_t num_queries = 0;
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
		zval *query_zval = NULL;

		query_zval = zend_hash_get_current_data(doc_queries);

		if (Z_TYPE_P(query_zval) == IS_STRING && Z_STRLEN_P(query_zval))
		{
			xmlChar *escaped_query_value = xmlEncodeEntitiesReentrant(doc_ptr, (xmlChar *) Z_STRVAL_P(query_zval));

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

		/* if there was an error with the http request solr_make_request throws an exception by itself
		 * if it wasn't a curl connection error, throw exception (omars)
		 */
		HANDLE_SOLR_SERVER_ERROR(client,"update");

		/* SOLR_SHOW_CURL_WARNING; commented by: omars <omars@php.net> */
	}

	object_init_ex(return_value, solr_ce_SolrUpdateResponse);
	solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::optimize([string maxSegments [, bool softCommit [, bool waitSearcher]])
   Sends an optimize XML request to the server. */
PHP_METHOD(SolrClient, optimize)
{
	zend_bool softCommit = 0, waitSearcher = 1;
	char *maxSegments = "1";
	int maxSegmentsLen = sizeof("1")-1;
	char *softCommitValue, *waitSearcherValue;
	xmlNode *root_node = NULL;
	xmlDoc *doc_ptr = NULL;
	solr_client_t *client = NULL;
	int format = 1;
	int size = 0;
	xmlChar *request_string = NULL;
	zend_bool success = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|sbb", &maxSegments, &maxSegmentsLen, &softCommit, &waitSearcher) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		return;
	}

	softCommitValue = (softCommit)? "true" : "false";
	waitSearcherValue = (waitSearcher)? "true" : "false";

	doc_ptr = solr_xml_create_xml_doc((xmlChar *) "optimize", &root_node);

	xmlNewProp(root_node, (xmlChar *) "maxSegments", (xmlChar *) maxSegments);
	xmlNewProp(root_node, (xmlChar *) "softCommit", (xmlChar *) softCommitValue);
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

		/* if there was an error with the http request solr_make_request throws an exception by itself
		 * if it wasn't a curl connection error, throw exception (omars)
		 */
		HANDLE_SOLR_SERVER_ERROR(client,"update");

		/* SOLR_SHOW_CURL_WARNING; commented by: omars <omars@php.net> */
	}

	object_init_ex(return_value, solr_ce_SolrUpdateResponse);
	solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
}
/* }}} */

/* {{{ proto SolrUpdateResponse SolrClient::commit( [bool softCommit [, bool waitSearcher [, bool expungeDeletes]]])
   Sends a commit XML request to the server. */
PHP_METHOD(SolrClient, commit)
{
	zend_bool softCommit = 0, waitSearcher = 1, expungeDeletes = 0;
	char *softCommitValue, *waitSearcherValue, *expungeDeletesValue;
	xmlNode *root_node = NULL;
	xmlDoc *doc_ptr = NULL;
	solr_client_t *client = NULL;
	int format = 1;
	int size = 0;
	xmlChar *request_string = NULL;
	zend_bool success = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|bbb", &softCommit, &waitSearcher, &expungeDeletes) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter");

		return;
	}

	softCommitValue = (softCommit)? "true" : "false";
	waitSearcherValue = (waitSearcher)? "true" : "false";
	expungeDeletesValue = (expungeDeletes)? "true": "false";

	doc_ptr = solr_xml_create_xml_doc((xmlChar *) "commit", &root_node);

	xmlNewProp(root_node, (xmlChar *) "softCommit", (xmlChar *) softCommitValue);
	xmlNewProp(root_node, (xmlChar *) "waitSearcher", (xmlChar *) waitSearcherValue);
	xmlNewProp(root_node, (xmlChar *) "expungeDeletes", (xmlChar *) expungeDeletesValue);

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

		/* if there was an error with the http request solr_make_request throws an exception by itself
		 * if it wasn't a curl connection error, throw exception (omars)
		 */
		HANDLE_SOLR_SERVER_ERROR(client,"update");

		/* SOLR_SHOW_CURL_WARNING; commented by: omars <omars@php.net> */
	}

	object_init_ex(return_value, solr_ce_SolrUpdateResponse);
	solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
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

		/* if there was an error with the http request solr_make_request throws an exception by itself
		 * if it wasn't a curl connection error, throw exception (omars)
		 */
		HANDLE_SOLR_SERVER_ERROR(client,"update");

		/* SOLR_SHOW_CURL_WARNING; commented by: omars <omars@php.net> */
	}

	object_init_ex(return_value, solr_ce_SolrUpdateResponse);
	solr_set_response_object_properties(solr_ce_SolrUpdateResponse, return_value, client, &(client->options.update_url), success TSRMLS_CC);
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

		/* if there was an error with the http request solr_make_request throws an exception by itself
		 * if it wasn't a curl connection error, throw exception (omars)
		 */
		HANDLE_SOLR_SERVER_ERROR(client,"ping");

		/* SOLR_SHOW_CURL_WARNING; commented by: omars <omars@php.net> */
	}

	object_init_ex(return_value, solr_ce_SolrPingResponse);
	solr_set_response_object_properties(solr_ce_SolrPingResponse, return_value, client, &(client->options.ping_url), success TSRMLS_CC);
}
/* }}} */

/* {{{ proto SolrGenericResponse SolrClient::threads()
   Sends a request to get info about threads. */
PHP_METHOD(SolrClient, threads)
{
	zend_bool success = 1;
	solr_client_t *client = NULL;

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
		success = 0;
		/* if there was an error with the http request solr_make_request throws an exception by itself
		 * if it wasn't a curl connection error, throw exception (omars)
		 */
		HANDLE_SOLR_SERVER_ERROR(client,"threads");

		/* SOLR_SHOW_CURL_WARNING; commented by: omars <omars@php.net> */
	}

	object_init_ex(return_value, solr_ce_SolrGenericResponse);
	solr_set_response_object_properties(solr_ce_SolrGenericResponse, return_value, client, &(client->options.thread_url), success TSRMLS_CC);
}
/* }}} */

/* {{{ proto SolrGenericResponse SolrClient::info()
   Sends a request to get system info. */
PHP_METHOD(SolrClient, system)
{
	zend_bool success = 1;
	solr_client_t *client = NULL;

	/* Retrieve the client entry */
	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client");

		return;
	}

	/* Always reset the URLs before making any request */
	solr_client_init_urls(client);

	/* Make the HTTP request to the Solr instance */
	if (solr_make_request(client, SOLR_REQUEST_SYSTEM TSRMLS_CC) == FAILURE)
	{
		success = 0;
		/* if there was an error with the http request solr_make_request throws an exception by itself
		 * if it wasn't a curl connection error, throw exception (omars)
		 */
		HANDLE_SOLR_SERVER_ERROR(client,"system");

		/* SOLR_SHOW_CURL_WARNING; commented by: omars <omars@php.net> */
	}

	object_init_ex(return_value, solr_ce_SolrGenericResponse);
	solr_set_response_object_properties(solr_ce_SolrGenericResponse, return_value, client, &(client->options.system_url), success TSRMLS_CC);
}
/* }}} */

/* {{{ proto array SolrClient::getOptions()
   Returns all the options for this client. */
PHP_METHOD(SolrClient, getOptions)
{
	solr_client_t *client = NULL;

	solr_client_options_t *options = NULL;

	/* Retrieve the client entry */
	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client");

		return;
	}

	options = &(client->options);

	array_init(return_value);

	add_assoc_long(return_value, "timeout", options->timeout);
	add_assoc_bool(return_value, "secure", (int) options->secure);

	add_assoc_stringl(return_value, "hostname", options->hostname.str, options->hostname.len);
	add_assoc_stringl(return_value, "wt", options->response_writer.str, options->response_writer.len);
	add_assoc_long(return_value, "port", options->host_port);

	add_assoc_stringl(return_value, "proxy_host", options->proxy_hostname.str, options->proxy_hostname.len);
	add_assoc_long(return_value, "proxy_port", options->proxy_port);


	add_assoc_stringl(return_value, "path", options->path.str, options->path.len);

	add_assoc_stringl(return_value, "http_auth", options->http_auth_credentials.str, options->http_auth_credentials.len);
	add_assoc_stringl(return_value, "proxy_auth", options->proxy_auth_credentials.str, options->proxy_auth_credentials.len);

	add_assoc_bool(return_value, "ssl_verify_peer", (int) options->ssl_verify_peer);
	add_assoc_long(return_value, "ssl_verify_host", options->ssl_verify_host);

	add_assoc_stringl(return_value, "ssl_cert", options->ssl_cert.str, options->ssl_cert.len);
	add_assoc_stringl(return_value, "ssl_key", options->ssl_key.str, options->ssl_key.len);
	add_assoc_stringl(return_value, "ssl_keypassword", options->ssl_keypassword.str, options->ssl_keypassword.len);
	add_assoc_stringl(return_value, "ssl_cainfo", options->ssl_cainfo.str, options->ssl_cainfo.len);
	add_assoc_stringl(return_value, "ssl_capath", options->ssl_capath.str, options->ssl_capath.len);
}
/* }}} */


/* {{{ proto string SolrClient::getDebug()
   Returns all debug data captured in the process of making the request. */
PHP_METHOD(SolrClient, getDebug)
{
	solr_client_t *client = NULL;

	solr_curl_t *handle = NULL;

	/* Retrieve the client entry */
	if (solr_fetch_client_entry(getThis(), &client TSRMLS_CC) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to retrieve client");

		return;
	}

	handle = &(client->handle);

	if (!handle->debug_data_buffer.len)
	{
		RETURN_NULL();
	}

	RETVAL_STRINGL(handle->debug_data_buffer.str, handle->debug_data_buffer.len);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

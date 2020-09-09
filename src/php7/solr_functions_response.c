/*
   +----------------------------------------------------------------------+
   | Copyright (c) The PHP Group                                          |
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

#include "php_solr.h"

/* Used to set the properties of the SolrResponse instance after a call to the server */

/* {{{ PHP_SOLR_API void solr_set_response_object_properties(zend_class_entry *scope, zval *response_object, const solr_client_t *client, const solr_string_t *request_url, zend_bool success) */
PHP_SOLR_API void solr_set_response_object_properties(zend_class_entry *scope, zval *response_object, const solr_client_t *client, const solr_string_t *request_url, zend_bool success)
{
	const solr_curl_t *handle = &(client->handle);

	const solr_string_t *raw_request_headers = &(handle->request_header.buffer);
	const solr_string_t *raw_request = &(handle->request_body_debug.buffer);
	const solr_string_t *raw_response_headers = &(handle->response_header.buffer);
	const solr_string_t *raw_response = &(handle->response_body.buffer);
	const solr_string_t *response_writer = &(client->options.response_writer);

	long int http_status = handle->response_header.response_code;

	zend_update_property_long(scope, OBJ_FOR_PROP(response_object), "http_status", sizeof("http_status")-1, http_status);

	zend_update_property_bool(scope, OBJ_FOR_PROP(response_object), "success", sizeof("success")-1, success);

	if (response_writer->str)
	{
		zend_update_property_stringl(scope, OBJ_FOR_PROP(response_object), "response_writer", sizeof("response_writer")-1, (char *)response_writer->str, response_writer->len);
	}

	if (request_url->str)
	{
		zend_update_property_stringl(scope, OBJ_FOR_PROP(response_object), "http_request_url", sizeof("http_request_url")-1, (char *)request_url->str, request_url->len);
	}

	if (raw_request_headers->str)
	{
		zend_update_property_stringl(scope, OBJ_FOR_PROP(response_object), "http_raw_request_headers", sizeof("http_raw_request_headers")-1, (char *)raw_request_headers->str, raw_request_headers->len);
	}

	if (raw_request->str)
	{
		zend_update_property_stringl(scope, OBJ_FOR_PROP(response_object), "http_raw_request", sizeof("http_raw_request")-1, (char *)raw_request->str, raw_request->len);
	}

	if (raw_response_headers->str)
	{
		zend_update_property_stringl(scope, OBJ_FOR_PROP(response_object), "http_raw_response_headers", sizeof("http_raw_response_headers")-1, (char *)raw_response_headers->str, raw_response_headers->len);
	}

	if (raw_response->str)
	{
		zend_update_property_stringl(scope, OBJ_FOR_PROP(response_object), "http_raw_response", sizeof("http_raw_response")-1, (char *)raw_response->str, raw_response->len);
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

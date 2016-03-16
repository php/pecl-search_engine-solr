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

/* {{{ Macro for extracting property values using string constants */
#define solr_read_response_object_property(objptr, name, silent, rv) zend_read_property(Z_OBJCE_P(objptr), objptr, name, sizeof(name)-1, silent, rv)
/* }}} */

/* {{{ proto int SolrResponse::getHttpStatus(void)
   Returns the value of the http_status property. */
PHP_METHOD(SolrResponse, getHttpStatus)
{
	zend_bool silent = 1;
	zval rv;
	zval *objptr = getThis();
	zval *http_status = NULL;

	http_status = solr_read_response_object_property(objptr, "http_status", silent, &rv);

	RETURN_LONG(Z_LVAL_P(http_status));
}
/* }}} */

/* {{{ proto string SolrResponse::getHttpStatusMessage(void)
   Returns the http_status_message property. */
PHP_METHOD(SolrResponse, getHttpStatusMessage)
{
	zend_bool silent = 1;
	zval rv;
	zval *objptr = getThis();
	zval *http_status_message = NULL;

	http_status_message = solr_read_response_object_property(objptr, "http_status_message", silent, &rv);

	RETURN_STRINGL(Z_STRVAL_P(http_status_message), Z_STRLEN_P(http_status_message));
}
/* }}} */

/* {{{ proto bool SolrResponse::success(void)
   Returns whether the request was successful or not. */
PHP_METHOD(SolrResponse, success)
{
	zend_bool silent = 1;
	zval rv;
	zval *objptr = getThis();
	zval *success = NULL;

	success = solr_read_response_object_property(objptr, "success", silent, &rv);
	RETURN_ZVAL(success, 0, 0);
}
/* }}} */

/* {{{ proto string SolrResponse::getRequestUrl(void)
   Returns the URL used for the request. */
PHP_METHOD(SolrResponse, getRequestUrl)
{
	zend_bool silent = 1;
	zval rv;
	zval *objptr = getThis();
	zval *prop = NULL;

	prop = solr_read_response_object_property(objptr, "http_request_url", silent, &rv);

	RETURN_STRINGL(Z_STRVAL_P(prop), Z_STRLEN_P(prop));
}
/* }}} */

/* {{{ proto string SolrResponse::getRawRequestHeaders(void)
   Returns the raw http request headers sent to the server. */
PHP_METHOD(SolrResponse, getRawRequestHeaders)
{
	zend_bool silent = 1;
	zval rv;
	zval *objptr = getThis();
	zval *prop = NULL;

	prop = solr_read_response_object_property(objptr, "http_raw_request_headers", silent, &rv);

	RETURN_STRINGL(Z_STRVAL_P(prop), Z_STRLEN_P(prop));
}
/* }}} */

/* {{{ proto string SolrResponse::getRawRequest(void)
   Returns the raw http request sent to the server. */
PHP_METHOD(SolrResponse, getRawRequest)
{
	zend_bool silent = 1;
	zval rv;
	zval *objptr = getThis();
	zval *prop = NULL;

	prop = solr_read_response_object_property(objptr, "http_raw_request", silent, &rv);

	RETURN_STRINGL(Z_STRVAL_P(prop), Z_STRLEN_P(prop));
}
/* }}} */

/* {{{ proto string SolrResponse::getRawResponseHeaders(void)
   Returns the raw http response headers from the server. */
PHP_METHOD(SolrResponse, getRawResponseHeaders)
{
	zend_bool silent = 1;
	zval rv;
	zval *objptr = getThis();
	zval *prop = NULL;

	prop = solr_read_response_object_property(objptr, "http_raw_response_headers", silent, &rv);

	RETURN_STRINGL(Z_STRVAL_P(prop), Z_STRLEN_P(prop));
}
/* }}} */

/* {{{ proto string SolrResponse::getRawResponse(void)
   Returns the raw http response from the server. */
PHP_METHOD(SolrResponse, getRawResponse)
{
	zend_bool silent = 1;
	zval rv;
	zval *objptr = getThis();
	zval *prop = NULL;

	prop = solr_read_response_object_property(objptr, "http_raw_response", silent, &rv);

	if (Z_STRLEN_P(prop))
	{
		RETURN_STRINGL(Z_STRVAL_P(prop), Z_STRLEN_P(prop));
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto string SolrResponse::getDigestedResponse(void)
   Returns the serialized object string derived from the XML response. */
PHP_METHOD(SolrResponse, getDigestedResponse)
{
	zend_bool silent = 0;
	zval rv;
	zval *objptr = getThis();
	zval *prop = NULL;

	prop = solr_read_response_object_property(objptr, "http_digested_response", silent, &rv);

	if (Z_STRLEN_P(prop))
	{
		RETURN_STRINGL(Z_STRVAL_P(prop), Z_STRLEN_P(prop));
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto string SolrReponse::setParseMode([bool parse_mode])
   Sets the parsing mode. This determines whether documents will be parsed as SolrObjects or SolrDocuments. */
PHP_METHOD(SolrResponse, setParseMode)
{
	long int parse_mode = 0L;
	zval *objptr = getThis();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &parse_mode) == FAILURE) {

		RETURN_FALSE;
	}

	parse_mode = ((parse_mode < 0L) ? 0L : ((parse_mode > 1L) ? 1L : parse_mode));

	zend_update_property_long(Z_OBJCE_P(objptr), objptr, "parser_mode", sizeof("parser_mode")-1, parse_mode TSRMLS_CC);

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto SolrObject SolrResponse::getResponse(void)
   Returns the response object from the server. */
PHP_METHOD(SolrResponse, getResponse)
{
    solr_response_get_response_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU,0);
}
/* }}} */

/* {{{ proto array SolrResponse::getArrayResponse(void)
   Returns the response array from the server. */
PHP_METHOD(SolrResponse, getArrayResponse)
{
    solr_response_get_response_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU,1);
}
/* }}} */

/**
 * Digest solr server raw response
 * and return SolrObject or array
 */
PHP_SOLR_API void solr_response_get_response_impl(
        INTERNAL_FUNCTION_PARAMETERS,
        int return_array)
{
    zend_bool silent = 0;
    zval *objptr = getThis();
    zval rv;
    zval *response_writer = solr_read_response_object_property(objptr, "response_writer", silent, &rv);
    zval *raw_response = solr_read_response_object_property(objptr, "http_raw_response", silent, &rv);
    zval *success = solr_read_response_object_property(objptr, "success", silent, &rv);
    zval *parser_mode = solr_read_response_object_property(objptr, "parser_mode", silent, &rv);

    if (Z_TYPE_P(success) == IS_TRUE && Z_STRLEN_P(raw_response))
    {
        solr_string_t buffer;
        php_unserialize_data_t var_hash;
        const unsigned char *raw_resp;
        size_t raw_res_length;
        const unsigned char *str_end;
        int successful = 1;

        memset(&buffer, 0, sizeof(solr_string_t));

        if (Z_STRLEN_P(response_writer))
        {
            if (0 == strcmp(Z_STRVAL_P(response_writer), SOLR_XML_RESPONSE_WRITER))
            {
                /* SOLR_XML_RESPONSE_WRITER */

                /* Convert from XML serialization to PHP serialization format */
                solr_encode_generic_xml_response(&buffer, Z_STRVAL_P(raw_response), Z_STRLEN_P(raw_response), Z_LVAL_P(parser_mode) TSRMLS_CC);
                if(return_array)
                {
                    solr_sobject_to_sarray(&buffer TSRMLS_CC);
                }
            } else if (0 == strcmp(Z_STRVAL_P(response_writer), SOLR_PHP_NATIVE_RESPONSE_WRITER) || 0 == strcmp(Z_STRVAL_P(response_writer), SOLR_PHP_SERIALIZED_RESPONSE_WRITER)) {

                /* SOLR_PHP_NATIVE_RESPONSE_WRITER */

                /* Response string is already in Native PHP serialization format */
                solr_string_set(&buffer, Z_STRVAL_P(raw_response), Z_STRLEN_P(raw_response));

                if(!return_array)
                {
                    solr_sarray_to_sobject(&buffer TSRMLS_CC);
                }

            } else if (0 == strcmp(Z_STRVAL_P(response_writer), SOLR_JSON_RESPONSE_WRITER)) {

                int json_translation_result = solr_json_to_php_native(&buffer, Z_STRVAL_P(raw_response), Z_STRLEN_P(raw_response) TSRMLS_CC);

                /* SOLR_JSON_RESPONSE_WRITER */

                /* Convert from JSON serialization to PHP serialization format */
                if (json_translation_result > 0)
                {
                    solr_throw_exception_ex(solr_ce_SolrException, SOLR_ERROR_1000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, solr_get_json_error_msg(json_translation_result));

                    php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error in JSON->PHP conversion. JSON Error Code %d", json_translation_result);
                }

                if(!return_array)
                {
                    solr_sarray_to_sobject(&buffer TSRMLS_CC);
                }
            }
        }

        if (buffer.len)
        {
            zend_update_property_stringl(Z_OBJCE_P(objptr), objptr, "http_digested_response", sizeof("http_digested_response")-1, buffer.str, buffer.len TSRMLS_CC);
        }

        memset(&var_hash, 0, sizeof(php_unserialize_data_t));

        PHP_VAR_UNSERIALIZE_INIT(var_hash);

        raw_resp = (unsigned char *) buffer.str;
        raw_res_length = buffer.len;
        str_end = (unsigned char *) (raw_resp + raw_res_length);

        if (!php_var_unserialize(return_value, &raw_resp, str_end, &var_hash TSRMLS_CC))
        {
            successful = 0;

            solr_throw_exception_ex(solr_ce_SolrException, SOLR_ERROR_1000 TSRMLS_CC, SOLR_FILE_LINE_FUNC, SOLR_ERROR_1000_MSG);

            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error unserializing raw response.");
        }

        PHP_VAR_UNSERIALIZE_DESTROY(var_hash);

        solr_string_free(&buffer);

        if (successful && !return_array)
        {
            /* Overriding the default object handlers */
            Z_OBJ_HT_P(return_value) = &solr_object_handlers;
        }

        return ;
    }

    RETURN_NULL();
}

/* {{{ proto string SolrPingResponse::getResponse(void)
  Ping responses are always empty. Returns null. */
PHP_METHOD(SolrPingResponse, getResponse)
{
	/* Ping responses are not serialized */
	RETURN_NULL();
}
/* }}} */

/* {{{ proto SolrPingResponse::__construct(void)
   Constructor */
PHP_METHOD(SolrPingResponse, __construct)
{

}
/* }}} */

/* {{{ proto SolrPingResponse::__destruct(void)
   Destructor */
PHP_METHOD(SolrPingResponse, __destruct)
{

}
/* }}} */

/* {{{ proto SolrQueryResponse::__construct(void)
   Constructor */
PHP_METHOD(SolrQueryResponse, __construct)
{

}
/* }}} */

/* {{{ proto SolrQueryResponse::__destruct(void)
   Destructor */
PHP_METHOD(SolrQueryResponse, __destruct)
{

}
/* }}} */

/* {{{ proto SolrUpdateResponse::__construct(void)
   Constructor */
PHP_METHOD(SolrUpdateResponse, __construct)
{

}
/* }}} */

/* {{{ proto SolrUpdateResponse::__destruct(void)
   Destructor */
PHP_METHOD(SolrUpdateResponse, __destruct)
{

}
/* }}} */

/* {{{ proto SolrGenericResponse::__construct(void)
   Constructor */
PHP_METHOD(SolrGenericResponse, __construct)
{

}
/* }}} */

/* {{{ proto SolrGenericResponse::__destruct(void)
   Destructor */
PHP_METHOD(SolrGenericResponse, __destruct)
{

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

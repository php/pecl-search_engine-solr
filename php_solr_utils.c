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

/* {{{ proto string SolrUtils::escapeQueryChars(string unescaped)
   Escapes the lucene string */
PHP_METHOD(SolrUtils, escapeQueryChars)
{
	solr_char_t *unescaped = NULL;

	long int unescaped_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &unescaped, &unescaped_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (!unescaped_length) {

		RETURN_NULL();
	}

	solr_string_t sbuilder;

	memset(&sbuilder, 0, sizeof(solr_string_t));

	solr_escape_query_chars(&sbuilder, unescaped, unescaped_length);

	RETVAL_STRINGL(sbuilder.str, sbuilder.len, 1);

	solr_string_free(&sbuilder);
}
/* }}} */

/* {{{  proto string SolrUtils::queryPhrase(string unescaped)
  Prepares a phrase from an unescaped lucene string. */
PHP_METHOD(SolrUtils, queryPhrase)
{
	solr_char_t *unescaped = NULL;

	long int unescaped_length = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &unescaped, &unescaped_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (!unescaped_length) {

		RETURN_NULL();
	}

	solr_string_t sbuilder;

	memset(&sbuilder, 0, sizeof(solr_string_t));

	solr_string_appendc(&sbuilder, '"');

	solr_escape_query_chars(&sbuilder, unescaped, unescaped_length);

	solr_string_appendc(&sbuilder, '"');

	RETVAL_STRINGL(sbuilder.str, sbuilder.len, 1);

	solr_string_free(&sbuilder);
}
/* }}} */

/* {{{  proto string SolrUtils::digestXMLResponse(string xml_response [, int parse_mode])
   Digests the xml response into a php serialize string. */
PHP_METHOD(SolrUtils, digestXmlResponse)
{
	solr_char_t *xmlresponse = NULL;

	int xmlresponse_len = 0;

	long int parse_mode = 0L;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &xmlresponse, &xmlresponse_len, &parse_mode) == FAILURE) {

		RETURN_FALSE;
	}

	parse_mode = ((parse_mode < 0L) ? 0L : ((parse_mode > 1L) ? 1L : parse_mode));

	solr_string_t sbuilder;

	memset(&sbuilder, 0, sizeof(solr_string_t));

	solr_encode_generic_xml_response(&sbuilder, xmlresponse, xmlresponse_len, parse_mode TSRMLS_CC);

	php_unserialize_data_t var_hash;

	memset(&var_hash, 0, sizeof(php_unserialize_data_t));

	PHP_VAR_UNSERIALIZE_INIT(var_hash);

	const unsigned char *raw_resp = (unsigned char *) sbuilder.str;
	size_t raw_res_length         = sbuilder.len;
	const unsigned char  *str_end = raw_resp + raw_res_length;

	int successful = 1;

	if (!php_var_unserialize(&return_value, &raw_resp, str_end, &var_hash TSRMLS_CC))
	{
		zend_throw_exception_ex(solr_ce_SolrException, SOLR_ERROR_1000 TSRMLS_CC, SOLR_ERROR_1000_MSG);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error unserializing raw response.");

		successful = 0;
	}

	PHP_VAR_UNSERIALIZE_DESTROY(var_hash);

	solr_string_free(&sbuilder);

	if (successful)
	{
		/* Overriding the default object handlers */
		Z_OBJ_HT_P(return_value) = &solr_object_handlers;
	}
}
/* }}} */

/* {{{ proto string SolrUtils::getSolrVersion(void)
   Returns the current extension version */
PHP_METHOD(SolrUtils, getSolrVersion)
{
	RETURN_STRINGL(PHP_SOLR_DOTTED_VERSION, sizeof(PHP_SOLR_DOTTED_VERSION)-1, 1);
}
/* }}} */

/* {{{ proto array SolrUtils::getSolrStats(void)
   Returns the number of active documents, clients and SolrParam objects in the current thread. */
PHP_METHOD(SolrUtils, getSolrStats)
{
	array_init(return_value);

	int document_count = zend_hash_num_elements(SOLR_GLOBAL(documents));
	int client_count = zend_hash_num_elements(SOLR_GLOBAL(clients));
	int params_count = zend_hash_num_elements(SOLR_GLOBAL(params));

	add_assoc_long(return_value, "document_count", document_count);
	add_assoc_long(return_value, "client_count", client_count);
	add_assoc_long(return_value, "params_count", params_count);
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


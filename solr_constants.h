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

#ifndef SOLR_CONSTANTS_H
#define SOLR_CONSTANTS_H

#include "php_solr_version.h"

#define SOLR_SPACE_STRING " "

/* {{{ Constants for the SolrClient with*/
#define SOLR_DEFAULT_UPDATE_SERVLET  "update"
#define SOLR_DEFAULT_SEARCH_SERVLET  "select"
#define SOLR_DEFAULT_THREADS_SERVLET "admin/threads"
#define SOLR_DEFAULT_PING_SERVLET    "admin/ping"
#define SOLR_DEFAULT_TERMS_SERVLET   "terms"
#define SOLR_DEFAULT_SYSTEM_SERVLET    "admin/system"
#define SOLR_DEFAULT_GET_SERVLET     "get"

#define SOLR_PHP_SERIALIZED_RESPONSE_WRITER    "phps"
#define SOLR_PHP_NATIVE_RESPONSE_WRITER        "phpnative"
#define SOLR_XML_RESPONSE_WRITER               "xml"
#define SOLR_JSON_RESPONSE_WRITER              "json"

#define SOLR_REQUEST_DEFAULT_HOST "localhost"
#define SOLR_REQUEST_DEFAULT_PATH "solr"
#define SOLR_REQUEST_DEFAULT_QS_DELIMITER "&"
#define SOLR_REQUEST_DEFAULT_PORT 8983L

#define SOLR_CURL_MAX_WRITE_SIZE CURL_MAX_WRITE_SIZE
#define SOLR_CURL_OPTIONS_LENGTH 512
/* }}} */

/* {{{ Names of Objects */
#define PHP_SOLR_OBJECT_CLASSNAME      	   	   "SolrObject"
#define PHP_SOLR_DOCUMENT_CLASSNAME      	   "SolrDocument"
#define PHP_SOLR_DOCUMENT_FIELD_CLASSNAME      "SolrDocumentField"
#define PHP_SOLR_INPUT_DOCUMENT_CLASSNAME      "SolrInputDocument"
#define PHP_SOLR_CLIENT_CLASSNAME              "SolrClient"
#define PHP_SOLR_PARAMS_CLASSNAME              "SolrParams"
#define PHP_SOLR_QUERY_CLASSNAME               "SolrQuery"
#define PHP_SOLR_COLLAPSE_FUNCTION_CLASSNAME   "SolrCollapseFunction"
#define PHP_SOLR_MODIFIABLE_PARAMS_CLASSNAME   "SolrModifiableParams"
#define PHP_SOLR_RESPONSE_CLASSNAME   		   "SolrResponse"
#define PHP_SOLR_QUERY_RESPONSE_CLASSNAME      "SolrQueryResponse"
#define PHP_SOLR_UPDATE_RESPONSE_CLASSNAME     "SolrUpdateResponse"
#define PHP_SOLR_PING_RESPONSE_CLASSNAME   	   "SolrPingResponse"
#define PHP_SOLR_GENERIC_RESPONSE_CLASSNAME    "SolrGenericResponse"
#define PHP_SOLR_UTILS_CLASSNAME           	   "SolrUtils"

#define PHP_SOLR_EXCEPTION_CLASSNAME           "SolrException"
#define PHP_SOLR_ILLEGAL_OPERATION_EXCEPTION_CLASSNAME	"SolrIllegalOperationException"
#define PHP_SOLR_ILLEGAL_ARGUMENT_EXCEPTION_CLASSNAME	"SolrIllegalArgumentException"
#define PHP_SOLR_CLIENT_EXCEPTION_CLASSNAME     "SolrClientException"
#define PHP_SOLR_SERVER_EXCEPTION_CLASSNAME     "SolrServerException"
#define PHP_SOLR_MISSING_MANDATORY_PARAMETER_EXCEPTION_CLASSNAME     "SolrMissingMandatoryParameterException"
/* }}} */

/* {{{ Informational constants */
#define PHP_SOLR_EXTENSION_NAME   "solr"
#define PHP_CURL_EXTENSION_NAME   "curl"
#define PHP_LIBXML_EXTENSION_NAME "libxml"
#define PHP_JSON_EXTENSION_NAME   "json"

/* }}} */

/* {{{ Property names */
#define SOLR_INDEX_PROPERTY_NAME 		"_hashtable_index"
#define SOLR_FIELD_NAME_PROPERTY_NAME   "name"
#define SOLR_FIELD_BOOST_PROPERTY_NAME  "boost"
#define SOLR_FIELD_VALUES_PROPERTY_NAME "values"

#define SOLR_SOURCELINE_NO_PROPERTY_NAME "sourceline"
#define SOLR_SOURCEFILE_PROPERTY_NAME "sourcefile"
#define SOLR_ZIFNAME_PROPERTY_NAME "zif_name"

#define SOLR_DISMAX_DEFAULT_PARSER "edismax"

#ifdef PHP_WIN32
#define __func__ __FUNCTION__
#endif

#define SOLR_FILE_LINE_FUNC __FILE__, __LINE__, __func__
/* }}} */

/* {{{ Constants for Method/Function arguments and return styles */
#define SOLR_ARG_PASS_BY_REF_FALSE 0
#define SOLR_ARG_PASS_BY_REF_TRUE  1

#define SOLR_ARG_PASS_REMAINING_BY_REF_FALSE 0
#define SOLR_ARG_PASS_REMAINING_BY_REF_TRUE  1

#define SOLR_ARG_ALLOW_NULL_FALSE 0
#define SOLR_ARG_ALLOW_NULL_TRUE  1

#define SOLR_METHOD_RETURN_REFERENCE_FALSE 0
#define SOLR_METHOD_RETURN_REFERENCE_TRUE  1
/* }}} */

/* {{{ Constants for Sorting SolrDocument Fields */
#define SOLR_SORT_ASC  1
#define SOLR_SORT_DESC 2

#define SOLR_SORT_FIELD_NAME 1
#define SOLR_SORT_FIELD_VALUE_COUNT 2
#define SOLR_SORT_FIELD_BOOST_VALUE 4
/* }}} */

/* {{{ Constants for document encoding formats */
#define SOLR_XML_ENCODE_OBJ 0L
#define SOLR_XML_ENCODE_DOC 1L
/* }}} */

/**
 * Setting this to 8 gets rid of the extra while loops in _zend_hash_init()
 *
 * _zend_hash_init loops 3 times to increase the value of the size to 8
 */
#define SOLR_INITIAL_HASH_TABLE_SIZE (1<<3)

/* {{{ Memory Allocation Related Constants */
#define SOLR_HASHTABLE_PERSISTENT 0
#define SOLR_DOCUMENT_PERSISTENT 0
#define SOLR_DOCUMENT_FIELD_PERSISTENT 0
#define SOLR_CLIENT_PERSISTENT 0
#define SOLR_PARAMS_PERSISTENT 0
#define SOLR_FUNCTIONS_PERSISTENT 0
/* }}} */

/* {{{ SolrException Codes : Internal and UserSpace */

/* {{{ Error codes and messages */

#define SOLR_ERROR_1000 1000L
#define SOLR_ERROR_1000_MSG "Error un-serializing response"

#define SOLR_ERROR_1001 1001L
#define SOLR_ERROR_1001_MSG "SolrClient objects cannot be serialized or unserialized"

#define SOLR_ERROR_1002 1002L
#define SOLR_ERROR_1002_MSG "The '%s' property cannot be removed or set to NULL. SolrObject properties cannot be unset or set to NULL."

#define SOLR_ERROR_1003 1003L
#define SOLR_ERROR_1003_MSG "Error building HTTP query from parameters"

#define SOLR_ERROR_1004 1004L
#define SOLR_ERROR_1004_MSG "Unsuccessful HTTP request"

#define SOLR_ERROR_1005 1005L
#define SOLR_ERROR_1005_MSG "SolrInputDocument objects cannot be serialized or unserialized"

#define SOLR_ERROR_1006 1006L
#define SOLR_ERROR_1006_MSG "SolrObject instances are read-only. Properties cannot be added, updated or removed."

#define SOLR_ERROR_1007 1007L
#define SOLR_ERROR_1007_MSG "SolrDocumentField instances are read-only. Properties cannot be updated or removed."

#define SOLR_ERROR_1008 1008L
#define SOLR_ERROR_1008_MSG "Internal Error 1008 generated from %s %d %s. The observed error is a possible side-effect of an illegal/unsupported operation in userspace. Please check the documentation and try again later."

#define SOLR_ERROR_1009 1009L
#define SOLR_ERROR_1009_MSG "The observed error is a possible side-effect of an illegal/unsupported operation in userspace. This object cannot be cloned. Cloning of this object type is not yet supported."

#define SOLR_ERROR_1010 1010L
#define SOLR_ERROR_1010_MSG "Unsuccessful %s request : Response Code %ld. %s"

#define SOLR_ERROR_4000 4000L
#define SOLR_ERROR_4000_MSG  "Invalid argument"

#define SOLR_ERROR_4001 4001L
#define SOLR_ERROR_4001_MSG  "Illegal Operation"

#define SOLR_ERROR_4002 4002L
#define SOLR_ERROR_4002_MSG  "Return value requested without processing output"

/* }}} */

/* {{{ UserSpace Errors */

#define SOLR_ERROR_4100 4100L
#define SOLR_ERROR_4100_MSG "Mandatory parameter Missing: %s"

/* }}} */

/* {{{ Compile time errors */

/* }}} */

/* }}} */

#endif /* SOLR_CONSTANTS_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

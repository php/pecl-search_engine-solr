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

#ifndef SOLR_TYPES_H
#define SOLR_TYPES_H

#include <main/php.h>
#include <ext/standard/url.h>

#include <curl/curl.h>
#include <curl/curlver.h>
#include <curl/easy.h>

/* Declaring workarounds for SSL private key constants */
#if LIBCURL_VERSION_NUM >= 0x071700
/* Use CURLOPT_KEYPASSWD as is */
#elif LIBCURL_VERSION_NUM >= 0x070903
#define CURLOPT_KEYPASSWD CURLOPT_SSLKEYPASSWD
#else
#define CURLOPT_KEYPASSWD CURLOPT_SSLCERTPASSWD
#endif

#include <Zend/zend_hash.h>
#include <Zend/zend.h>
#include <Zend/zend_API.h>

#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <libxml/tree.h>

typedef unsigned char solr_bool;

#include "solr_string.h"

/* {{{ types for the http client */
typedef enum {

	SOLR_REQUEST_BEGIN   = 0,
	SOLR_REQUEST_SEARCH  = 1,    /** 1 **/
	SOLR_REQUEST_UPDATE  = 2,    /** 2 **/
	SOLR_REQUEST_THREADS = 3,    /** 3 **/
	SOLR_REQUEST_PING    = 4,    /** 4 **/
	SOLR_REQUEST_TERMS   = 5,    /** 5 **/
	SOLR_REQUEST_SYSTEM  = 6,    /** 6 **/
	SOLR_REQUEST_GET     = 7,
	SOLR_REQUEST_END

} solr_request_type_t;

typedef enum {

	SOLR_SERVLET_TYPE_BEGIN   = 0,
	SOLR_SERVLET_TYPE_SEARCH  = 1,
	SOLR_SERVLET_TYPE_UPDATE  = 2,
	SOLR_SERVLET_TYPE_THREADS = 4,
	SOLR_SERVLET_TYPE_PING    = 8,
	SOLR_SERVLET_TYPE_TERMS   = 16,
	SOLR_SERVLET_TYPE_SYSTEM  = 32,
	SOLR_SERVLET_TYPE_GET     = 64,
	SOLR_SERVLET_TYPE_END

} solr_servlet_type_t;

typedef enum
{
	SOLR_PARAM_TYPE_BEGIN 		= 0,
	SOLR_PARAM_TYPE_NORMAL 		= 1,
	SOLR_PARAM_TYPE_SIMPLE_LIST = 2,
	SOLR_PARAM_TYPE_ARG_LIST 	= 4,
	SOLR_PARAM_TYPE_END

} solr_param_type_t;

typedef enum
{
	SOLR_SORT_DIR_ASC  = 0,
	SOLR_SORT_DIR_DESC = 1

} solr_sort_dir_t;

typedef enum  {
    SOLR_JSON_ERROR_NONE = 0,
    SOLR_JSON_ERROR_DEPTH,
    SOLR_JSON_ERROR_STATE_MISMATCH,
    SOLR_JSON_ERROR_CTRL_CHAR,
    SOLR_JSON_ERROR_SYNTAX,
    SOLR_JSON_ERROR_UTF8,
    SOLR_JSON_ERROR_SERIALIZATION
} solr_json_error_codes_t;

typedef struct curl_slist solr_http_header_list_t;

typedef struct {

	solr_string_t buffer;	/* Stores the HTTP request headers */

} solr_curl_send_headers_t;

typedef struct _solr_curl_send_data {

	solr_string_t buffer; /* Stores the HTTP request data */

} solr_curl_send_data_t;

typedef struct {

	solr_string_t buffer; /* Stores the HTTP response headers */

	long int response_code; /* Stores the HTTP response code */

} solr_curl_response_headers_t;

typedef struct {

	solr_string_t buffer;	/* Stores the HTTP response data */

} solr_curl_response_data_t;

typedef struct {

	char str[CURL_ERROR_SIZE + 1]; /* Stores the error message */

	uint  number;	/* Stores the error number */

} solr_curl_error_t;

typedef struct {

	solr_curl_send_headers_t request_header;

	solr_curl_send_data_t request_body;

	solr_curl_send_data_t request_body_debug;

	solr_curl_response_headers_t response_header;

	solr_curl_response_data_t response_body;

	solr_curl_error_t err;

	solr_string_t debug_data_buffer; /* Stores all the debug data */

	size_t handle_status; /* Whether or not the handle is still usable */

	CURLcode result_code;

	CURL *curl_handle;

} solr_curl_t;

typedef struct {

	long int host_port;						/* HTTP port for Solr server */

	long int proxy_port;					/* Proxy port for Solr server */

	long int timeout;						/* maximum time in seconds allowed for the http data transfer operation */

	long int secure;						/* Whether to connect to Solr Server using SSL/HTTPS */

	long int ssl_verify_peer;				/* Determines whether libcurl verifies the peer certificate */

	long int ssl_verify_host;				/* Determines how libcurl verifies the server certificate */

	solr_string_t hostname; 				/* IP address or domain name */

	solr_string_t path; 					/* Path to solr */

	solr_string_t http_auth_credentials; 	/* HTTP Auth username:password */

	solr_string_t proxy_hostname;			/* IP address of domain name for the proxy server */

	solr_string_t proxy_auth_credentials; 	/* Proxy Auth username:password */

	solr_string_t ssl_cert;					/* File name to a PEM-formatted private key + private certificate (concatenated in that order) */

	solr_string_t ssl_key;					/* File name to a PEM-formatted private key */

	solr_string_t ssl_keypassword;			/* The pass phrase/password for the private ssl_key */

	solr_string_t ssl_cainfo;				/* Name of file holding one or more certificates to verify peer with */

	solr_string_t ssl_capath;				/* Name of directory holding multiple CA certificates to verify peer with */

	solr_string_t qs_delimiter;				/* The query string delimiter */

	solr_string_t response_writer;			/* The response writer type (wt parameter) */

	solr_string_t update_url;				/* URL used for updates */

	solr_string_t search_url;				/* URL used for queries */

	solr_string_t thread_url;				/* URL used for thread monitoring */

	solr_string_t ping_url;					/* URL for sending ping requests */

	solr_string_t terms_url;				/* URL for sending terms requests */

	solr_string_t system_url;			    /* URL for sending system requests */

	solr_string_t get_url;                  /* URL for sending realtime get requests */

	solr_string_t update_servlet;			/* The update servlet */

	solr_string_t search_servlet;			/* The search servlet */

	solr_string_t thread_servlet;			/* The thread servlet */

	solr_string_t ping_servlet;				/* The ping servlet */

	solr_string_t terms_servlet;			/* The terms servlet */

	solr_string_t system_servlet;			/* The system info servlet */

	solr_string_t get_servlet;              /* The realtime get servlet */

} solr_client_options_t;

typedef struct {

	ulong client_index;     	   	/* Unique for the SolrClient instance. Used as index in HashTables */

	uint request_count; 			/* The number of requests made from this client */

	solr_client_options_t options;	/* The connection options for this client */

	solr_curl_t handle;           	/* The Solr handle for this client */

} solr_client_t;

/* }}} */

/* Types for documents and collections */

/* {{{ Types for documents and collections */

/* {{{ Types for SolrDocument fields */
typedef struct _solr_field_value_t
{
	solr_char_t *field_value;         /* The value for this field */

	struct _solr_field_value_t *next; /* The next entry in the queue */

} solr_field_value_t;

/**
 * List of Fields in a Solr Document
 *
 * @field_boost stores the boost value
 * @count stores how many fields there are in the list
 * @field_name stores the name of the field
 * @head the first entry in the list (if any)
 * @last the last entry in the list (if any)
 */
typedef struct {

	double field_boost;         /* The boost value for this field */

	uint count;                 /* The number of values in this field */

	solr_char_t *field_name;   	/* The name of the field */

	solr_field_value_t *head;  	/* The first value in the queue */

	solr_field_value_t *last;  	/* The last value in the queue */

} solr_field_list_t;
/* }}} */

/* {{{ Types for Documents and Document Collections */
typedef struct {

	ulong document_index;   /* Unique for the SolrInputDocument instance. Used as index in HashTables */

	uint field_count;  		/* Number of fields in this document */

	double document_boost;	/* The boost value for this document */

	HashTable *fields;    	/* HashTable for storing all the solr_field_list_t fields */

	HashTable *children;    /* Hashtable for storing child documents(zval *) */

} solr_document_t;

/* }}} */

/* {{{ Types for Solr Query Parameters */

typedef struct
{
	solr_string_t value;	/* The value for this parameter */

	solr_string_t arg;		/* The argument for this value*/

	solr_char_t *delimiter_override; /* overrides the arg_list delimiter for this particular argument */

	solr_bool delimiter_overriden; /* is delimiter overriden */

} solr_arg_list_value_t;

typedef union
{
	solr_string_t	normal;			/* Stores normal parameters */

	solr_string_t	simple_list;	/* Stores delimited list parameters */

	solr_arg_list_value_t arg_list;		/* Stores parameters that have arguments */

} solr_pvc_t;

typedef struct _solr_param_value_t
{
	solr_pvc_t contents;				/* A union for the contents of this value */

	struct _solr_param_value_t *prev;	/* The previous value in the list */

	struct _solr_param_value_t *next;	/* The next value in the list */

} solr_param_value_t;

/* Checks if two parameter values are equal */
typedef int (*solr_param_value_equal_func_t)(const solr_param_value_t *a, const solr_param_value_t *b);

/* Used to retrieve all the values for this parameter as a single solr string */
typedef void (*solr_param_fetch_func_t)(void *solr_param, solr_string_t *buffer);

/* Frees the parameter value and its contents. */
typedef void (*solr_param_value_free_func_t)(solr_param_value_t *param_value);

typedef struct {

	solr_param_type_t type;							/* What type of query parameter this is */

	uint count;               		 				/* The number of values for this parameter */

	solr_char_t *param_name;    					/* The name of the parameter */

	size_t param_name_length;    					/* The length of name of the parameter */

	solr_bool allow_multiple;						/* Whether this parameter should store more than one value */

	solr_param_value_t *head;   					/* The first value in the list */

	solr_param_value_t *last;   					/* The last value in the list */

	solr_param_fetch_func_t fetch_func; 			/* Retrieves all the value contents as a single solr_string_t */

	solr_param_value_free_func_t value_free_func;	/* Frees the value and its contents */

	solr_param_value_equal_func_t value_equal_func;	/* Checks if two values are equal */

	solr_char_t delimiter;							/* Default is "," Used to separate list parameter values */

	solr_char_t arg_separator;						/* Used only be arg_lists to separate arguments from values */

} solr_param_t;

/* Used to retrieve parameter values just for display purposes */
typedef void (*solr_param_display_func_t)(solr_param_t *solr_param, zval *param_value_array);

/* Used to retrieve parameter values just for the toString() method */
/* The url_encode parameter will be ignored for now */
typedef void (*solr_param_tostring_func_t)(solr_param_t *solr_param, solr_string_t *buffer, zend_bool url_encode);

typedef struct {

	ulong params_index;	/* The index for this object in the HashTable */

	uint  params_count;	/* The number of parameters for the query object */

	HashTable *params;	/* The HashTable for storing query parameters */

} solr_params_t;

/* }}} */

/* {{{ solr function/localparams type */
typedef struct {

    ulong function_index; /* The index for this object in the HashTable */

    solr_char_t *name;
    size_t name_length;

    solr_char_t *argument;
    size_t argument_length;

    HashTable *params;  /* The HashTable<solr_string_t> for storing function key-val parameters */

} solr_function_t;

/* }}} */

/* }}} */

/* {{{ Extension Global : This should be the last data type declared. More members may be added later. */
ZEND_BEGIN_MODULE_GLOBALS(solr)

	uint request_count;      /* The number of times PHP_RINIT has been called */

	uint document_count;     /* The number of active SolrDocuments in this request */

	uint client_count;	     /* The number of active SolrClients in this request */

	uint functions_count;    /* The number of active Functions in this request */

	HashTable *documents;	 /* HashTable for storing solr_document_t documents */

	HashTable *clients;      /* HashTable for storing solr_client_t clients */

	HashTable *params;		 /* HashTable for storing solr_params_t parameter containers */

	HashTable *functions;    /* HashTable for storing solr_function_t */

ZEND_END_MODULE_GLOBALS(solr)
/* }}} */

typedef struct {
    int code;
    solr_char_t *message;
} solr_exception_t;

#endif /* SOLR_TYPES_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

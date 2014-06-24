/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2014 The PHP Group                                |
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

#if !(PHP_MAJOR_VERSION==5 && PHP_MINOR_VERSION==2)
	ZEND_EXTERN_MODULE_GLOBALS(json)
#endif

/** ************************************************************************ **/
/** FUNCTIONS FOR DECLARING CONSTANTS                                        **/
/** ************************************************************************ **/

/* {{{ void solr_extension_register_constants(int type, int module_number TSRMLS_DC) */
PHP_SOLR_API void solr_extension_register_constants(int type, int module_number TSRMLS_DC)
{
	REGISTER_LONG_CONSTANT("SOLR_MAJOR_VERSION", PHP_SOLR_MAJOR_VERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SOLR_MINOR_VERSION", PHP_SOLR_MINOR_VERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SOLR_PATCH_VERSION", PHP_SOLR_PATCH_VERSION, CONST_CS | CONST_PERSISTENT);

	REGISTER_STRING_CONSTANT("SOLR_EXTENSION_VERSION", PHP_SOLR_DOTTED_VERSION, CONST_CS | CONST_PERSISTENT);
}
/* }}} */

/* {{{ void solr_document_register_class_constants(zend_class_entry * ce TSRMLS_DC) */
PHP_SOLR_API void solr_document_register_class_constants(zend_class_entry *ce TSRMLS_DC)
{
	zend_declare_class_constant_long(ce, "SORT_DEFAULT", sizeof("SORT_DEFAULT")-1, SOLR_SORT_ASC TSRMLS_CC);
	zend_declare_class_constant_long(ce, "SORT_ASC",     sizeof("SORT_ASC")-1, SOLR_SORT_ASC TSRMLS_CC);
	zend_declare_class_constant_long(ce, "SORT_DESC",    sizeof("SORT_DESC")-1, SOLR_SORT_DESC TSRMLS_CC);

	zend_declare_class_constant_long(ce, "SORT_FIELD_NAME", sizeof("SORT_FIELD_NAME")-1, SOLR_SORT_FIELD_NAME TSRMLS_CC);
	zend_declare_class_constant_long(ce, "SORT_FIELD_VALUE_COUNT", sizeof("SORT_FIELD_VALUE_COUNT")-1, SOLR_SORT_FIELD_VALUE_COUNT TSRMLS_CC);
	zend_declare_class_constant_long(ce, "SORT_FIELD_BOOST_VALUE", sizeof("SORT_FIELD_BOOST_VALUE")-1, SOLR_SORT_FIELD_BOOST_VALUE TSRMLS_CC);
}
/* }}} */

/* {{{ void solr_client_register_class_constants(zend_class_entry *ce TSRMLS_DC) */
PHP_SOLR_API void solr_client_register_class_constants(zend_class_entry *ce TSRMLS_DC)
{
	zend_declare_class_constant_long(ce, "SEARCH_SERVLET_TYPE",  sizeof("SEARCH_SERVLET_TYPE")-1, SOLR_SERVLET_TYPE_SEARCH TSRMLS_CC);
	zend_declare_class_constant_long(ce, "UPDATE_SERVLET_TYPE",  sizeof("UPDATE_SERVLET_TYPE")-1, SOLR_SERVLET_TYPE_UPDATE TSRMLS_CC);
	zend_declare_class_constant_long(ce, "THREADS_SERVLET_TYPE", sizeof("THREADS_SERVLET_TYPE")-1, SOLR_SERVLET_TYPE_THREADS TSRMLS_CC);
	zend_declare_class_constant_long(ce, "PING_SERVLET_TYPE",    sizeof("PING_SERVLET_TYPE")-1, SOLR_SERVLET_TYPE_PING TSRMLS_CC);
	zend_declare_class_constant_long(ce, "TERMS_SERVLET_TYPE",    sizeof("TERMS_SERVLET_TYPE")-1, SOLR_SERVLET_TYPE_TERMS TSRMLS_CC);
	zend_declare_class_constant_long(ce, "SYSTEM_SERVLET_TYPE",    sizeof("SYSTEM_SERVLET_TYPE")-1, SOLR_SERVLET_TYPE_SYSTEM TSRMLS_CC);

	zend_declare_class_constant_string(ce, "DEFAULT_SEARCH_SERVLET",  sizeof("DEFAULT_SEARCH_SERVLET")-1, SOLR_DEFAULT_SEARCH_SERVLET TSRMLS_CC);
	zend_declare_class_constant_string(ce, "DEFAULT_UPDATE_SERVLET",  sizeof("DEFAULT_UPDATE_SERVLET")-1, SOLR_DEFAULT_UPDATE_SERVLET TSRMLS_CC);
	zend_declare_class_constant_string(ce, "DEFAULT_THREADS_SERVLET", sizeof("DEFAULT_THREADS_SERVLET")-1, SOLR_DEFAULT_THREADS_SERVLET TSRMLS_CC);
	zend_declare_class_constant_string(ce, "DEFAULT_PING_SERVLET",    sizeof("DEFAULT_PING_SERVLET")-1, SOLR_DEFAULT_PING_SERVLET TSRMLS_CC);
	zend_declare_class_constant_string(ce, "DEFAULT_TERMS_SERVLET",    sizeof("DEFAULT_TERMS_SERVLET")-1, SOLR_DEFAULT_TERMS_SERVLET TSRMLS_CC);
	zend_declare_class_constant_string(ce, "DEFAULT_SYSTEM_SERVLET",    sizeof("DEFAULT_SYSTEM_SERVLET")-1, SOLR_DEFAULT_SYSTEM_SERVLET TSRMLS_CC);
}
/* }}} */

/* {{{ void solr_response_register_class_properties(zend_class_entry *ce TSRMLS_DC) */
PHP_SOLR_API void solr_response_register_class_properties(zend_class_entry *ce TSRMLS_DC)
{
	zend_declare_property_long(ce, "http_status", sizeof("http_status")-1, 0L, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_long(ce, "parser_mode", sizeof("parser_mode")-1, 0L, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_bool(ce, "success", sizeof("success")-1, 0L, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(ce, "response_writer", sizeof("response_writer")-1, SOLR_SPACE_STRING, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(ce, "http_status_message", sizeof("http_status_message")-1, SOLR_SPACE_STRING, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(ce, "http_request_url", sizeof("http_request_url")-1, SOLR_SPACE_STRING, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(ce, "http_raw_request_headers", sizeof("http_raw_request_headers")-1, SOLR_SPACE_STRING, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(ce, "http_raw_request", sizeof("http_raw_request")-1, SOLR_SPACE_STRING, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(ce, "http_raw_response_headers", sizeof("http_raw_response_headers")-1, SOLR_SPACE_STRING, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(ce, "http_raw_response", sizeof("http_raw_response")-1, SOLR_SPACE_STRING, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(ce, "http_digested_response", sizeof("http_digested_response")-1, SOLR_SPACE_STRING, ZEND_ACC_PROTECTED TSRMLS_CC);
}
/* }}} */

/* {{{ void solr_exception_register_class_properties(zend_class_entry *ce TSRMLS_DC) */
PHP_SOLR_API void solr_exception_register_class_properties(zend_class_entry *ce TSRMLS_DC)
{
	zend_declare_property_long(ce, SOLR_SOURCELINE_NO_PROPERTY_NAME, sizeof(SOLR_SOURCELINE_NO_PROPERTY_NAME)-1, __LINE__, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(ce, SOLR_SOURCEFILE_PROPERTY_NAME, sizeof(SOLR_SOURCEFILE_PROPERTY_NAME)-1, __FILE__, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(ce, SOLR_ZIFNAME_PROPERTY_NAME, sizeof(SOLR_ZIFNAME_PROPERTY_NAME)-1, (char *) __func__, ZEND_ACC_PROTECTED TSRMLS_CC);
}
/* }}} */

/* {{{ void solr_response_register_class_constants(zend_class_entry *ce TSRMLS_DC) */
PHP_SOLR_API void solr_response_register_class_constants(zend_class_entry *ce TSRMLS_DC)
{
	zend_declare_class_constant_long(ce, "PARSE_SOLR_OBJ",  sizeof("PARSE_SOLR_OBJ")-1, 0L TSRMLS_CC);
	zend_declare_class_constant_long(ce, "PARSE_SOLR_DOC",  sizeof("PARSE_SOLR_DOC")-1, 1L TSRMLS_CC);
}
/* }}} */

/* {{{ void solr_query_register_class_constants(zend_class_entry *ce TSRMLS_DC) */
PHP_SOLR_API void solr_query_register_class_constants(zend_class_entry *ce TSRMLS_DC)
{
	zend_declare_class_constant_long(ce, "ORDER_ASC",  sizeof("ORDER_ASC")-1, SOLR_SORT_DIR_ASC TSRMLS_CC);
	zend_declare_class_constant_long(ce, "ORDER_DESC",  sizeof("ORDER_DESC")-1, SOLR_SORT_DIR_DESC TSRMLS_CC);

	zend_declare_class_constant_long(ce, "FACET_SORT_INDEX", sizeof("FACET_SORT_INDEX")-1, 0L TSRMLS_CC);
	zend_declare_class_constant_long(ce, "FACET_SORT_COUNT", sizeof("FACET_SORT_COUNT")-1, 1L TSRMLS_CC);

	zend_declare_class_constant_long(ce, "TERMS_SORT_INDEX", sizeof("TERMS_SORT_INDEX")-1, 0L TSRMLS_CC);
	zend_declare_class_constant_long(ce, "TERMS_SORT_COUNT", sizeof("TERMS_SORT_COUNT")-1, 1L TSRMLS_CC);
}
/* }}} */

/** ************************************************************************ **/
/** FUNCTIONS FOR REFERENCE COUNT MANAGEMENT                                 **/
/** ************************************************************************ **/

/** {{{ void solr_zval_add_ref(zval **p) */
PHP_SOLR_API void solr_zval_add_ref(zval **p)
{
	Z_ADDREF_PP(p);
}
/* }}} */

/** {{{ void solr_zval_minus_ref(zval **p) */
PHP_SOLR_API void solr_zval_minus_ref(zval **p)
{
	Z_DELREF_PP(p);
}
/* }}} */

/** ************************************************************************ **/
/** UTILITY FUNCTIONS                                                        **/
/** ************************************************************************ **/

/* {{{ int solr_hashtable_get_new_index(HashTable *ht TSRMLS_DC)
	Retrieves a unique index for this HashTable */
PHP_SOLR_API int solr_hashtable_get_new_index(HashTable *ht TSRMLS_DC)
{
	int new_index = SOLR_GET_RANDOM_NUMBER();

	/* If the key already exists in the HashTable, create another one. */
	while(zend_hash_index_exists(ht, new_index)) {

		new_index = SOLR_GET_RANDOM_NUMBER();
	}

	return new_index;
}
/* }}} */

/* {{{ static inline int solr_fetch_document_entry(zval *objptr, solr_document_t **doc_entry TSRMLS_DC)
	Retrieves a Document from the HashTable */
PHP_SOLR_API int solr_fetch_document_entry(zval *objptr, solr_document_t **doc_entry TSRMLS_DC)
{
	zval *id = zend_read_property(Z_OBJCE_P(objptr), objptr, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, 1 TSRMLS_CC);

	/* Retrieving the value of the document index from the zval */
	long int document_index = Z_LVAL_P(id);

	*doc_entry = NULL;

	/* Retrieve the doc_entry from the HashTable */
	if (zend_hash_index_find(SOLR_GLOBAL(documents), document_index, (void **) doc_entry) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid Document Index %ld. HashTable index does not exist.", document_index);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, SOLR_ERROR_1008_MSG, SOLR_FILE_LINE_FUNC);

		return FAILURE;
	}

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_SOLR_API int solr_fetch_client_entry(zval *objptr, solr_client_t **solr_client TSRMLS_DC) */
PHP_SOLR_API int solr_fetch_client_entry(zval *objptr, solr_client_t **solr_client TSRMLS_DC)
{
	zval *id = zend_read_property(solr_ce_SolrClient, objptr, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, 1 TSRMLS_CC);

	/* Retrieving the value of the client index from the zval */
	long int client_index = Z_LVAL_P(id);

	*solr_client = NULL;

	/* Retrieve the doc_entry from the HashTable */
	if (zend_hash_index_find(SOLR_GLOBAL(clients), client_index, (void **) solr_client) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid SolrClient Index %ld. HashTable index does not exist.", client_index);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, SOLR_ERROR_1008_MSG, SOLR_FILE_LINE_FUNC);

		return FAILURE;
	}

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_SOLR_API int solr_fetch_params_entry(zval *objptr, solr_params_t **solr_params TSRMLS_DC) */
PHP_SOLR_API int solr_fetch_params_entry(zval *objptr, solr_params_t **solr_params TSRMLS_DC)
{
	zval *id = zend_read_property(Z_OBJCE_P(objptr), objptr, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, 1 TSRMLS_CC);

	long int params_index = Z_LVAL_P(id);

	*solr_params = NULL;

	if (zend_hash_index_find(SOLR_GLOBAL(params), params_index, (void **) solr_params) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid SolrParams Index %ld. HashTable index does not exist.", params_index);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, SOLR_ERROR_1008_MSG, SOLR_FILE_LINE_FUNC);

		return FAILURE;
	}

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_SOLR_API xmlDocPtr solr_xml_create_xml_doc(const xmlChar *root_node_name, xmlNode **root_node_ptr) */
PHP_SOLR_API xmlDocPtr solr_xml_create_xml_doc(const xmlChar *root_node_name, xmlNode **root_node_ptr)
{
	xmlNs *ns = NULL;

	xmlDoc *doc_ptr = xmlNewDoc((xmlChar *) "1.0");

	xmlNode *root_node = xmlNewNode(ns, root_node_name);

	xmlDocSetRootElement(doc_ptr, root_node);

	if (root_node_ptr)
	{
		*root_node_ptr = root_node;
	}

	return doc_ptr;
}
/* }}} */

/**
 * escapes strings with characters that are part of the Lucene query syntax
 *
 * @sbuilder is a solr_string_t pointer used to store the escape char sequence
 * @unescaped is the unescaped string. It must be null terminated
 * @unescaped_length is the original length of the unescaped_string
 */
/* {{{ PHP_SOLR_API void solr_escape_query_chars(solr_string_t *sbuilder, solr_char_t *unescaped, long int unescaped_length) */
PHP_SOLR_API void solr_escape_query_chars(solr_string_t *sbuilder, solr_char_t *unescaped, long int unescaped_length)
{
	register int i = 0;

	/**
	 * Lucene supports escaping special characters that are part of the query syntax.
	 *
	 * The current list special characters are
	 * + - && || ! ( ) { } [ ] ^ " ~ * ? : \ /
	 *
	 * These characters are part of the query syntax and must be escaped
	 */
	for (i = 0; i < unescaped_length; i++) {

enter_switchboard :

		switch(unescaped[i])
		{
			case '\\' :
			case '+'  :
			case '-'  :
			case '!'  :
			case '('  :
			case ')'  :
			case ':'  :
			case '/'  :

			case '^'  :
			case '['  :
			case ']'  :
			case '"'  :
			case '{'  :
			case '}'  :
			case '~'  :

			case '*'  :
			case '?'  :
			case ';'  :
			{
				solr_string_appendc(sbuilder, '\\');
			}
			break;

			case '|'  : /* || */
			{
				if ('|' == unescaped[i+1])
				{
					solr_string_appendc(sbuilder, '\\');

					solr_string_append_const(sbuilder, "||");

					i += 2;

					goto enter_switchboard;
				}
			}
			break;

			case '&'  : /* && */
			{
				if ('&' == unescaped[i+1])
				{
					solr_string_appendc(sbuilder, '\\');

					solr_string_append_const(sbuilder, "&&");

					i += 2;

					goto enter_switchboard;
				}
			}
			break;

			default : /* The current character is not a special character */
			{
				/* Do nothing. Just append the character as is */
			}

		} /* END switch(unescaped[i]) */

		solr_string_appendc(sbuilder, unescaped[i]);

	} /* END for (i = 0; i < unescaped_length; i++) { */
}
/* }}} */

/******************************************************************************/
/* SOLR XML RESPONSE DIGEST DATA TYPES AND FUNCTIONS                          */
/******************************************************************************/

/* {{{ solr_doc_encode_t, solr_php_encode_t, solr_encoding_type_t, solr_php_encode_func_t, solr_document_field_encode_func_t */
typedef enum
{
	SOLR_DOC_ENCODE_START  = 0,
	SOLR_DOC_ENCODE_FIELDS = 1,
	SOLR_DOC_ENCODE_FIELD  = 2,
	SOLR_DOC_ENCODE_END

} solr_doc_encode_t;

typedef enum
{
	SOLR_ENCODE_START	= 0,
	SOLR_ENCODE_NULL	= 1,
	SOLR_ENCODE_BOOL	= 2,
	SOLR_ENCODE_INT		= 3,
	SOLR_ENCODE_FLOAT	= 4,
	SOLR_ENCODE_STRING  = 5,
	SOLR_ENCODE_ARRAY  	= 6,
	SOLR_ENCODE_OBJECT  = 7,
	SOLR_ENCODE_DOC		= 8,
	SOLR_ENCODE_RESULT	= 9,
	SOLR_ENCODE_END
} solr_php_encode_t;

typedef enum
{
	SOLR_ENCODE_STANDALONE 		= 0,
	SOLR_ENCODE_OBJECT_PROPERTY = 1,
	SOLR_ENCODE_ARRAY_KEY   	= 2,
	SOLR_ENCODE_ARRAY_INDEX     = 3
} solr_encoding_type_t;

typedef void (*solr_php_encode_func_t)(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode);

typedef void (*solr_document_field_encode_func_t)(const xmlNode *node, xmlNode *field);
/* }}} */

/* {{{ Macros for XML transcoding */
/* Serializes the current XML node */
#define solr_encode_xml_node(__node, __buf, __enc_type, __arr_idx, __mode) solr_encoder_functions[solr_get_xml_type((__node))]((__node),(__buf), (__enc_type), (__arr_idx), (__mode))

#define solr_write_object_closer(__buf) solr_string_append_const((__buf), "}")

#define solr_write_array_closer(__buf) solr_string_append_const((__buf), "}")

#define solr_write_root_object_closer(__buf) solr_string_append_const((__buf), "}")
/* }}} */

/* {{{ static void solr_encode_* prototypes */
static void solr_encode_null(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode);

static void solr_encode_bool(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode);

static void solr_encode_int(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode);

static void solr_encode_float(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode);

static void solr_encode_string(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode);

static void solr_encode_array(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode);

static void solr_encode_object(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode);

static void solr_encode_document(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode);

static void solr_encode_result(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode);

static void solr_encode_document_field_simple(const xmlNode *fieldNode, xmlNode *field);

static void solr_encode_document_field_complex(const xmlNode *fieldNode, xmlNode *field);
/* }}} */

/* {{{ global variables solr_encoder_functions[], solr_document_field_encoders[] */
static solr_php_encode_func_t solr_encoder_functions[] = {
	solr_encode_string,
	solr_encode_null,
	solr_encode_bool,
	solr_encode_int,
	solr_encode_float,
	solr_encode_string,
	solr_encode_array,
	solr_encode_object,
	solr_encode_document,
	solr_encode_result,
	NULL
};

static solr_document_field_encode_func_t solr_document_field_encoders[] = {
	solr_encode_document_field_simple, /* maps to SOLR_SIMPLE_FIELD */
	solr_encode_document_field_complex, /* maps to SOLR_COMPLEX_FIELD */
	NULL
};
/* }}} */

/* {{{ Constants and Macros for handling node types */
#define SOLR_SIMPLE_FIELD 0
#define SOLR_COMPLEX_FIELD 1

#define solr_xml_field_node_type(node) (xmlStrEqual((node)->name, (xmlChar *)"arr")? SOLR_COMPLEX_FIELD : SOLR_SIMPLE_FIELD)

#define solr_encode_document_field(field_in, field_out) solr_document_field_encoders[solr_xml_field_node_type((field_in))]((field_in), (field_out))
/* }}} */

/* Used to figure out now many properties or elements there are in an object or an array */
/* {{{ static inline int solr_get_node_size(const xmlNode *data_node) */
static inline int solr_get_node_size(const xmlNode *data_node)
{
	register int size = 0;

	xmlNode *curr_node = data_node->children;

	while(curr_node != NULL)
	{
		if (XML_ELEMENT_NODE == curr_node->type)
		{
			size++;
		}

		curr_node = curr_node->next;
	}

	return size;
}
/* }}} */

/* {{{ static inline int solr_get_xml_type(xmlNode *node) */
static inline int solr_get_xml_type(xmlNode *node)
{
	solr_char_t *node_name = (solr_char_t *) node->name;

	if (!node_name)
	{
		return SOLR_ENCODE_STRING;
	}

	if (!strcmp(node_name, "str")) {

		return SOLR_ENCODE_STRING;

	} else if (!strcmp(node_name, "int") || !strcmp(node_name, "long") || !strcmp(node_name, "short") || !strcmp(node_name, "byte")) {

		return SOLR_ENCODE_INT;

	} else if (!strcmp(node_name, "double") || !strcmp(node_name, "float")) {

		return SOLR_ENCODE_FLOAT;

	} else if (!strcmp(node_name, "lst")) {

		return SOLR_ENCODE_OBJECT;

	} else if (!strcmp(node_name, "arr")) {

		return SOLR_ENCODE_ARRAY;

	} else if (!strcmp(node_name, "bool")) {

		return SOLR_ENCODE_BOOL;

	} else if (!strcmp(node_name, "null")) {

		return SOLR_ENCODE_NULL;

	} else if (!strcmp(node_name, "result")) {

		return SOLR_ENCODE_RESULT;

	} else {

		return SOLR_ENCODE_STRING;
	}
}
/* }}} */

/* {{{ static inline void solr_write_variable_opener(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index) */
static inline void solr_write_variable_opener(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index)
{
	switch(enc_type)
	{
		case SOLR_ENCODE_OBJECT_PROPERTY : /* fall through */
		case SOLR_ENCODE_ARRAY_KEY :
		{
			solr_char_t *object_name = "_undefined_property_name";

			xmlAttr *name_attr = node->properties; /* get the contents of the name attribute */

			if (name_attr)
			{
				object_name = (solr_char_t *) solr_xml_get_node_contents(name_attr);
			}

			solr_string_append_const(buffer, "s:");

			solr_string_append_long(buffer, strlen(object_name));

			solr_string_append_const(buffer, ":\"");

			solr_string_appends(buffer, object_name, strlen(object_name));

			solr_string_append_const(buffer, "\";");
		}
		break;

		case SOLR_ENCODE_ARRAY_INDEX :
		{
			solr_string_append_const(buffer, "i:");

			solr_string_append_long(buffer, array_index);

			solr_string_appendc(buffer, ';');
		}
		break;

		default :
		{
			/* do nothing */
		}
		break;
	}
}
/* }}} */

/* {{{ static void solr_write_object_opener(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index) */
static void solr_write_object_opener(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index)
{
	int size = solr_get_node_size(node);

	solr_write_variable_opener(node, buffer, enc_type, array_index);

	solr_string_append_const(buffer, "O:10:\"SolrObject\":");

	solr_string_append_long(buffer, size);

	solr_string_append_const(buffer, ":{");
}
/* }}} */

/* {{{ static void solr_write_solr_document_opener(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, int size) */
static void solr_write_solr_document_opener(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, int size)
{
	solr_write_variable_opener(node, buffer, enc_type, array_index);

	solr_string_append_const(buffer, "C:12:\"SolrDocument\":");

	solr_string_append_long(buffer, size);

	solr_string_append_const(buffer, ":{");
}
/* }}} */

/* {{{ static void solr_write_array_opener(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index) */
static void solr_write_array_opener(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index)
{
	int size = solr_get_node_size(node);

	solr_write_variable_opener(node, buffer, enc_type, array_index);

	solr_string_append_const(buffer, "a:");

	solr_string_append_long(buffer, size);

	solr_string_append_const(buffer, ":{");
}
/* }}} */

/* {{{ static void solr_encode_document(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode) */
static void solr_encode_document(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode)
{
	xmlNode *curr_node = NULL;

	solr_write_object_opener(node, buffer, enc_type, array_index);

	curr_node = node->children;

	while(curr_node != NULL)
	{
		if (XML_ELEMENT_NODE == curr_node->type)
		{
			solr_encode_xml_node(curr_node, buffer, SOLR_ENCODE_OBJECT_PROPERTY, 0L, parse_mode);
		}

		curr_node = curr_node->next;
	}

	solr_write_object_closer(buffer);
}
/* }}} */

/**
 * Handles simple data types like strings, integers, booleans etc.
 */
/* {{{ static void solr_encode_document_field_simple(const xmlNode *fieldNode, xmlNode *field) */
static void solr_encode_document_field_simple(const xmlNode *fieldNode, xmlNode *field)
{
	xmlChar *fieldname = solr_xml_get_node_contents(fieldNode->properties);

	xmlChar *field_value = xmlEncodeEntitiesReentrant(fieldNode->doc, solr_xml_get_node_contents(fieldNode));

	xmlNewChild(field, NULL, (xmlChar *) "field_value", field_value);

	xmlNewProp(field, (xmlChar *) "name", fieldname);

	xmlFree(field_value);
}
/* }}} */

/* Handles complex data types like arrays */
/* {{{ static void solr_encode_document_field_complex(const xmlNode *fieldNode, xmlNode *field) */
static void solr_encode_document_field_complex(const xmlNode *fieldNode, xmlNode *field)
{
	xmlChar *fieldname = solr_xml_get_node_contents(fieldNode->properties);

	xmlNode *current_value = fieldNode->children;

	while(current_value != NULL)
	{
		if (current_value->type == XML_ELEMENT_NODE)
		{
			xmlChar *field_value = xmlEncodeEntitiesReentrant(fieldNode->doc, solr_xml_get_node_contents(current_value));

			xmlNewChild(field, NULL, (xmlChar *) "field_value", field_value);

			xmlFree(field_value);
		}

		current_value = current_value->next;
	}

	xmlNewProp(field, (xmlChar *) "name", fieldname);
}
/* }}} */

/**
 *
 * The @enc_type parameter must be SOLR_ENCODE_ARRAY_INDEX
 */
/* {{{ static void solr_encode_solr_document(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode) */
static void solr_encode_solr_document(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode)
{
	xmlNode *solr_document_node = NULL;
	xmlDoc *doc_ptr = solr_xml_create_xml_doc((xmlChar *) "solr_document", &solr_document_node);
	xmlNode *fields_node = xmlNewChild(solr_document_node, NULL, (xmlChar *) "fields", NULL);
	xmlNode *curr_node = node->children;
	int format = 1;
	xmlChar *doc_txt_buffer = NULL;
	int doc_txt_len = 0;

	while(curr_node != NULL)
	{
		if (XML_ELEMENT_NODE == curr_node->type)
		{
			 xmlNode *field = xmlNewChild(fields_node, NULL, (xmlChar *)"field", NULL);

			 solr_encode_document_field(curr_node, field);
		}

		curr_node = curr_node->next;
	}

	/* We have written all the fields to the document */

	xmlIndentTreeOutput = 1;

	/* Dumping the document from memory to the buffer */
	xmlDocDumpFormatMemoryEnc(doc_ptr, &doc_txt_buffer, &doc_txt_len, "UTF-8", format);

	solr_write_solr_document_opener(NULL, buffer, enc_type, array_index, doc_txt_len);

	solr_string_appends(buffer, (char *) doc_txt_buffer, doc_txt_len);

	solr_write_object_closer(buffer);

	xmlFree(doc_txt_buffer);

	xmlFreeDoc(doc_ptr);
}
/* }}} */

/* {{{ static void solr_encode_result(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode) */
static void solr_encode_result(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode)
{
	xmlAttr *properties = node->properties;

	solr_char_t *object_name = (solr_char_t *) node->name;
	solr_char_t *num_found   = NULL;
	solr_char_t *start       = NULL;

	solr_php_encode_func_t document_encoder_functions[] = {
		solr_encode_document,
		solr_encode_solr_document,
		NULL
	};

	xmlAttr *curr_prop = properties;
	xmlXPathContext *xpathctxt = NULL;
	const xmlChar *xpath_expression = (xmlChar *) "child::doc";
	xmlXPathObject *xpathObj = NULL;
	xmlNodeSet *result = NULL;
	long int document_count = 0;

	while(curr_prop != NULL)
	{
		if (solr_xml_match_node(curr_prop, "numFound"))
		{
			num_found = (solr_char_t *) solr_xml_get_node_contents(curr_prop);
		}

		if (solr_xml_match_node(curr_prop, "start"))
		{
			start = (solr_char_t *) solr_xml_get_node_contents(curr_prop);
		}

		if (solr_xml_match_node(curr_prop, "name"))
		{
			object_name = (solr_char_t *) solr_xml_get_node_contents(curr_prop);
		}

		curr_prop = curr_prop->next;
	}

	xpathctxt = xmlXPathNewContext(node->doc);
	xpathctxt->node = (xmlNodePtr) node;
	xpathObj = xmlXPathEval(xpath_expression, xpathctxt);
	result = xpathObj->nodesetval;
	document_count = result->nodeNr;

	solr_string_append_const(buffer, "s:");
	solr_string_append_long(buffer, strlen(object_name));
	solr_string_append_const(buffer, ":\"");
	solr_string_appends(buffer, object_name, strlen(object_name));

	solr_string_append_const(buffer, "\";");
	solr_string_append_const(buffer, "O:10:\"SolrObject\":");

	solr_string_append_long(buffer, 3); /* numFound, start, docs properties */
	solr_string_append_const(buffer, ":{"); /* Object Opener for response */

	/* Writing the numFound property */
	solr_string_append_const(buffer, "s:");
	solr_string_append_long(buffer, sizeof("numFound")-1);
	solr_string_append_const(buffer, ":\"");
	solr_string_appends(buffer, "numFound", sizeof("numFound")-1);
	solr_string_append_const(buffer, "\";");

	solr_string_append_const(buffer, "i:");
	solr_string_appends(buffer, num_found, solr_strlen(num_found));
	solr_string_appendc(buffer, ';');

	/* Writing the start property */
	solr_string_append_const(buffer, "s:");
	solr_string_append_long(buffer, sizeof("start")-1);
	solr_string_append_const(buffer, ":\"");
	solr_string_appends(buffer, "start", sizeof("start")-1);
	solr_string_append_const(buffer, "\";");

	solr_string_append_const(buffer, "i:");
	solr_string_appends(buffer, start, solr_strlen(start));
	solr_string_appendc(buffer, ';');

	/* Writing the docs property */

	solr_string_append_const(buffer, "s:");
	solr_string_append_long(buffer, sizeof("docs")-1);
	solr_string_append_const(buffer, ":\"");
	solr_string_appends(buffer, "docs", sizeof("docs")-1);
	solr_string_append_const(buffer, "\";");

	if (document_count)
	{
		/* Grab all the first /response/result/doc node */
		xmlNode *curr_doc = node->children;

		long int curr_doc_index = 0L;

		/* Array opener */
		solr_string_append_const(buffer, "a:");
		solr_string_append_long(buffer, document_count);
		solr_string_append_const(buffer, ":{");

		while(curr_doc != NULL)
		{
			/* Absolutely no assumptions. At least for now. */
			if (XML_ELEMENT_NODE == curr_doc->type && solr_xml_match_node(curr_doc, "doc"))
			{
				/* This is where you decided whether to use SolrDocument or StdClass */
				/* parse_mode value of 0 creates SolrObject; 1 creates SolrDocument */
				document_encoder_functions[parse_mode](curr_doc, buffer, SOLR_ENCODE_ARRAY_INDEX, curr_doc_index, parse_mode);

				curr_doc_index++;
			}

			curr_doc = curr_doc->next;
		}

		solr_write_array_closer(buffer); /* Array closer */

	} else {

		solr_string_append_const(buffer, "b:0;"); /* This means there are no docs */
	}

	solr_write_object_closer(buffer); /* Object closer */

	xmlXPathFreeContext(xpathctxt);

	xmlXPathFreeObject(xpathObj);
}
/* }}} */

/* {{{ static void solr_encode_null(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode) */
static void solr_encode_null(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode)
{
	/* SolrObject should not contain nulls because of how magic functionality is implemented */
	solr_write_variable_opener(node, buffer, enc_type, array_index);

	/* Setting nulls to boolean false */
	solr_string_append_const(buffer, "b:0;");
}
/* }}} */

/* {{{ static void solr_encode_bool(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode) */
static void solr_encode_bool(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode)
{
	solr_char_t *data_value = (solr_char_t *) solr_xml_get_node_contents(node);
	long int boolean_value = (!strcmp("true", data_value))? 1 : 0;

	solr_write_variable_opener(node, buffer, enc_type, array_index);
	solr_string_append_const(buffer, "b:");
	solr_string_append_long(buffer, boolean_value);

	solr_string_appendc(buffer, ';');
}
/* }}} */

/* {{{ static void solr_encode_int(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode) */
static void solr_encode_int(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode)
{
	solr_char_t *data_value = (solr_char_t *) solr_xml_get_node_contents(node);

	size_t data_value_len   = solr_strlen(data_value);

	solr_write_variable_opener(node, buffer, enc_type, array_index);

	solr_string_append_const(buffer, "i:");

	solr_string_appends(buffer, data_value, data_value_len);

	solr_string_appendc(buffer, ';');
}
/* }}} */

/* {{{ static void solr_encode_float(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode) */
static void solr_encode_float(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode)
{
	solr_char_t *data_value = (solr_char_t *) solr_xml_get_node_contents(node);

	size_t data_value_len   = solr_strlen(data_value);

	solr_write_variable_opener(node, buffer, enc_type, array_index);

	solr_string_append_const(buffer, "d:");

	solr_string_appends(buffer, data_value, data_value_len);

	solr_string_appendc(buffer, ';');
}
/* }}} */

/* {{{ static void solr_encode_string(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode) */
static void solr_encode_string(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode)
{
	solr_char_t *data_value = (solr_char_t *) solr_xml_get_node_contents(node);

	size_t data_value_len   = solr_strlen(data_value);

	solr_write_variable_opener(node, buffer, enc_type, array_index);

	solr_string_append_const(buffer, "s:");

	solr_string_append_long(buffer, data_value_len);

	solr_string_append_const(buffer, ":\"");

	solr_string_appends(buffer, data_value, data_value_len);

	solr_string_append_const(buffer, "\";");
}
/* }}} */

/* {{{ static void solr_encode_array(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode) */
static void solr_encode_array(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode)
{
	xmlNode *curr_node = NULL;

	long int current_index = 0L;

	solr_write_array_opener(node, buffer, enc_type, array_index);

	curr_node = node->children;

	while(curr_node != NULL)
	{
		if (XML_ELEMENT_NODE == curr_node->type)
		{
			solr_encode_xml_node(curr_node, buffer, SOLR_ENCODE_ARRAY_INDEX, current_index, parse_mode);

			current_index++;
		}

		curr_node = curr_node->next;
	}

	solr_write_array_closer(buffer);
}
/* }}} */

/* {{{ static void solr_encode_object(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode) */
static void solr_encode_object(const xmlNode *node, solr_string_t *buffer, solr_encoding_type_t enc_type, long int array_index, long int parse_mode)
{
	xmlNode *curr_node = NULL;

	solr_write_object_opener(node, buffer, enc_type, array_index);

	curr_node = node->children;

	while(curr_node != NULL)
	{
		if (XML_ELEMENT_NODE == curr_node->type)
		{
			solr_encode_xml_node(curr_node, buffer, SOLR_ENCODE_OBJECT_PROPERTY, 0L, parse_mode);
		}

		curr_node = curr_node->next;
	}

	solr_write_object_closer(buffer);
}
/* }}} */

/**
 * Used to digest Xml response messages from Solr
 *
 */
/* {{{ PHP_SOLR_API void solr_encode_generic_xml_response(solr_string_t *buffer, const solr_char_t *serialized, int size, long int parse_mode TSRMLS_DC) */
PHP_SOLR_API void solr_encode_generic_xml_response(solr_string_t *buffer, const solr_char_t *serialized, int size, long int parse_mode TSRMLS_DC)
{
	xmlDoc *doc = xmlReadMemory(serialized, size, NULL, "UTF-8", XML_PARSE_RECOVER);
	xmlNode *root = NULL;

	if (!doc)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error loading XML document");

		return;
	}

	root = xmlDocGetRootElement(doc);

	if (!root)
	{
		xmlFreeDoc(doc);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error loading root of XML document");

		return;
	}

	parse_mode = ((parse_mode < 0L) ? 0L : ((parse_mode > 1L) ? 1L : parse_mode));

	solr_encode_object(root, buffer, SOLR_ENCODE_STANDALONE, 0L, parse_mode);

	if (buffer->len == 0)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error parsing XML document");
	}

	xmlFreeDoc(doc);
}
/* }}} */


/* {{{ PHP_SOLR_API int solr_is_supported_response_writer(const solr_char_t * response_writer, int length) */
PHP_SOLR_API int solr_is_supported_response_writer(const solr_char_t * response_writer, int length)
{
	if (length < 1)
	{
		return 0;
	}

	if (0 == strcmp(response_writer, SOLR_PHP_SERIALIZED_RESPONSE_WRITER))
	{
		return 1;
	}

	if (0 == strcmp(response_writer, SOLR_XML_RESPONSE_WRITER))
	{
		return 1;
	}

	if (0 == strcmp(response_writer, SOLR_JSON_RESPONSE_WRITER))
	{
		return 1;
	}

	return 0;
}
/* }}} */

/* {{{ PHP_SOLR_API solr_char_t *solr_get_json_error_msg(solr_json_error_codes_t error_code) */
PHP_SOLR_API solr_char_t *solr_get_json_error_msg(solr_json_error_codes_t error_code)
{
	switch(error_code)
	{
		case  SOLR_JSON_ERROR_DEPTH:
			return "JSON maximum recursion depth was exceeded";
		break;

		case  SOLR_JSON_ERROR_STATE_MISMATCH:
			return "JSON error state mismatch";
		break;

		case  SOLR_JSON_ERROR_CTRL_CHAR:
			return "JSON control character was encountered";
		break;

		case  SOLR_JSON_ERROR_SYNTAX:
			return "JSON syntax error";
		break;

		case  SOLR_JSON_ERROR_UTF8:
			return "JSON UTF8 error";
		break;

		default :
			return "JSON unknown error";
		break;
	}
}
/* }}} */

/* {{{ PHP_SOLR_API int solr_json_to_php_native(solr_string_t *buffer, const solr_char_t *json_string, int json_string_length TSRMLS_DC) */
PHP_SOLR_API int solr_json_to_php_native(solr_string_t *buffer, const solr_char_t *json_string, int json_string_length TSRMLS_DC)
{
#if !(PHP_MAJOR_VERSION==5 && PHP_MINOR_VERSION==2)
	/* JSON recursion depth. default is 512 */
	long recursion_depth = 1024L;
#endif
	long json_error = 0L;

	php_serialize_data_t var_hash;

	smart_str serialize_buffer = {0};

	/* object instance to perform the method call */
	zval **object_pp = (zval **) NULL;

	/* return value for the function */
	zval json_decode_ret_val, *json_decode_ret_val_ptr, json_last_error_ret_val;

	zend_uchar json_decode_ret_val_type = IS_NULL;

	/* stores the name of the function in this string variable */
	zval json_decode_function_name, json_last_error_function_name;

	/* Default function table to look for the function */
	HashTable *global_function_table = EG(function_table);

	/* json_last_error() */
	zval *json_last_error_params[] = { NULL };

	json_decode_ret_val_ptr = &json_decode_ret_val;

	ZVAL_STRINGL(&json_decode_function_name, "json_decode", sizeof("json_decode"), 0);

	ZVAL_STRINGL(&json_last_error_function_name, "json_last_error", sizeof("json_last_error"), 0);

#if PHP_MAJOR_VERSION==5 && PHP_MINOR_VERSION==2
		php_json_decode(&json_decode_ret_val, (char *) json_string, json_string_length, 1 TSRMLS_CC);
#else
		php_json_decode(&json_decode_ret_val, (char *) json_string, json_string_length, 1, recursion_depth TSRMLS_CC);
#endif

	call_user_function(global_function_table, object_pp, &json_last_error_function_name, &json_last_error_ret_val, 0, json_last_error_params TSRMLS_CC);

	json_error = Z_LVAL(json_last_error_ret_val);

	zval_dtor(&json_last_error_ret_val);

	solr_string_set(buffer, "i:99;", sizeof("i:99;"));

	if (json_error > 0)
	{
		zval_dtor(&json_decode_ret_val);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "JSON error. JSON->PHP serialization error");

		return (int) json_error;
	}

	memset(&var_hash, 0, sizeof(php_serialize_data_t));

	PHP_VAR_SERIALIZE_INIT(var_hash);

	php_var_serialize(&serialize_buffer, &json_decode_ret_val_ptr, &var_hash TSRMLS_CC);

	json_decode_ret_val_type = Z_TYPE_P(json_decode_ret_val_ptr);

	zval_dtor(&json_decode_ret_val);

	solr_string_set(buffer, serialize_buffer.c, serialize_buffer.len);

	PHP_VAR_SERIALIZE_DESTROY(var_hash);

	smart_str_free(&serialize_buffer);

	/* return value should not be of NULL type. NULL means an error has occurred */
	if (json_decode_ret_val_type == IS_NULL)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "JSON error. Error occurred in php_json_decode(). Raw JSON string is \n %s \n", (char *) json_string);

		return (int) SOLR_JSON_ERROR_SERIALIZATION;
	}

	return (int) json_error;
}

PHP_SOLR_API long solr_get_json_last_error(TSRMLS_D)
{
    long json_error;
    zval json_last_error_ret_val, **object_pp;

    zval *json_last_error_params[] = {NULL};
    zval json_last_error_function_name;

    ZVAL_STRINGL(&json_last_error_function_name, "json_last_error", sizeof("json_last_error"), 0);
    /* object instance to perform the method call */
    object_pp = (zval **) NULL;
    call_user_function(EG(function_table), object_pp, &json_last_error_function_name, &json_last_error_ret_val, 0, json_last_error_params TSRMLS_CC);

    json_error = Z_LVAL(json_last_error_ret_val);

    zval_dtor(&json_last_error_ret_val);

    return json_error;
}


/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

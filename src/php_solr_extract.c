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
   | Author: Omar Shaban <omars@php.net>                                  |
   +----------------------------------------------------------------------+
*/

#include "php_solr.h"

extern zend_class_entry *solr_ce_SolrExtractRequest;
extern zend_object_handlers solr_extract_request_object_handlers;
extern zend_class_entry *solr_ce_SolrIllegalArgumentException;
extern zend_class_entry *solr_ce_SolrIllegalOperationException;
extern HashTable *ustreams;

#define SOLR_EXTRACT_OBJ_CTOR() { \
    do { \
        object_init_ex(return_value, solr_ce_SolrExtractRequest); \
        stream_entry = Z_USTREAM_P(return_value); \
        stream_entry->params = Z_REFVAL_P(params); \
        Z_ADDREF_P(stream_entry->params); \
    } while(0); \
}

PHP_SOLR_API int solr_init_ustream(zval *obj)
{
    zend_ulong index = SOLR_UNIQUE_USTREAM_INDEX();
    solr_ustream_t *ustream_entry = NULL;

    ustream_entry = pemalloc(sizeof(solr_ustream_t), 0);

    if (zend_hash_index_update_ptr(SOLR_GLOBAL(ustreams), index, ustream_entry) == NULL) {
        return FAILURE;
    }

    return SUCCESS;
}

/* {{{ solr_extract_obj_handlers */
static void solr_extract_free_object_handler(zend_object *obj)
{
    solr_ustream_t *intern = solr_get_ustream_object(obj);

    solr_string_free(&(intern->content_info->filename));
    solr_string_free(&(intern->content_info->stream_info.binary_content));
    solr_string_free(&(intern->content_info->stream_info.mime_type));

    Z_DELREF_P(intern->params);

    efree(intern->content_info);
    zend_object_std_dtor(obj);
    efree(intern);
}

zend_object *solr_extract_create_object_handler(zend_class_entry *ce)
{
    solr_ustream_t *intern = ecalloc(1, sizeof(solr_ustream_t)+zend_object_properties_size(ce));
    memset(intern, 0, sizeof(solr_ustream_t));

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->content_info = emalloc(sizeof(solr_cuv_t));

    solr_string_init(&(intern->content_info->stream_info.mime_type));
    solr_string_init(&(intern->content_info->stream_info.binary_content));

    solr_extract_request_object_handlers.free_obj = solr_extract_free_object_handler;

    intern->std.handlers = &solr_extract_request_object_handlers;

    return &intern->std;
}
/* }}} */

PHP_METHOD(SolrExtractRequest, __construct)
{
}

PHP_METHOD(SolrExtractRequest, __destruct)
{
}

/* {{{ proto SolrExtractRequest::createFromFile(string filename, SolrModifiableParams params)
   Create request from file */
PHP_METHOD(SolrExtractRequest, createFromFile)
{
    char *filename;
    COMPAT_ARG_SIZE_T filename_length = 0;
    solr_ustream_t *stream_entry = NULL;
    zval *params = NULL;
    zend_error_handling error_handling;

    zend_replace_error_handling(EH_THROW, solr_ce_SolrIllegalArgumentException, &error_handling);

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "sz", &filename, &filename_length, &params) == FAILURE) {
        zend_restore_error_handling(&error_handling);
        return;
    }

    SOLR_EXTRACT_OBJ_CTOR();

    stream_entry->content_type = SOLR_EXTRACT_CONTENT_FILE;

    solr_string_set_ex(&(stream_entry->content_info->filename), filename, filename_length);
}

/* {{{ proto SolrExtractRequest::createFromStream(string content, string contentType, SolrModifiableParams params)
   Create request from binary stream */
PHP_METHOD(SolrExtractRequest, createFromStream)
{
    char *content, *content_type;
    COMPAT_ARG_SIZE_T content_length = 0, content_type_length = 0;
    solr_ustream_t *stream_entry = NULL;
    zval *params = NULL;
    zend_error_handling error_handling;

    zend_replace_error_handling(EH_THROW, solr_ce_SolrIllegalArgumentException, &error_handling);
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ssz", &content, &content_length, &content_type, &content_type_length, &params) == FAILURE) {
        zend_restore_error_handling(&error_handling);
        return;
    }

    SOLR_EXTRACT_OBJ_CTOR();

    stream_entry->content_type = SOLR_EXTRACT_CONTENT_STREAM;
    solr_string_set_ex(&(stream_entry->content_info->stream_info.mime_type), content_type, content_type_length);
    solr_string_set_ex(&(stream_entry->content_info->stream_info.binary_content), content, content_length);
}
/* }}} */

/* {{{ proto SolrExtractRequest::__clone(void)
   Should not be called directly. Cloning is not supported. */
PHP_METHOD(SolrExtractRequest, __clone)
{
    solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_4001, SOLR_FILE_LINE_FUNC, "Cloning of SolrExtractRequest objects is currently not supported");
}
/* }}} */

/* {{{ proto SolrExtractRequest::__sleep(void)
   Should not be called directly. Serialization is not supported. */
PHP_METHOD(SolrExtractRequest, __sleep)
{
    solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_4001, SOLR_FILE_LINE_FUNC, "SolrExtractRequest objects cannot be serialized or unserialized");
}
/* }}} */

/* {{{ proto SolrExtractRequest::__wakeup(void)
   Should not be called directly. Deserialization is not supported. */
PHP_METHOD(SolrExtractRequest, __wakeup)
{
    solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_4001, SOLR_FILE_LINE_FUNC, "SolrExtractRequest objects cannot be serialized or unserialized");
}
/* }}} */

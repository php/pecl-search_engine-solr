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

#ifdef HAVE_SOLR

/* PHP versions lower than 5.2.3 are not compatible or are causing tests to FAIL */
#if ((PHP_MAJOR_VERSION < 5) || (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION < 2) || (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION == 2 && PHP_RELEASE_VERSION < 3))
#error PHP 5.2.3 or newer is required. Please upgrade your php version.
#endif

#if LIBCURL_VERSION_NUM < 0x070F00
#error libcurl 7.15.0 or later is required. Please upgrade your libcurl version.
#endif

#if LIBXML_VERSION < 20616
#error libxml2 2.6.16 or later is required. Please upgrade your libxml2 version.
#endif

/******************************************************************************/
/** GLOBAL VARIABLE FOR THE EXTENSION				                         **/
/******************************************************************************/

/* {{{ ZEND_DECLARE_MODULE_GLOBALS(solr) */
ZEND_DECLARE_MODULE_GLOBALS(solr)
/* }}} */

/******************************************************************************/
/** OBJECT HANDLERS AND DECLARATIONS FOR CLASS ENTRIES                       **/
/******************************************************************************/

/* {{{ zend_class_entry declarations of the classes */
zend_class_entry *solr_ce_SolrObject;
zend_class_entry *solr_ce_SolrInputDocument;
zend_class_entry *solr_ce_SolrDocument;
zend_class_entry *solr_ce_SolrDocumentField;
zend_class_entry *solr_ce_SolrClient;
zend_class_entry *solr_ce_SolrParams;
zend_class_entry *solr_ce_SolrModifiableParams;
zend_class_entry *solr_ce_SolrCollapseFunction;
zend_class_entry *solr_ce_SolrQuery;
zend_class_entry *solr_ce_SolrResponse;
zend_class_entry *solr_ce_SolrQueryResponse;
zend_class_entry *solr_ce_SolrUpdateResponse;
zend_class_entry *solr_ce_SolrPingResponse;
zend_class_entry *solr_ce_SolrGenericResponse;
zend_class_entry *solr_ce_SolrUtils;
zend_class_entry *solr_ce_SolrException;
zend_class_entry *solr_ce_SolrIllegalOperationException;
zend_class_entry *solr_ce_SolrIllegalArgumentException;
zend_class_entry *solr_ce_SolrClientException;
zend_class_entry *solr_ce_SolrServerException;
zend_class_entry *solr_ce_SolrMissingMandatoryParameterException;
/* }}} */

/* {{{ zend_object_handlers */
zend_object_handlers solr_object_handlers;
zend_object_handlers solr_document_field_handlers;
zend_object_handlers solr_input_document_object_handlers;
zend_object_handlers solr_client_object_handlers;
zend_object_handlers solr_response_object_handlers;
zend_object_handlers solr_collapse_function_object_handlers;
/* }}} */

/* {{{ static void php_solr_globals_ctor(zend_solr_globals *solr_globals_arg TSRMLS_DC)
	Global variable initializer. In ZTS mode, called once for each thread spawned. */
static void php_solr_globals_ctor(zend_solr_globals *solr_globals_arg TSRMLS_DC)
{
	/* Initializing the counters to Zero */
	solr_globals_arg->request_count    = 0U;
    solr_globals_arg->document_count   = 0U;
    solr_globals_arg->client_count     = 0U;
    solr_globals_arg->functions_count  = 0U;

    solr_globals_arg->documents   = NULL;
    solr_globals_arg->clients     = NULL;
    solr_globals_arg->params      = NULL;
    solr_globals_arg->functions   = NULL;
}
/* }}} */

/******************************************************************************/
/** DECLARING STRUCTURES FOR METHOD ARGUMENTS TYPE HINTING                   **/
/******************************************************************************/

/* {{{ arg_info vectors for functions and methods */

ZEND_BEGIN_ARG_INFO_EX(SolrObject__get_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, property_name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrObject__set_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 2)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, property_name)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, property_value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrObject_one_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, property_name)
ZEND_END_ARG_INFO()

/* {{{ SolrDocument arguments */
ZEND_BEGIN_ARG_INFO_EX(SolrDocument__construct_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDocument_addField_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 2)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldName)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldValue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDocument_getField_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDocument_fieldExists_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDocument_deleteField_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDocument_sort_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, sortOrderBy)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, sortDirection)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDocument_merge_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_OBJ_INFO(SOLR_ARG_PASS_BY_REF_TRUE, sourceDoc, SolrDocument, SOLR_ARG_ALLOW_NULL_FALSE)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, overwrite)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDocument_current_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDocument_getInputDocument_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(SolrDocument_unserialize_args, 0)
ZEND_ARG_INFO(0, serialized)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ SolrInputDocument arguments */
ZEND_BEGIN_ARG_INFO_EX(SolrInputDocument__construct_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrInputDocument_setBoost_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, documentBoostValue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrInputDocument_addField_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 2)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldName)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldValue)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldBoostValue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrInputDocument_getFieldBoost_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrInputDocument_getField_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrInputDocument_setFieldBoost_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 2)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldName)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldBoostValue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrInputDocument_fieldExists_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrInputDocument_deleteField_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrInputDocument_sort_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, sortOrderBy)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, sortDirection)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrInputDocument_merge_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_OBJ_INFO(SOLR_ARG_PASS_BY_REF_TRUE, sourceDoc, SolrInputDocument, SOLR_ARG_ALLOW_NULL_FALSE)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, overwrite)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrInputDocument_addChildDocument_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_OBJ_INFO(SOLR_ARG_PASS_BY_REF_TRUE, child, SolrInputDocument, SOLR_ARG_ALLOW_NULL_FALSE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrInputDocument_addChildDocuments_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_ARRAY_INFO(SOLR_ARG_PASS_BY_REF_TRUE, docs, SOLR_ARG_ALLOW_NULL_FALSE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrInputDocument_updateField_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 3)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldName)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, modifier)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrInputDocument_setVersion_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, version)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ SolrClient arguments */
ZEND_BEGIN_ARG_INFO_EX(SolrClient_constructor_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_ARRAY_INFO(SOLR_ARG_PASS_BY_REF_FALSE, clientOptions, SOLR_ARG_ALLOW_NULL_FALSE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_query_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_OBJ_INFO(SOLR_ARG_PASS_BY_REF_TRUE, query, SolrParams, SOLR_ARG_ALLOW_NULL_FALSE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_addDocument_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_OBJ_INFO(SOLR_ARG_PASS_BY_REF_TRUE, doc, SolrInputDocument, SOLR_ARG_ALLOW_NULL_FALSE)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, overwrite)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, commitWithin)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_addDocuments_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_ARRAY_INFO(SOLR_ARG_PASS_BY_REF_TRUE, docs, SOLR_ARG_ALLOW_NULL_FALSE)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, overwrite)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, commitWithin)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_request_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, raw_request)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_setResponseWriter_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, responseWriter)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_commit_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, softCommit)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, waitSearcher)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, expungeDeletes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_optimize_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, maxSegments)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, softCommit)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, waitSearcher)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_rollback_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_deleteById_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_deleteByIds_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_ARRAY_INFO(SOLR_ARG_PASS_BY_REF_FALSE, ids, SOLR_ARG_ALLOW_NULL_FALSE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_deleteByQuery_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, query)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_deleteByQueries_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_ARRAY_INFO(SOLR_ARG_PASS_BY_REF_FALSE, queries, SOLR_ARG_ALLOW_NULL_FALSE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_ping_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_threads_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_info_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrClient_setServlet_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 2)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, type)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, value)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ SolrParams arguments */
ZEND_BEGIN_ARG_INFO_EX(SolrParams_setParam_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 2)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, name)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrParams_addParam_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 2)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, name)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrParams_toString_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, url_encode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrParams_getParam_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, param_name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(SolrParams_unserialize_args, 0)
ZEND_ARG_INFO(0, serialized)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ SolrQuery arguments */
ZEND_BEGIN_ARG_INFO_EX(SolrQuery_constructor_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, q)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_setQuery_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, q)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_setStart_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, start)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_setRows_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, rows)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_addField_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, field)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_addSortField_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, field)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, order)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_addFilterQuery_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fq)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_setShowDebugInfo_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, flag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_setExplainOther_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, flag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_setTimeAllowed_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, timeAllowed)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_setOmitHeader_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, flag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_setEchoHandler_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, flag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_setEchoParams_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_facet_get_1_0_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, field_override)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_facet_1_1_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_facet_2_1_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, value)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, field_override)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_group_1_1_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_hl_get_1_0_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, field_override)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_hl_1_1_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_hl_2_1_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, value)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, field_override)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_stats_1_1_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_mlt_1_1_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_mlt_2_2_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 2)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, field)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, boost)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_terms_1_1_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_setGroupCachePct_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, percent)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrQuery_collapse_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_OBJ_INFO(SOLR_ARG_PASS_BY_REF_TRUE, collapseFunction, SolrCollapseFunction, SOLR_ARG_ALLOW_NULL_FALSE)
ZEND_END_ARG_INFO()

/* }}} */

/* {{{ Solr Generic arguments */
ZEND_BEGIN_ARG_INFO_EX(Solr_no_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ */
ZEND_BEGIN_ARG_INFO_EX(SolrResponse_setParseMode_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, parser_mode)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ SolrUtils */
ZEND_BEGIN_ARG_INFO_EX(SolrUtils_escapeQueryChars_arg, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, str)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrUtils_digestXML_arg, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, xmlresponse)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, parse_mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrUtils_digestJson_arg, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, jsonResponse)
ZEND_END_ARG_INFO()

/* }}} */

ZEND_BEGIN_ARG_INFO_EX(SolrCollapseFunction_construct_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, field)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrCollapseFunction_set_size_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, size)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrCollapseFunction_set_hint_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, hint)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrCollapseFunction_set_max_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, max)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrCollapseFunction_set_min_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, min)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrCollapseFunction_set_field_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, fieldName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrCollapseFunction_set_null_policy_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(SOLR_ARG_PASS_BY_REF_FALSE, policy)
ZEND_END_ARG_INFO()

/* }}} */

/* {{{ solr_functions[] */
static zend_function_entry solr_functions[] = {
	PHP_FE(solr_get_version, Solr_no_args)

	PHP_FE_END
};
/* }}} */

/* {{{ solr_object_methods */
static zend_function_entry solr_object_methods[] = {
	SOLR_CTOR(SolrObject, __construct, Solr_no_args)
	SOLR_DTOR(SolrObject, __destruct, Solr_no_args)
/**
	Temporarily disconnected for now.
	May be brought back in the future.

	PHP_ME(SolrObject, __set, SolrObject__set_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrObject, __get, SolrObject__get_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrObject, __isset, SolrObject_one_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrObject, __unset, SolrObject_one_args, ZEND_ACC_PUBLIC)
*/
	PHP_ME(SolrObject, offsetSet, SolrObject__set_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrObject, offsetGet, SolrObject__get_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrObject, offsetExists, SolrObject_one_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrObject, offsetUnset, SolrObject_one_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrObject, getPropertyNames, Solr_no_args, ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

/* {{{ solr_document_methods */
static zend_function_entry solr_document_field_methods[] = {
	SOLR_CTOR(SolrDocumentField, __construct, Solr_no_args)
	SOLR_DTOR(SolrDocumentField, __destruct, Solr_no_args)

	PHP_FE_END
};
/* }}} */

/* {{{ solr_collapse_function_methods for the SolrCollapseFunction ce */
static zend_function_entry solr_collapse_function_methods[] = {
    SOLR_CTOR(SolrCollapseFunction, __construct, SolrCollapseFunction_construct_args)
    SOLR_DTOR(SolrCollapseFunction, __destruct, Solr_no_args)

    PHP_ME(SolrCollapseFunction, setField, SolrCollapseFunction_set_field_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrCollapseFunction, getField, Solr_no_args, ZEND_ACC_PUBLIC)

    PHP_ME(SolrCollapseFunction, setMax, SolrCollapseFunction_set_max_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrCollapseFunction, getMax, Solr_no_args, ZEND_ACC_PUBLIC)

    PHP_ME(SolrCollapseFunction, setMin, SolrCollapseFunction_set_min_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrCollapseFunction, getMin, Solr_no_args, ZEND_ACC_PUBLIC)

    PHP_ME(SolrCollapseFunction, setSize, SolrCollapseFunction_set_size_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrCollapseFunction, getSize, Solr_no_args, ZEND_ACC_PUBLIC)

    PHP_ME(SolrCollapseFunction, setHint, SolrCollapseFunction_set_hint_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrCollapseFunction, getHint, Solr_no_args, ZEND_ACC_PUBLIC)

    PHP_ME(SolrCollapseFunction, setNullPolicy, SolrCollapseFunction_set_null_policy_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrCollapseFunction, getNullPolicy, Solr_no_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrCollapseFunction, __toString, Solr_no_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrCollapseFunction, __sleep, Solr_no_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrCollapseFunction, __wakeup, Solr_no_args, ZEND_ACC_PUBLIC)

    PHP_FE_END
};
/* }}} */

/* {{{ solr_document_methods */
static zend_function_entry solr_document_methods[] = {
	SOLR_CTOR(SolrDocument, __construct, SolrDocument__construct_args)
	SOLR_DTOR(SolrDocument, __destruct, Solr_no_args)

	PHP_ME(SolrDocument, __clone, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CLONE)
	PHP_ME(SolrDocument, __set, SolrDocument_addField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, __get, SolrDocument_getField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, __isset, SolrDocument_fieldExists_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, __unset, SolrDocument_deleteField_args, ZEND_ACC_PUBLIC)

	PHP_ME(SolrDocument, offsetSet, SolrDocument_addField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, offsetGet, SolrDocument_getField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, offsetExists, SolrDocument_fieldExists_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, offsetUnset, SolrDocument_deleteField_args, ZEND_ACC_PUBLIC)

	PHP_ME(SolrDocument, current, SolrDocument_current_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, key, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, next, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, rewind, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, valid, Solr_no_args, ZEND_ACC_PUBLIC)

	PHP_ME(SolrDocument, serialize, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, unserialize, SolrDocument_unserialize_args, ZEND_ACC_PUBLIC)

	PHP_ME(SolrDocument, clear, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_MALIAS(SolrDocument, reset, clear, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, addField, SolrDocument_addField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, getFieldNames, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, getFieldCount, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, getField, SolrDocument_getField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, toArray, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, fieldExists, SolrDocument_fieldExists_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, deleteField, SolrDocument_deleteField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, sort, SolrDocument_sort_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, merge, SolrDocument_merge_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, getInputDocument, SolrDocument_getInputDocument_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, getChildDocumentsCount, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, hasChildDocuments, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrDocument, getChildDocuments, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/* {{{ solr_input_document_methods */
static zend_function_entry solr_input_document_methods[] = {
	SOLR_CTOR(SolrInputDocument, __construct, SolrInputDocument__construct_args)
	SOLR_DTOR(SolrInputDocument, __destruct, Solr_no_args)
	PHP_ME(SolrInputDocument, __clone, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CLONE)
	PHP_ME(SolrInputDocument, __sleep, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, __wakeup, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, setBoost, SolrInputDocument_setBoost_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, getBoost, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, clear, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_MALIAS(SolrInputDocument, reset, clear, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, addField, SolrInputDocument_addField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, updateField, SolrInputDocument_updateField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, getFieldBoost, SolrInputDocument_getFieldBoost_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, setFieldBoost, SolrInputDocument_setFieldBoost_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, getFieldNames, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, getFieldCount, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, getField, SolrInputDocument_getField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, toArray, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, fieldExists, SolrInputDocument_fieldExists_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, deleteField, SolrInputDocument_deleteField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, sort, SolrInputDocument_sort_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, merge, SolrInputDocument_merge_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, addChildDocument, SolrInputDocument_addChildDocument_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, getChildDocuments, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, hasChildDocuments, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, getChildDocumentsCount, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, addChildDocuments, SolrInputDocument_addChildDocuments_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, setVersion, SolrInputDocument_setVersion_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrInputDocument, getVersion, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/* {{{ solr_client_methods */
static zend_function_entry solr_client_methods[] = {
	SOLR_CTOR(SolrClient, __construct, SolrClient_constructor_args)
	SOLR_DTOR(SolrClient, __destruct, Solr_no_args)
	PHP_ME(SolrClient, __sleep, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, __wakeup, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, __clone, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CLONE)
	PHP_ME(SolrClient, getOptions, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, getDebug, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, setServlet, SolrClient_setServlet_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, query, SolrClient_query_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, addDocument, SolrClient_addDocument_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, addDocuments, SolrClient_addDocuments_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, request, SolrClient_request_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, setResponseWriter, SolrClient_setResponseWriter_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, deleteById, SolrClient_deleteById_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, deleteByIds, SolrClient_deleteByIds_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, deleteByQuery, SolrClient_deleteByQuery_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, deleteByQueries, SolrClient_deleteByQueries_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, getById, SolrClient_deleteById_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, getByIds, SolrClient_deleteByIds_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, commit, SolrClient_commit_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, optimize, SolrClient_optimize_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, rollback, SolrClient_rollback_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, ping, SolrClient_ping_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, system, SolrClient_info_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrClient, threads, SolrClient_threads_args, ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

/* {{{ solr_exception_methods. None. */
static zend_function_entry solr_exception_methods[] = {
	PHP_ME(SolrException, getInternalInfo, Solr_no_args, ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

/* {{{ solr_exception_methods. None. */
static zend_function_entry solr_client_exception_methods[] = {
	PHP_ME(SolrClientException, getInternalInfo, Solr_no_args, ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

/* {{{ solr_exception_methods. None. */
static zend_function_entry solr_server_exception_methods[] = {
    PHP_ME(SolrServerException, getInternalInfo, Solr_no_args, ZEND_ACC_PUBLIC)

    PHP_FE_END
};
/* }}} */

/* {{{ solr_exception_methods. None. */
static zend_function_entry solr_illegal_operation_exception_methods[] = {
	PHP_ME(SolrIllegalOperationException, getInternalInfo, Solr_no_args, ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

/* {{{ solr_exception_methods. None. */
static zend_function_entry solr_illegal_argument_exception_methods[] = {
	PHP_ME(SolrIllegalArgumentException, getInternalInfo, Solr_no_args, ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

/* PHP_MALIAS(SolrInputDocument, reset, clear, Solr_no_args, ZEND_ACC_PUBLIC) */

/* {{{ solr_params_methods. */
static zend_function_entry solr_params_methods[] = {
	PHP_ME(SolrParams, setParam,  SolrParams_setParam_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrParams, addParam,  SolrParams_addParam_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrParams, __toString, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrParams, toString, SolrParams_toString_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrParams, getParams, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrParams, getParam, SolrParams_getParam_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrParams, getPreparedParams, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrParams, __clone, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CLONE)
	PHP_ME(SolrParams, serialize,   NULL, ZEND_ACC_PUBLIC)
	PHP_ME(SolrParams, unserialize,  SolrParams_unserialize_args, ZEND_ACC_PUBLIC)
	PHP_MALIAS(SolrParams, add, addParam, SolrParams_addParam_args, ZEND_ACC_PUBLIC)
	PHP_MALIAS(SolrParams, set, setParam, SolrParams_setParam_args, ZEND_ACC_PUBLIC)
	PHP_MALIAS(SolrParams, get, getParam, SolrParams_getParam_args, ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

/* {{{ solr_modifiable_params_methods. */
static zend_function_entry solr_modifiable_params_methods[] = {
	SOLR_CTOR(SolrModifiableParams, __construct, Solr_no_args)
	SOLR_DTOR(SolrModifiableParams, __destruct, Solr_no_args)

	PHP_FE_END
};
/* }}} */

/* {{{ solr_query_methods. */
static zend_function_entry solr_query_methods[] = {
	SOLR_CTOR(SolrQuery, __construct, SolrQuery_constructor_args)
	SOLR_DTOR(SolrQuery, __destruct, Solr_no_args)

	/* CommonQueryParameters  */
	PHP_ME(SolrQuery, setQuery, SolrQuery_setQuery_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getQuery, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setStart, SolrQuery_setStart_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getStart, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setRows,  SolrQuery_setRows_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getRows,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, addField,  SolrQuery_addField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, removeField,  SolrQuery_addField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFields,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, addSortField,  SolrQuery_addSortField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, removeSortField,  SolrQuery_addField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getSortFields,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, addFilterQuery,  SolrQuery_addFilterQuery_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, removeFilterQuery,  SolrQuery_addFilterQuery_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFilterQueries,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setShowDebugInfo,  SolrQuery_setShowDebugInfo_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setExplainOther,  SolrQuery_setExplainOther_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setTimeAllowed,  SolrQuery_setTimeAllowed_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getTimeAllowed,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setOmitHeader,  SolrQuery_setOmitHeader_args, ZEND_ACC_PUBLIC)

	/* CoreQueryParameters */
	PHP_ME(SolrQuery, setEchoHandler,  SolrQuery_setEchoHandler_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setEchoParams,  SolrQuery_setEchoParams_args, ZEND_ACC_PUBLIC)

	/* SimpleFacetParameters */
	PHP_ME(SolrQuery, setFacet,  SolrQuery_facet_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacet,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, addFacetField,  SolrQuery_facet_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, removeFacetField,  SolrQuery_facet_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacetFields,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, addFacetQuery,  SolrQuery_facet_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, removeFacetQuery,  SolrQuery_facet_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacetQueries,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setFacetPrefix,  SolrQuery_facet_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacetPrefix,  SolrQuery_facet_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setFacetSort,  SolrQuery_facet_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacetSort,  SolrQuery_facet_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setFacetLimit,  SolrQuery_facet_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacetLimit,  SolrQuery_facet_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setFacetOffset,  SolrQuery_facet_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacetOffset,  SolrQuery_facet_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setFacetMinCount,  SolrQuery_facet_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacetMinCount,  SolrQuery_facet_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setFacetMissing,  SolrQuery_facet_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacetMissing,  SolrQuery_facet_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setFacetMethod,  SolrQuery_facet_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacetMethod,  SolrQuery_facet_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setFacetEnumCacheMinDefaultFrequency,  SolrQuery_facet_2_1_args, ZEND_ACC_PUBLIC)

	/* Date Faceting Parameters */
	PHP_ME(SolrQuery, addFacetDateField,  SolrQuery_facet_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, removeFacetDateField,  SolrQuery_facet_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacetDateFields,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setFacetDateStart,  SolrQuery_facet_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacetDateStart,  SolrQuery_facet_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setFacetDateEnd,  SolrQuery_facet_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacetDateEnd,  SolrQuery_facet_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setFacetDateGap,  SolrQuery_facet_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacetDateGap,  SolrQuery_facet_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setFacetDateHardEnd,  SolrQuery_facet_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacetDateHardEnd,  SolrQuery_facet_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, addFacetDateOther,  SolrQuery_facet_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, removeFacetDateOther,  SolrQuery_facet_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getFacetDateOther,  SolrQuery_facet_get_1_0_args, ZEND_ACC_PUBLIC)

	/* SimpleGroupParameters */
	PHP_ME(SolrQuery, setGroup,  SolrQuery_group_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getGroup, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, addGroupField,  SolrQuery_group_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getGroupFields,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, addGroupFunction,  SolrQuery_group_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getGroupFunctions, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, addGroupQuery,  SolrQuery_group_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getGroupQueries, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setGroupLimit,  SolrQuery_group_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getGroupLimit, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setGroupOffset,  SolrQuery_group_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getGroupOffset, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, addGroupSortField,  SolrQuery_addSortField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getGroupSortFields, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setGroupFormat,  SolrQuery_group_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getGroupFormat, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setGroupMain,  SolrQuery_group_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getGroupMain, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setGroupNGroups,  SolrQuery_group_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getGroupNGroups, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setGroupTruncate,  SolrQuery_group_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getGroupTruncate, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setGroupFacet,  SolrQuery_group_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getGroupFacet, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setGroupCachePercent, SolrQuery_setGroupCachePct_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getGroupCachePercent, Solr_no_args, ZEND_ACC_PUBLIC)

	/* Collapse Function */
	PHP_ME(SolrQuery, collapse, SolrQuery_collapse_args, ZEND_ACC_PUBLIC)

	/* Expand Componenet */
	PHP_ME(SolrQuery, setExpand, SolrQuery_group_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getExpand, Solr_no_args, ZEND_ACC_PUBLIC)

	PHP_ME(SolrQuery, addExpandSortField, SolrQuery_addSortField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, removeExpandSortField, SolrQuery_addField_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getExpandSortFields, Solr_no_args, ZEND_ACC_PUBLIC)

	PHP_ME(SolrQuery, setExpandRows, SolrQuery_group_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getExpandRows, Solr_no_args, ZEND_ACC_PUBLIC)

	PHP_ME(SolrQuery, setExpandQuery, SolrQuery_setQuery_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getExpandQuery, Solr_no_args, ZEND_ACC_PUBLIC)

	PHP_ME(SolrQuery, addExpandFilterQuery, SolrQuery_addFilterQuery_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, removeExpandFilterQuery, SolrQuery_addFilterQuery_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getExpandFilterQueries, Solr_no_args, ZEND_ACC_PUBLIC)

	/* HighlightingParameters */
	PHP_ME(SolrQuery, setHighlight,  SolrQuery_hl_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlight,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, addHighlightField,  SolrQuery_hl_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, removeHighlightField,  SolrQuery_hl_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightFields,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightSnippets,  SolrQuery_hl_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightSnippets,  SolrQuery_hl_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightFragsize,  SolrQuery_hl_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightFragsize,  SolrQuery_hl_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightMergeContiguous,  SolrQuery_hl_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightMergeContiguous,  SolrQuery_hl_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightRequireFieldMatch,  SolrQuery_hl_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightRequireFieldMatch,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightMaxAnalyzedChars,  SolrQuery_hl_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightMaxAnalyzedChars,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightAlternateField,  SolrQuery_hl_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightAlternateField,  SolrQuery_hl_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightMaxAlternateFieldLength,  SolrQuery_hl_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightMaxAlternateFieldLength,  SolrQuery_hl_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightFormatter,  SolrQuery_hl_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightFormatter,  SolrQuery_hl_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightSimplePre,  SolrQuery_hl_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightSimplePre,  SolrQuery_hl_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightSimplePost,  SolrQuery_hl_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightSimplePost,  SolrQuery_hl_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightFragmenter,  SolrQuery_hl_2_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightFragmenter,  SolrQuery_hl_get_1_0_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightUsePhraseHighlighter,  SolrQuery_hl_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightUsePhraseHighlighter,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightHighlightMultiTerm,  SolrQuery_hl_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightHighlightMultiTerm,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightRegexSlop,  SolrQuery_hl_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightRegexSlop,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightRegexPattern,  SolrQuery_hl_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightRegexPattern,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setHighlightRegexMaxAnalyzedChars,  SolrQuery_hl_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getHighlightRegexMaxAnalyzedChars,  Solr_no_args, ZEND_ACC_PUBLIC)

	/* StatsComponent */
	PHP_ME(SolrQuery, setStats,  SolrQuery_stats_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getStats,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, addStatsField,  SolrQuery_stats_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, removeStatsField,  SolrQuery_stats_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getStatsFields,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, addStatsFacet,  SolrQuery_stats_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, removeStatsFacet,  SolrQuery_stats_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getStatsFacets,  Solr_no_args, ZEND_ACC_PUBLIC)

	/* MoreLikeThis */
	PHP_ME(SolrQuery, setMlt,  SolrQuery_mlt_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getMlt,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setMltCount,  SolrQuery_mlt_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getMltCount,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, addMltField,  SolrQuery_mlt_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, removeMltField,  SolrQuery_mlt_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getMltFields,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, addMltQueryField,  SolrQuery_mlt_2_2_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, removeMltQueryField,  SolrQuery_mlt_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getMltQueryFields,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setMltMinTermFrequency,  SolrQuery_mlt_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getMltMinTermFrequency,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setMltMinDocFrequency,  SolrQuery_mlt_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getMltMinDocFrequency,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setMltMinWordLength,  SolrQuery_mlt_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getMltMinWordLength,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setMltMaxWordLength,  SolrQuery_mlt_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getMltMaxWordLength,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setMltMaxNumTokens,  SolrQuery_mlt_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getMltMaxNumTokens,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setMltMaxNumQueryTerms,  SolrQuery_mlt_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getMltMaxNumQueryTerms,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setMltBoost,  SolrQuery_mlt_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getMltBoost,  Solr_no_args, ZEND_ACC_PUBLIC)

	/* TermsComponent */
	PHP_ME(SolrQuery, setTerms,  SolrQuery_terms_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getTerms,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setTermsField,  SolrQuery_terms_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getTermsField,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setTermsLowerBound,  SolrQuery_terms_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getTermsLowerBound,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setTermsUpperBound,  SolrQuery_terms_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getTermsUpperBound,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setTermsIncludeLowerBound,  SolrQuery_terms_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getTermsIncludeLowerBound,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setTermsIncludeUpperBound,  SolrQuery_terms_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getTermsIncludeUpperBound,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setTermsMinCount,  SolrQuery_terms_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getTermsMinCount,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setTermsMaxCount,  SolrQuery_terms_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getTermsMaxCount,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setTermsPrefix,  SolrQuery_terms_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getTermsPrefix,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setTermsLimit,  SolrQuery_terms_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getTermsLimit,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setTermsReturnRaw,  SolrQuery_terms_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getTermsReturnRaw,  Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, setTermsSort,  SolrQuery_terms_1_1_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrQuery, getTermsSort,  Solr_no_args, ZEND_ACC_PUBLIC)

	/* TODO : TermVectorComponent */

	PHP_FE_END
};
/* }}} */

/* {{{ solr_response_methods. */
static zend_function_entry solr_response_methods[] = {
	PHP_ME(SolrResponse, getHttpStatus, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrResponse, getHttpStatusMessage, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrResponse, success, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrResponse, getRequestUrl, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrResponse, getRawRequestHeaders, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrResponse, getRawRequest, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrResponse, getRawResponseHeaders, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrResponse, getRawResponse, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrResponse, getDigestedResponse, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrResponse, setParseMode, SolrResponse_setParseMode_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrResponse, getResponse, Solr_no_args, ZEND_ACC_PUBLIC)
	PHP_ME(SolrResponse, getArrayResponse, Solr_no_args, ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

/* {{{ solr_query_response_methods. */
static zend_function_entry solr_query_response_methods[] = {
	SOLR_CTOR(SolrQueryResponse, __construct, Solr_no_args)
	SOLR_DTOR(SolrQueryResponse, __destruct, Solr_no_args)

	PHP_FE_END
};
/* }}} */

/* {{{ solr_update_response_methods. */
static zend_function_entry solr_update_response_methods[] = {
	SOLR_CTOR(SolrUpdateResponse, __construct, Solr_no_args)
	SOLR_DTOR(SolrUpdateResponse, __destruct, Solr_no_args)

	PHP_FE_END
};
/* }}} */

/* {{{ solr_ping_response_methods. */
static zend_function_entry solr_ping_response_methods[] = {
	SOLR_CTOR(SolrPingResponse, __construct, Solr_no_args)
	SOLR_DTOR(SolrPingResponse, __destruct, Solr_no_args)
	PHP_ME(SolrPingResponse, getResponse, Solr_no_args, ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

/* {{{ solr_generic_response_methods. */
static zend_function_entry solr_generic_response_methods[] = {
	SOLR_CTOR(SolrGenericResponse, __construct, Solr_no_args)
	SOLR_DTOR(SolrGenericResponse, __destruct, Solr_no_args)

	PHP_FE_END
};
/* }}} */

/* {{{ solr_utils_methods. */
static zend_function_entry solr_utils_methods[] = {
	PHP_ME(SolrUtils, escapeQueryChars, SolrUtils_escapeQueryChars_arg, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(SolrUtils, queryPhrase, SolrUtils_escapeQueryChars_arg, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(SolrUtils, digestXmlResponse, SolrUtils_digestXML_arg, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(SolrUtils, digestJsonResponse, SolrUtils_digestJson_arg, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(SolrUtils, getSolrVersion, Solr_no_args, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(SolrUtils, getSolrStats, Solr_no_args, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

	PHP_FE_END
};
/* }}} */

/* {{{ solr_module_deps  */
static zend_module_dep solr_module_deps[] = {
    ZEND_MOD_REQUIRED(PHP_LIBXML_EXTENSION_NAME)
    ZEND_MOD_REQUIRED(PHP_JSON_EXTENSION_NAME)
    ZEND_MOD_END
};
/* }}} */

/* {{{ solr_module_entry */
zend_module_entry solr_module_entry = {
	STANDARD_MODULE_HEADER_EX, NULL,
	solr_module_deps,
	PHP_SOLR_EXTENSION_NAME,
	solr_functions,
	PHP_MINIT(solr),
	PHP_MSHUTDOWN(solr),
	PHP_RINIT(solr),
	PHP_RSHUTDOWN(solr),
	PHP_MINFO(solr),
	PHP_SOLR_DOTTED_VERSION, /* The current extension version number. */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SOLR
ZEND_GET_MODULE(solr)
#endif

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(solr)
{

#ifdef ZTS
	/* As of ZE 2.2.0, this has to be NULL. */
	/* It causes a segmentation fault, if it points to an actual function */
	/* Probably a bug in the Zend Engine API */
	ts_allocate_dtor php_solr_globals_dtor  = NULL;
#endif

	zend_class_entry ce;

	memcpy(&solr_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&solr_document_field_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&solr_input_document_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&solr_client_object_handlers, &solr_input_document_object_handlers, sizeof(zend_object_handlers));
	memcpy(&solr_collapse_function_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	solr_collapse_function_object_handlers.clone_obj = solr_collapse_function_object_handler_clone;
	solr_input_document_object_handlers.clone_obj = solr_document_object_handler_clone;

	/* solr_object_handlers.read_property   = solr_object_read_property;   */
	solr_object_handlers.write_property  = solr_object_write_property;
	solr_object_handlers.write_dimension = solr_object_write_dimension;
	solr_object_handlers.unset_property  = solr_object_unset_property;
	solr_object_handlers.unset_dimension = solr_object_unset_dimension;

	solr_document_field_handlers.write_property = solr_document_field_write_property;
	solr_document_field_handlers.unset_property = solr_document_field_unset_property;

#ifdef ZTS
    ZEND_INIT_MODULE_GLOBALS(solr, php_solr_globals_ctor, php_solr_globals_dtor);
#else
    php_solr_globals_ctor(&solr_globals TSRMLS_CC);
#endif

    /* Register extension constants */
    solr_extension_register_constants(type, module_number TSRMLS_CC);

    /* Register the SolrObject class */
    INIT_CLASS_ENTRY(ce, PHP_SOLR_OBJECT_CLASSNAME, solr_object_methods);
    solr_ce_SolrObject = zend_register_internal_class(&ce TSRMLS_CC);
    solr_ce_SolrObject->ce_flags |= ZEND_ACC_FINAL;

    /* SolrObject implements ArrayAccess */
    zend_class_implements(solr_ce_SolrObject TSRMLS_CC, 1, solr_ce_ArrayAccess);

    /* Register the SolrDocument class */
    INIT_CLASS_ENTRY(ce, PHP_SOLR_DOCUMENT_CLASSNAME, solr_document_methods);
    solr_ce_SolrDocument = zend_register_internal_class(&ce TSRMLS_CC);
    solr_ce_SolrDocument->ce_flags |= ZEND_ACC_FINAL;

    /* This internal property will be used to map to this SolrDocument instance */
    zend_declare_property_long(solr_ce_SolrDocument, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) -1, 0L, ZEND_ACC_PRIVATE TSRMLS_CC);

    /* Register SolrDocument class constants */
    solr_document_register_class_constants(solr_ce_SolrDocument TSRMLS_CC);

    /* SolrDocument implements ArrayAccess, Iterator, Serializable */
    zend_class_implements(solr_ce_SolrDocument TSRMLS_CC, 3, solr_ce_ArrayAccess, solr_ce_Iterator, solr_ce_Serializable);

    /* Register the SolrDocumentField class */
    INIT_CLASS_ENTRY(ce, PHP_SOLR_DOCUMENT_FIELD_CLASSNAME, solr_document_field_methods);
    solr_ce_SolrDocumentField = zend_register_internal_class(&ce TSRMLS_CC);
    solr_ce_SolrDocumentField->ce_flags |= ZEND_ACC_FINAL;

    /* Register the name, boost and values properties */
    zend_declare_property_stringl(solr_ce_SolrDocumentField, SOLR_FIELD_NAME_PROPERTY_NAME, sizeof(SOLR_FIELD_NAME_PROPERTY_NAME)-1, SOLR_SPACE_STRING, sizeof(SOLR_SPACE_STRING)-1, ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_double(solr_ce_SolrDocumentField, SOLR_FIELD_BOOST_PROPERTY_NAME, sizeof(SOLR_FIELD_BOOST_PROPERTY_NAME)-1, 0.0f, ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_null(solr_ce_SolrDocumentField, SOLR_FIELD_VALUES_PROPERTY_NAME, sizeof(SOLR_FIELD_VALUES_PROPERTY_NAME)-1, ZEND_ACC_PUBLIC TSRMLS_CC);

    /* Register the SolrInputDocument class */
    INIT_CLASS_ENTRY(ce, PHP_SOLR_INPUT_DOCUMENT_CLASSNAME, solr_input_document_methods);
    solr_ce_SolrInputDocument = zend_register_internal_class(&ce TSRMLS_CC);
    solr_ce_SolrInputDocument->ce_flags |= ZEND_ACC_FINAL;

    /* This internal property will be used to map to this SolrDocument instance */
    zend_declare_property_long(solr_ce_SolrInputDocument, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) -1, 0L, ZEND_ACC_PRIVATE TSRMLS_CC);

    /* Register SolrInputDocument class constants */
    solr_input_document_register_class_constants(solr_ce_SolrInputDocument TSRMLS_CC);

    /* Register SolrClient Class */
    INIT_CLASS_ENTRY(ce, PHP_SOLR_CLIENT_CLASSNAME, solr_client_methods);
    solr_ce_SolrClient = zend_register_internal_class(&ce TSRMLS_CC);
    /* solr_ce_SolrClient->ce_flags |= ZEND_ACC_FINAL; */

    /* This internal property will be used to map to this SolrClient instance */
    zend_declare_property_long(solr_ce_SolrClient, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) -1, 0L, ZEND_ACC_PRIVATE TSRMLS_CC);

    /* Register SolrClient class constants */
    solr_client_register_class_constants(solr_ce_SolrClient TSRMLS_CC);

	/* Register the SolrParams class */
	INIT_CLASS_ENTRY(ce, PHP_SOLR_PARAMS_CLASSNAME, solr_params_methods);
	solr_ce_SolrParams = zend_register_internal_class(&ce TSRMLS_CC);
	solr_ce_SolrParams->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

	zend_class_implements(solr_ce_SolrParams TSRMLS_CC, 1, solr_ce_Serializable);

	/* This internal property will be used to map to this SolrParams instance */
    zend_declare_property_long(solr_ce_SolrParams, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) -1, 0L, ZEND_ACC_PROTECTED TSRMLS_CC);

    /* Register the SolrModifiableParams class */
	INIT_CLASS_ENTRY(ce, PHP_SOLR_MODIFIABLE_PARAMS_CLASSNAME, solr_modifiable_params_methods);
	solr_ce_SolrModifiableParams = zend_register_internal_class_ex(&ce, solr_ce_SolrParams);

    /* Register the SolrQuery class */
	INIT_CLASS_ENTRY(ce, PHP_SOLR_QUERY_CLASSNAME, solr_query_methods);
	solr_ce_SolrQuery = zend_register_internal_class_ex(&ce, solr_ce_SolrModifiableParams);
	init_solr_dismax_query(TSRMLS_C);
	solr_query_register_class_constants(solr_ce_SolrQuery TSRMLS_CC);

    /* Register the SolrCollapseFunction class */
    INIT_CLASS_ENTRY(ce, PHP_SOLR_COLLAPSE_FUNCTION_CLASSNAME, solr_collapse_function_methods);
    solr_ce_SolrCollapseFunction = zend_register_internal_class_ex(&ce, solr_ce_SolrCollapseFunction);

    zend_declare_property_long(solr_ce_SolrCollapseFunction, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME)-1, 0l, ZEND_ACC_PROTECTED TSRMLS_CC);
    solr_collapse_function_register_class_constants(solr_ce_SolrCollapseFunction TSRMLS_CC);

	/* Register the SolrResponse base class */
	INIT_CLASS_ENTRY(ce, PHP_SOLR_RESPONSE_CLASSNAME, solr_response_methods);
	solr_ce_SolrResponse = zend_register_internal_class(&ce TSRMLS_CC);
	solr_ce_SolrResponse->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

	/* Register all the properties for the SolrResponse object */
	solr_response_register_class_properties(solr_ce_SolrResponse TSRMLS_CC);

	/* Register all the constants for the SolrResponse object */
	solr_response_register_class_constants(solr_ce_SolrResponse TSRMLS_CC);

	/* Register the SolrQueryResponse class */
	INIT_CLASS_ENTRY(ce, PHP_SOLR_QUERY_RESPONSE_CLASSNAME, solr_query_response_methods);
	solr_ce_SolrQueryResponse = zend_register_internal_class_ex(&ce, solr_ce_SolrResponse);
	solr_ce_SolrQueryResponse->ce_flags |= ZEND_ACC_FINAL;

	/* Register the SolrUpdateResponse class */
	INIT_CLASS_ENTRY(ce, PHP_SOLR_UPDATE_RESPONSE_CLASSNAME, solr_update_response_methods);
	solr_ce_SolrUpdateResponse = zend_register_internal_class_ex(&ce, solr_ce_SolrResponse);
	solr_ce_SolrUpdateResponse->ce_flags |= ZEND_ACC_FINAL;

	/* Register the SolrPingResponse class */
	INIT_CLASS_ENTRY(ce, PHP_SOLR_PING_RESPONSE_CLASSNAME, solr_ping_response_methods);
	solr_ce_SolrPingResponse = zend_register_internal_class_ex(&ce, solr_ce_SolrResponse);
	solr_ce_SolrPingResponse->ce_flags |= ZEND_ACC_FINAL;

	/* Register the SolrGenericResponse class */
	INIT_CLASS_ENTRY(ce, PHP_SOLR_GENERIC_RESPONSE_CLASSNAME, solr_generic_response_methods);
	solr_ce_SolrGenericResponse = zend_register_internal_class_ex(&ce, solr_ce_SolrResponse);
	solr_ce_SolrGenericResponse->ce_flags |= ZEND_ACC_FINAL;

	/* Register the SolrUtils class */
	INIT_CLASS_ENTRY(ce, PHP_SOLR_UTILS_CLASSNAME, solr_utils_methods);
	solr_ce_SolrUtils = zend_register_internal_class(&ce TSRMLS_CC);
	solr_ce_SolrUtils->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

	/* Register the SolrException class */
	INIT_CLASS_ENTRY(ce, PHP_SOLR_EXCEPTION_CLASSNAME, solr_exception_methods);
	solr_ce_SolrException = zend_register_internal_class_ex(&ce, solr_ce_Exception);

	solr_exception_register_class_properties(solr_ce_SolrException TSRMLS_CC);

	INIT_CLASS_ENTRY(ce, PHP_SOLR_ILLEGAL_OPERATION_EXCEPTION_CLASSNAME, solr_illegal_operation_exception_methods);
	solr_ce_SolrIllegalOperationException = zend_register_internal_class_ex(&ce, solr_ce_SolrException);

	INIT_CLASS_ENTRY(ce, PHP_SOLR_ILLEGAL_ARGUMENT_EXCEPTION_CLASSNAME, solr_illegal_argument_exception_methods);
	solr_ce_SolrIllegalArgumentException = zend_register_internal_class_ex(&ce, solr_ce_SolrException);

	INIT_CLASS_ENTRY(ce, PHP_SOLR_CLIENT_EXCEPTION_CLASSNAME, solr_client_exception_methods);
	solr_ce_SolrClientException = zend_register_internal_class_ex(&ce, solr_ce_SolrException);

	INIT_CLASS_ENTRY(ce, PHP_SOLR_SERVER_EXCEPTION_CLASSNAME, solr_server_exception_methods);
	solr_ce_SolrServerException = zend_register_internal_class_ex(&ce, solr_ce_SolrException);

	INIT_CLASS_ENTRY(ce, PHP_SOLR_MISSING_MANDATORY_PARAMETER_EXCEPTION_CLASSNAME, NULL);
	solr_ce_SolrMissingMandatoryParameterException = zend_register_internal_class_ex(&ce, solr_ce_SolrException);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(solr)
{
	zend_bool persistent   = SOLR_HASHTABLE_PERSISTENT;

	/* Initial size of the HashTable */
	uint nSize             = SOLR_INITIAL_HASH_TABLE_SIZE;

	ALLOC_HASHTABLE(SOLR_GLOBAL(documents));
	ALLOC_HASHTABLE(SOLR_GLOBAL(clients));
	ALLOC_HASHTABLE(SOLR_GLOBAL(params));
	ALLOC_HASHTABLE(SOLR_GLOBAL(functions));

	/* Initialize the HashTable for directory for SolrInputDocuments */
	zend_hash_init(SOLR_GLOBAL(documents), nSize, NULL, solr_destroy_document, persistent);
	zend_hash_init(SOLR_GLOBAL(clients), nSize, NULL, solr_destroy_client, persistent);
	/* Initialize the HashTable for directory of SolrParams */
	zend_hash_init(SOLR_GLOBAL(params), nSize, NULL, solr_destroy_params, persistent);

	zend_hash_init(SOLR_GLOBAL(functions), nSize, NULL, solr_destroy_function, persistent);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION */
PHP_RSHUTDOWN_FUNCTION(solr)
{
	zend_hash_destroy(SOLR_GLOBAL(documents));
	zend_hash_destroy(SOLR_GLOBAL(clients));
	zend_hash_destroy(SOLR_GLOBAL(params));
	zend_hash_destroy(SOLR_GLOBAL(functions));

	FREE_HASHTABLE(SOLR_GLOBAL(documents));
	FREE_HASHTABLE(SOLR_GLOBAL(clients));
	FREE_HASHTABLE(SOLR_GLOBAL(params));
	FREE_HASHTABLE(SOLR_GLOBAL(functions));

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(solr)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(solr)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Solr Support", "enabled");
	php_info_print_table_row(2, "Version", PHP_SOLR_DOTTED_VERSION);
	php_info_print_table_row(2, "Last Build Date", __DATE__);
	php_info_print_table_row(2, "Last Build Time", __TIME__);

	php_info_print_table_end();
}
/* }}} */

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

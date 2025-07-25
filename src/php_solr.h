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
   | Authors:                                                             |
   |          Israel Ekpo <iekpo@php.net>                                 |
   |          Omar Shaban <omars@php.net>                                 |
   +----------------------------------------------------------------------+
*/

#ifndef SOLRCLIENT_H
#define SOLRCLIENT_H

/* #define SOLR_MEM_DEBUG 1 */

#include <main/php.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_SOLR

#include <time.h>
#include <locale.h>

#include <main/php_ini.h>
#include <main/SAPI.h>
#include <main/snprintf.h>

#include <ext/standard/info.h>
#include <ext/standard/url.h>
#include <ext/standard/php_var.h>
#include <ext/standard/php_string.h>
#include <ext/standard/base64.h>
#include <ext/pcre/php_pcre.h>


#include <Zend/zend_extensions.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>
#include <Zend/zend_modules.h>
#include <Zend/zend_API.h>

#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlstring.h>

#include <pecl-compat/compat.h>

extern zend_module_entry solr_module_entry;

#define phpext_solr_ptr &solr_module_entry

/* {{{ Startup, Shutdown, Activation, Deactivation and Info functions */
PHP_MINIT_FUNCTION(solr); 		/* Module Startup Function */
PHP_MSHUTDOWN_FUNCTION(solr);	/* Module Shutdown Function */
PHP_RINIT_FUNCTION(solr);		/* Request Activation Function */
PHP_RSHUTDOWN_FUNCTION(solr);	/* Request Deactivation Function */
PHP_MINFO_FUNCTION(solr);		/* Module Information Display Function */
/* }}} */

#ifdef ZTS
#include <TSRM/TSRM.h>
#endif

/* List of constants */
#include "solr_constants.h"

/* List of types */
#include "solr_types.h"

#ifdef ZTS
# define SOLR_GLOBAL(v) TSRMG(solr_globals_id, zend_solr_globals *, v)
#else
# define SOLR_GLOBAL(v) (solr_globals.v)
#endif

#include <ext/json/php_json.h>

#include "php_solr_api.h"


/* {{{ Variables declared elsewhere */
ZEND_EXTERN_MODULE_GLOBALS(solr)
/* ZEND_EXTERN_MODULE_GLOBALS(json) */

extern zend_class_entry *solr_ce_SolrObject;
extern zend_class_entry *solr_ce_SolrInputDocument;
extern zend_class_entry *solr_ce_SolrDocument;
extern zend_class_entry *solr_ce_SolrDocumentField;
extern zend_class_entry *solr_ce_SolrClient;
extern zend_class_entry *solr_ce_SolrParams;
extern zend_class_entry *solr_ce_SolrModifiableParams;
extern zend_class_entry *solr_ce_SolrCollapseFunction;
extern zend_class_entry *solr_ce_SolrQuery;
extern zend_class_entry *solr_ce_SolrResponse;
extern zend_class_entry *solr_ce_SolrQueryResponse;
extern zend_class_entry *solr_ce_SolrUpdateResponse;
extern zend_class_entry *solr_ce_SolrPingResponse;
extern zend_class_entry *solr_ce_SolrGenericResponse;
extern zend_class_entry *solr_ce_SolrUtils;
extern zend_class_entry *solr_ce_SolrException;
extern zend_class_entry *solr_ce_SolrIllegalOperationException;
extern zend_class_entry *solr_ce_SolrIllegalArgumentException;
extern zend_class_entry *solr_ce_SolrClientException;
extern zend_class_entry *solr_ce_SolrServerException;
extern zend_class_entry *solr_ce_SolrMissingMandatoryParameterException;

extern ZEND_API zend_class_entry *zend_ce_serializable;
extern ZEND_API zend_class_entry *zend_ce_arrayaccess;
extern ZEND_API zend_class_entry *zend_ce_iterator;

/* {{{ Aliases for external class entries */
#define solr_ce_Serializable zend_ce_serializable
#define solr_ce_ArrayAccess  zend_ce_arrayaccess
#define solr_ce_Iterator     zend_ce_iterator
#define solr_ce_Exception    zend_ce_exception
/* }}} */

extern zend_object_handlers solr_object_handlers;
extern zend_object_handlers solr_document_field_handlers;
extern zend_object_handlers solr_input_document_object_handlers;
extern zend_object_handlers solr_client_object_handlers;
extern zend_object_handlers solr_response_object_handlers;
extern zend_object_handlers solr_collapse_function_object_handlers;
/* }}} */

/******************************************************************************/
/** DECLARATIONS FOR EXTENSION METHODS  AND FUNCTIONS                        **/
/******************************************************************************/

/* {{{ Extension functions */
PHP_FUNCTION(solr_get_version);
/* }}} */

/* {{{ SolrObject methods */
PHP_METHOD(SolrObject, __construct);
PHP_METHOD(SolrObject, __destruct);
PHP_METHOD(SolrObject, __set);
PHP_METHOD(SolrObject, __get);
PHP_METHOD(SolrObject, __isset);
PHP_METHOD(SolrObject, __unset);
PHP_METHOD(SolrObject, offsetSet);
PHP_METHOD(SolrObject, offsetGet);
PHP_METHOD(SolrObject, offsetExists);
PHP_METHOD(SolrObject, offsetUnset);
PHP_METHOD(SolrObject, getPropertyNames);
/* }}} */

/* {{{ SolException object methods */
PHP_METHOD(SolrException, getInternalInfo);
PHP_METHOD(SolrClientException, getInternalInfo);
PHP_METHOD(SolrIllegalOperationException, getInternalInfo);
PHP_METHOD(SolrIllegalArgumentException, getInternalInfo);
PHP_METHOD(SolrServerException, getInternalInfo);
/* }}} */

/* {{{ SolrDocument methods declarations */
PHP_METHOD(SolrDocument, __construct);
PHP_METHOD(SolrDocument, __destruct);
PHP_METHOD(SolrDocument, __clone);
PHP_METHOD(SolrDocument, __get);
PHP_METHOD(SolrDocument, __set);
PHP_METHOD(SolrDocument, __isset);
PHP_METHOD(SolrDocument, __unset);

/* Methods from Serializable */
PHP_METHOD(SolrDocument, serialize);
PHP_METHOD(SolrDocument, unserialize);
#if PHP_VERSION_ID >= 80100
PHP_METHOD(SolrDocument, __serialize);
PHP_METHOD(SolrDocument, __unserialize);
#endif

/* Methods from ArrayAccess */
PHP_METHOD(SolrDocument, offsetExists);
PHP_METHOD(SolrDocument, offsetGet);
PHP_METHOD(SolrDocument, offsetSet);
PHP_METHOD(SolrDocument, offsetUnset);

/* Methods from Iterator */
PHP_METHOD(SolrDocument, current);
PHP_METHOD(SolrDocument, key);
PHP_METHOD(SolrDocument, next);
PHP_METHOD(SolrDocument, rewind);
PHP_METHOD(SolrDocument, valid);

PHP_METHOD(SolrDocument, clear);
PHP_METHOD(SolrDocument, addField);
PHP_METHOD(SolrDocument, getFieldNames);
PHP_METHOD(SolrDocument, getFieldCount);
PHP_METHOD(SolrDocument, getField);
PHP_METHOD(SolrDocument, toArray);
PHP_METHOD(SolrDocument, fieldExists);
PHP_METHOD(SolrDocument, deleteField);
PHP_METHOD(SolrDocument, sort);
PHP_METHOD(SolrDocument, merge);
PHP_METHOD(SolrDocument, getInputDocument);
PHP_METHOD(SolrDocument, hasChildDocuments);
PHP_METHOD(SolrDocument, getChildDocuments);
PHP_METHOD(SolrDocument, getChildDocumentsCount);
/* }}} */

/* {{{ SolrExtractRequest methods */
PHP_METHOD(SolrExtractRequest, __construct);
PHP_METHOD(SolrExtractRequest, createFromFile);
PHP_METHOD(SolrExtractRequest, createFromStream);
PHP_METHOD(SolrExtractRequest, __destruct);
PHP_METHOD(SolrExtractRequest, __clone);
PHP_METHOD(SolrExtractRequest, __sleep);
PHP_METHOD(SolrExtractRequest, __wakeup);

/* }}} */

/* {{{ SolrDocumentField methods */
PHP_METHOD(SolrDocumentField, __construct);
PHP_METHOD(SolrDocumentField, __destruct);
/* }}} */

/* {{{ SolrInputDocument methods declarations */
PHP_METHOD(SolrInputDocument, __construct);
PHP_METHOD(SolrInputDocument, __destruct);
PHP_METHOD(SolrInputDocument, __clone);
PHP_METHOD(SolrInputDocument, __sleep);
PHP_METHOD(SolrInputDocument, __wakeup);
PHP_METHOD(SolrInputDocument, setBoost);
PHP_METHOD(SolrInputDocument, getBoost);
PHP_METHOD(SolrInputDocument, clear);
PHP_METHOD(SolrInputDocument, addField);
PHP_METHOD(SolrInputDocument, updateField);
PHP_METHOD(SolrInputDocument, setFieldBoost);
PHP_METHOD(SolrInputDocument, getFieldBoost);
PHP_METHOD(SolrInputDocument, getFieldNames);
PHP_METHOD(SolrInputDocument, getFieldCount);
PHP_METHOD(SolrInputDocument, getField);
PHP_METHOD(SolrInputDocument, toArray);
PHP_METHOD(SolrInputDocument, fieldExists);
PHP_METHOD(SolrInputDocument, deleteField);
PHP_METHOD(SolrInputDocument, sort);
PHP_METHOD(SolrInputDocument, merge);
PHP_METHOD(SolrInputDocument, addChildDocument);
PHP_METHOD(SolrInputDocument, getChildDocuments);
PHP_METHOD(SolrInputDocument, hasChildDocuments);
PHP_METHOD(SolrInputDocument, getChildDocumentsCount);
PHP_METHOD(SolrInputDocument, addChildDocuments);
PHP_METHOD(SolrInputDocument, setVersion);
PHP_METHOD(SolrInputDocument, getVersion);
/* }}} */

/* {{{ SolrClient methods declarations */
PHP_METHOD(SolrClient, __construct);
PHP_METHOD(SolrClient, __destruct);
PHP_METHOD(SolrClient, __sleep);
PHP_METHOD(SolrClient, __wakeup);
PHP_METHOD(SolrClient, __clone);
PHP_METHOD(SolrClient, query);
PHP_METHOD(SolrClient, getOptions);
PHP_METHOD(SolrClient, getDebug);
PHP_METHOD(SolrClient, addDocument);
PHP_METHOD(SolrClient, addDocuments);
PHP_METHOD(SolrClient, setServlet);
PHP_METHOD(SolrClient, setResponseWriter);
PHP_METHOD(SolrClient, request);
PHP_METHOD(SolrClient, sendUpdateStream);
PHP_METHOD(SolrClient, ping);
PHP_METHOD(SolrClient, system);
PHP_METHOD(SolrClient, threads);
PHP_METHOD(SolrClient, deleteById);
PHP_METHOD(SolrClient, deleteByIds);
PHP_METHOD(SolrClient, deleteByQuery);
PHP_METHOD(SolrClient, deleteByQueries);
PHP_METHOD(SolrClient, getById);
PHP_METHOD(SolrClient, getByIds);
PHP_METHOD(SolrClient, optimize);
PHP_METHOD(SolrClient, commit);
PHP_METHOD(SolrClient, rollback);
/* }}} */

/* {{{ SolrParams methods declarations */
PHP_METHOD(SolrParams, setParam);	/* Parameter can only accept one value */
PHP_METHOD(SolrParams, addParam);	/* Parameter can accept more than one value */
PHP_METHOD(SolrParams, getParams);	/* Retrieves the parameters and their values */
PHP_METHOD(SolrParams, getParam);	/* Retrieves a parameter value */
PHP_METHOD(SolrParams, __toString); /* Returns a string representation of the object */
PHP_METHOD(SolrParams, toString);	/* Returns a string representation of the object */
PHP_METHOD(SolrParams, getPreparedParams); /* Returns the prepared parameters */
PHP_METHOD(SolrParams, serialize);	 /* used by serialize() */
PHP_METHOD(SolrParams, unserialize);	/* used by unserialize() */
#if PHP_VERSION_ID >= 80100
PHP_METHOD(SolrParams, __serialize);	 /* used by serialize() */
PHP_METHOD(SolrParams, __unserialize);	 /* used by serialize() */
#endif
PHP_METHOD(SolrParams, __clone); /* Used to enforce the cloning of SolrParams is currently unsupported */
/* }}} */

/* {{{ SolrModifiableParams methods declarations */
PHP_METHOD(SolrModifiableParams, __construct);
PHP_METHOD(SolrModifiableParams, __destruct);
/* }}} */

/* {{{ SolrQuery methods declarations */

/* Constructor and Destructor */
PHP_METHOD(SolrQuery, __construct);
PHP_METHOD(SolrQuery, __destruct);

/* CommonQueryParameters  */
PHP_METHOD(SolrQuery, setQuery);
PHP_METHOD(SolrQuery, getQuery);
PHP_METHOD(SolrQuery, setStart);
PHP_METHOD(SolrQuery, getStart);
PHP_METHOD(SolrQuery, setRows);
PHP_METHOD(SolrQuery, getRows);
PHP_METHOD(SolrQuery, addField);
PHP_METHOD(SolrQuery, removeField);
PHP_METHOD(SolrQuery, getFields);
PHP_METHOD(SolrQuery, addSortField);
PHP_METHOD(SolrQuery, removeSortField);
PHP_METHOD(SolrQuery, getSortFields);
PHP_METHOD(SolrQuery, addFilterQuery);
PHP_METHOD(SolrQuery, removeFilterQuery);
PHP_METHOD(SolrQuery, getFilterQueries);
PHP_METHOD(SolrQuery, setShowDebugInfo);
PHP_METHOD(SolrQuery, setExplainOther);
PHP_METHOD(SolrQuery, setTimeAllowed);
PHP_METHOD(SolrQuery, getTimeAllowed);
PHP_METHOD(SolrQuery, setOmitHeader);

/* CoreQueryParameters */
PHP_METHOD(SolrQuery, setEchoHandler);
PHP_METHOD(SolrQuery, setEchoParams);

/* SimpleFacetParameters */
PHP_METHOD(SolrQuery, setFacet);
PHP_METHOD(SolrQuery, getFacet);
PHP_METHOD(SolrQuery, addFacetField);
PHP_METHOD(SolrQuery, removeFacetField);
PHP_METHOD(SolrQuery, getFacetFields);
PHP_METHOD(SolrQuery, addFacetQuery);
PHP_METHOD(SolrQuery, removeFacetQuery);
PHP_METHOD(SolrQuery, getFacetQueries);
PHP_METHOD(SolrQuery, setFacetPrefix);
PHP_METHOD(SolrQuery, getFacetPrefix);
PHP_METHOD(SolrQuery, setFacetSort);
PHP_METHOD(SolrQuery, getFacetSort);
PHP_METHOD(SolrQuery, setFacetLimit);
PHP_METHOD(SolrQuery, getFacetLimit);
PHP_METHOD(SolrQuery, setFacetOffset);
PHP_METHOD(SolrQuery, getFacetOffset);
PHP_METHOD(SolrQuery, setFacetMinCount);
PHP_METHOD(SolrQuery, getFacetMinCount);
PHP_METHOD(SolrQuery, setFacetMissing);
PHP_METHOD(SolrQuery, getFacetMissing);
PHP_METHOD(SolrQuery, setFacetMethod);
PHP_METHOD(SolrQuery, getFacetMethod);
PHP_METHOD(SolrQuery, setFacetEnumCacheMinDefaultFrequency);

/* Date facet parameters */
PHP_METHOD(SolrQuery, addFacetDateField);
PHP_METHOD(SolrQuery, removeFacetDateField);
PHP_METHOD(SolrQuery, getFacetDateFields);
PHP_METHOD(SolrQuery, setFacetDateStart);
PHP_METHOD(SolrQuery, getFacetDateStart);
PHP_METHOD(SolrQuery, setFacetDateEnd);
PHP_METHOD(SolrQuery, getFacetDateEnd);
PHP_METHOD(SolrQuery, setFacetDateGap);
PHP_METHOD(SolrQuery, getFacetDateGap);
PHP_METHOD(SolrQuery, setFacetDateHardEnd);
PHP_METHOD(SolrQuery, getFacetDateHardEnd);
PHP_METHOD(SolrQuery, addFacetDateOther);
PHP_METHOD(SolrQuery, removeFacetDateOther);
PHP_METHOD(SolrQuery, getFacetDateOther);

/* GroupParameters */
PHP_METHOD(SolrQuery, setGroup);
PHP_METHOD(SolrQuery, getGroup);
PHP_METHOD(SolrQuery, addGroupField);
PHP_METHOD(SolrQuery, getGroupFields);
PHP_METHOD(SolrQuery, addGroupFunction);
PHP_METHOD(SolrQuery, getGroupFunctions);
PHP_METHOD(SolrQuery, addGroupQuery);
PHP_METHOD(SolrQuery, getGroupQueries);
PHP_METHOD(SolrQuery, setGroupLimit);
PHP_METHOD(SolrQuery, getGroupLimit);
PHP_METHOD(SolrQuery, setGroupOffset);
PHP_METHOD(SolrQuery, getGroupOffset);
PHP_METHOD(SolrQuery, addGroupSortField);
PHP_METHOD(SolrQuery, getGroupSortFields);
PHP_METHOD(SolrQuery, setGroupFormat);
PHP_METHOD(SolrQuery, getGroupFormat);
PHP_METHOD(SolrQuery, setGroupMain);
PHP_METHOD(SolrQuery, getGroupMain);
PHP_METHOD(SolrQuery, setGroupNGroups);
PHP_METHOD(SolrQuery, getGroupNGroups);
PHP_METHOD(SolrQuery, setGroupTruncate);
PHP_METHOD(SolrQuery, getGroupTruncate);
PHP_METHOD(SolrQuery, setGroupFacet);
PHP_METHOD(SolrQuery, getGroupFacet);
PHP_METHOD(SolrQuery, setGroupCachePercent);
PHP_METHOD(SolrQuery, getGroupCachePercent);

/* Collapse */
PHP_METHOD(SolrQuery, collapse);

/* Expand Parameters */
PHP_METHOD(SolrQuery, setExpand);
PHP_METHOD(SolrQuery, getExpand);
PHP_METHOD(SolrQuery, addExpandSortField);
PHP_METHOD(SolrQuery, removeExpandSortField);
PHP_METHOD(SolrQuery, getExpandSortFields);
PHP_METHOD(SolrQuery, setExpandRows);
PHP_METHOD(SolrQuery, getExpandRows);
PHP_METHOD(SolrQuery, setExpandQuery);
PHP_METHOD(SolrQuery, getExpandQuery);
PHP_METHOD(SolrQuery, addExpandFilterQuery);
PHP_METHOD(SolrQuery, removeExpandFilterQuery);
PHP_METHOD(SolrQuery, getExpandFilterQueries);

/* HighlightingParameters */
PHP_METHOD(SolrQuery, setHighlight);
PHP_METHOD(SolrQuery, getHighlight);
PHP_METHOD(SolrQuery, setHighlightQuery);
PHP_METHOD(SolrQuery, getHighlightQuery);
PHP_METHOD(SolrQuery, addHighlightField);
PHP_METHOD(SolrQuery, removeHighlightField);
PHP_METHOD(SolrQuery, getHighlightFields);
PHP_METHOD(SolrQuery, setHighlightSnippets);
PHP_METHOD(SolrQuery, getHighlightSnippets);
PHP_METHOD(SolrQuery, setHighlightFragsize);
PHP_METHOD(SolrQuery, getHighlightFragsize);
PHP_METHOD(SolrQuery, setHighlightMergeContiguous);
PHP_METHOD(SolrQuery, getHighlightMergeContiguous);
PHP_METHOD(SolrQuery, setHighlightRequireFieldMatch);
PHP_METHOD(SolrQuery, getHighlightRequireFieldMatch);
PHP_METHOD(SolrQuery, setHighlightMaxAnalyzedChars);
PHP_METHOD(SolrQuery, getHighlightMaxAnalyzedChars);
PHP_METHOD(SolrQuery, setHighlightAlternateField);
PHP_METHOD(SolrQuery, getHighlightAlternateField);
PHP_METHOD(SolrQuery, setHighlightMaxAlternateFieldLength);
PHP_METHOD(SolrQuery, getHighlightMaxAlternateFieldLength);
PHP_METHOD(SolrQuery, setHighlightFormatter);
PHP_METHOD(SolrQuery, getHighlightFormatter);
PHP_METHOD(SolrQuery, setHighlightSimplePre);
PHP_METHOD(SolrQuery, getHighlightSimplePre);
PHP_METHOD(SolrQuery, setHighlightSimplePost);
PHP_METHOD(SolrQuery, getHighlightSimplePost);
PHP_METHOD(SolrQuery, setHighlightFragmenter);
PHP_METHOD(SolrQuery, getHighlightFragmenter);
PHP_METHOD(SolrQuery, setHighlightUsePhraseHighlighter);
PHP_METHOD(SolrQuery, getHighlightUsePhraseHighlighter);
PHP_METHOD(SolrQuery, setHighlightHighlightMultiTerm);
PHP_METHOD(SolrQuery, getHighlightHighlightMultiTerm);
PHP_METHOD(SolrQuery, setHighlightRegexSlop);
PHP_METHOD(SolrQuery, getHighlightRegexSlop);
PHP_METHOD(SolrQuery, setHighlightRegexPattern);
PHP_METHOD(SolrQuery, getHighlightRegexPattern);
PHP_METHOD(SolrQuery, setHighlightRegexMaxAnalyzedChars);
PHP_METHOD(SolrQuery, getHighlightRegexMaxAnalyzedChars);

/* StatsComponent */
PHP_METHOD(SolrQuery, setStats);
PHP_METHOD(SolrQuery, getStats);
PHP_METHOD(SolrQuery, addStatsField);
PHP_METHOD(SolrQuery, removeStatsField);
PHP_METHOD(SolrQuery, getStatsFields);
PHP_METHOD(SolrQuery, addStatsFacet);
PHP_METHOD(SolrQuery, removeStatsFacet);
PHP_METHOD(SolrQuery, getStatsFacets);

/* MoreLikeThis */
PHP_METHOD(SolrQuery, setMlt);
PHP_METHOD(SolrQuery, getMlt);
PHP_METHOD(SolrQuery, setMltCount);
PHP_METHOD(SolrQuery, getMltCount);
PHP_METHOD(SolrQuery, addMltField);
PHP_METHOD(SolrQuery, removeMltField);
PHP_METHOD(SolrQuery, getMltFields);
PHP_METHOD(SolrQuery, addMltQueryField);
PHP_METHOD(SolrQuery, removeMltQueryField);
PHP_METHOD(SolrQuery, getMltQueryFields);
PHP_METHOD(SolrQuery, setMltMinTermFrequency);
PHP_METHOD(SolrQuery, getMltMinTermFrequency);
PHP_METHOD(SolrQuery, setMltMinDocFrequency);
PHP_METHOD(SolrQuery, getMltMinDocFrequency);
PHP_METHOD(SolrQuery, setMltMinWordLength);
PHP_METHOD(SolrQuery, getMltMinWordLength);
PHP_METHOD(SolrQuery, setMltMaxWordLength);
PHP_METHOD(SolrQuery, getMltMaxWordLength);
PHP_METHOD(SolrQuery, setMltMaxNumTokens);
PHP_METHOD(SolrQuery, getMltMaxNumTokens);
PHP_METHOD(SolrQuery, setMltMaxNumQueryTerms);
PHP_METHOD(SolrQuery, getMltMaxNumQueryTerms);
PHP_METHOD(SolrQuery, setMltBoost);
PHP_METHOD(SolrQuery, getMltBoost);

/* TermsComponent */
PHP_METHOD(SolrQuery, setTerms);
PHP_METHOD(SolrQuery, getTerms);
PHP_METHOD(SolrQuery, setTermsField);
PHP_METHOD(SolrQuery, getTermsField);
PHP_METHOD(SolrQuery, setTermsLowerBound);
PHP_METHOD(SolrQuery, getTermsLowerBound);
PHP_METHOD(SolrQuery, setTermsUpperBound);
PHP_METHOD(SolrQuery, getTermsUpperBound);
PHP_METHOD(SolrQuery, setTermsIncludeLowerBound);
PHP_METHOD(SolrQuery, getTermsIncludeLowerBound);
PHP_METHOD(SolrQuery, setTermsIncludeUpperBound);
PHP_METHOD(SolrQuery, getTermsIncludeUpperBound);
PHP_METHOD(SolrQuery, setTermsMinCount);
PHP_METHOD(SolrQuery, getTermsMinCount);
PHP_METHOD(SolrQuery, setTermsMaxCount);
PHP_METHOD(SolrQuery, getTermsMaxCount);
PHP_METHOD(SolrQuery, setTermsPrefix);
PHP_METHOD(SolrQuery, getTermsPrefix);
PHP_METHOD(SolrQuery, setTermsLimit);
PHP_METHOD(SolrQuery, getTermsLimit);
PHP_METHOD(SolrQuery, setTermsReturnRaw);
PHP_METHOD(SolrQuery, getTermsReturnRaw);
PHP_METHOD(SolrQuery, setTermsSort);
PHP_METHOD(SolrQuery, getTermsSort);

/* TODO : TermVectorComponent */
/* {{{ TermVectorComponent methods not yet defined */
PHP_METHOD(SolrQuery, setTermVector);
PHP_METHOD(SolrQuery, setTermVectorTermFrequency);
PHP_METHOD(SolrQuery, setTermVectorDocFrequency);
PHP_METHOD(SolrQuery, setTermVectorPositions);
PHP_METHOD(SolrQuery, setTermVectorOffsets);
PHP_METHOD(SolrQuery, setTermVectorTfIdfProduct);
PHP_METHOD(SolrQuery, setTermVectorAll);
PHP_METHOD(SolrQuery, addTermVectorField);
PHP_METHOD(SolrQuery, addTermVectorLuceneDocId);
/* }}} */

/* }}} */

/* {{{ SolrResponse methods declarations */
PHP_METHOD(SolrResponse, getHttpStatus);
PHP_METHOD(SolrResponse, getHttpStatusMessage);
PHP_METHOD(SolrResponse, success);
PHP_METHOD(SolrResponse, getRequestUrl);
PHP_METHOD(SolrResponse, getRawRequestHeaders);
PHP_METHOD(SolrResponse, getRawRequest);
PHP_METHOD(SolrResponse, getRawResponseHeaders);
PHP_METHOD(SolrResponse, getRawResponse);
PHP_METHOD(SolrResponse, getDigestedResponse);
PHP_METHOD(SolrResponse, setParseMode);
PHP_METHOD(SolrResponse, getArrayResponse);
PHP_METHOD(SolrResponse, getResponse);
/* }}} */

/* {{{ SolrQueryResponse methods */
PHP_METHOD(SolrQueryResponse, __construct);
PHP_METHOD(SolrQueryResponse, __destruct);
/* }}} */

/* {{{ SolrUpdateResponse methods */
PHP_METHOD(SolrUpdateResponse, __construct);
PHP_METHOD(SolrUpdateResponse, __destruct);
/* }}} */

/* {{{ SolrPingResponse methods declarations */
PHP_METHOD(SolrPingResponse, __construct);
PHP_METHOD(SolrPingResponse, __destruct);
PHP_METHOD(SolrPingResponse, getResponse);
/* }}} */

/* {{{ SolrGenericResponse methods */
PHP_METHOD(SolrGenericResponse, __construct);
PHP_METHOD(SolrGenericResponse, __destruct);
/* }}} */

/* {{{ SolrCollapseFunction methods */
PHP_METHOD(SolrCollapseFunction, __construct);
PHP_METHOD(SolrCollapseFunction, __destruct);
PHP_METHOD(SolrCollapseFunction, setField);
PHP_METHOD(SolrCollapseFunction, getField);

PHP_METHOD(SolrCollapseFunction, setMin);
PHP_METHOD(SolrCollapseFunction, getMin);

PHP_METHOD(SolrCollapseFunction, setMax);
PHP_METHOD(SolrCollapseFunction, getMax);

PHP_METHOD(SolrCollapseFunction, setNullPolicy);
PHP_METHOD(SolrCollapseFunction, getNullPolicy);

PHP_METHOD(SolrCollapseFunction, setHint);
PHP_METHOD(SolrCollapseFunction, getHint);

PHP_METHOD(SolrCollapseFunction, setSize);
PHP_METHOD(SolrCollapseFunction, getSize);
PHP_METHOD(SolrCollapseFunction, __toString);

PHP_METHOD(SolrCollapseFunction, __sleep);
PHP_METHOD(SolrCollapseFunction, __wakeup);

/* }}} */

/* {{{ SolrUtils methods declarations */
PHP_METHOD(SolrUtils, escapeQueryChars);
PHP_METHOD(SolrUtils, queryPhrase);
PHP_METHOD(SolrUtils, digestXmlResponse);
PHP_METHOD(SolrUtils, digestJsonResponse);
PHP_METHOD(SolrUtils, getSolrVersion);
PHP_METHOD(SolrUtils, getSolrStats);
/* }}} */

/******************************************************************************/
/** DECLARATIONS FOR HELPERS AND EXTENSION-SPECIFIC FUNCTIONS                **/
/******************************************************************************/

/* {{{ HTTP request function declarations */
size_t solr_curl_write(solr_char_t *data, size_t size, size_t nmemb, void *ctx);
size_t solr_curl_write_header(solr_char_t *data, size_t size, size_t nmemb, void *ctx);
int solr_curl_debug_callback(CURL *curl_handle, curl_infotype infotype, solr_char_t *debug_data, size_t size, void *ctx);

PHP_SOLR_API int solr_init_options(solr_client_options_t *options);
PHP_SOLR_API int solr_init_handle(solr_curl_t *sch, solr_client_options_t *options);
PHP_SOLR_API int solr_make_request(solr_client_t *client, solr_request_type_t request_type);
PHP_SOLR_API int solr_make_update_stream_request(solr_client_t *client, solr_ustream_t* stream_data, solr_string_t *request_params);
PHP_SOLR_API void solr_free_handle(solr_curl_t *sch);
PHP_SOLR_API void solr_free_option(solr_client_options_t *options);

/* }}} */

PHP_SOLR_API void solr_extension_register_constants(int type, int module_number);
PHP_SOLR_API void solr_document_register_class_constants(zend_class_entry *ce);
PHP_SOLR_API void solr_extract_register_class_constants(zend_class_entry *ce);
PHP_SOLR_API void solr_client_register_class_constants(zend_class_entry *ce);
PHP_SOLR_API void solr_query_register_class_constants(zend_class_entry *ce);
PHP_SOLR_API void solr_collapse_function_register_class_constants(zend_class_entry *ce);
PHP_SOLR_API void solr_response_register_class_properties(zend_class_entry *ce);
PHP_SOLR_API void solr_response_register_class_constants(zend_class_entry *ce);
PHP_SOLR_API void solr_exception_register_class_properties(zend_class_entry *ce);
PHP_SOLR_API void solr_input_document_register_class_constants(zend_class_entry *ce);

PHP_SOLR_API void solr_set_response_object_properties(zend_class_entry *scope, zval *response_object, const solr_client_t *client, const solr_string_t *request_url, zend_bool success);
PHP_SOLR_API void solr_throw_exception_ex(zend_class_entry *exception_ce, long code, const char *filename, int file_line, const char *function_name, char *format, ...);
PHP_SOLR_API void solr_throw_exception(zend_class_entry *exception_ce, char *message, long code, const char *filename, int file_line, const char *function_name);
PHP_SOLR_API void solr_throw_solr_server_exception(solr_client_t *client,const char *requestType);

/* {{{ init functions called in constructors - allocate/initialize params_t */
PHP_SOLR_API int solr_params_obj_ctor(zval *obj);
PHP_SOLR_API void solr_params_obj_dtor(zval *obj);
PHP_SOLR_API int solr_init_params(solr_params_t *solr_params, long int index);

zend_object *solr_extract_create_object_handler(zend_class_entry *ce);
/* }}} */

PHP_SOLR_API int  solr_init_ustream(zval *obj);
PHP_SOLR_API void solr_destroy_ustream_ex(solr_ustream_t *stream);
PHP_SOLR_API void solr_destroy_ustream_zv(zval *obj);
PHP_SOLR_API int  solr_fetch_ustream_entry(zval *objptr, solr_ustream_t **stream_entry);

#ifdef PHP_7
    #define solr_destroy_ustream solr_destroy_ustream_zv
#else
    #define solr_destroy_ustream solr_destroy_ustream_ex
#endif

/* {{{ solr_document_t based objects methods*/
PHP_SOLR_API solr_document_t *solr_init_document(long int document_index);
PHP_SOLR_API solr_document_t *solr_input_doc_ctor(zval *objptr);
#if PHP_VERSION_ID < 80000
PHP_SOLR_API zend_object *solr_document_object_handler_clone(zval *zobject);
#else
PHP_SOLR_API zend_object *solr_document_object_handler_clone(zend_object *zobject);
#endif
/* }}} */

/* {{{ zend_hash_free functions */
PHP_SOLR_API void solr_destroy_field_list_ht_dtor(zval *zv_field_entry);
PHP_SOLR_API void solr_destroy_field_list(solr_field_list_t *field_entry);
PHP_SOLR_API void solr_destroy_client(zval *client);


PHP_SOLR_API void solr_destroy_document_zv(zval *document);
PHP_SOLR_API void solr_destroy_document_ex(solr_document_t *document);

#ifdef PHP_7
    #define solr_destroy_document solr_destroy_document_zv
#else
    #define solr_destroy_document solr_destroy_document_ex
#endif

PHP_SOLR_API void solr_destroy_params(zval *solr_params);
PHP_SOLR_API void solr_destroy_function(zval *solr_function);
PHP_SOLR_API void solr_destory_param_ht_dtor(zval *param_zv);
PHP_SOLR_API void solr_destroy_param(solr_param_t **param);
/* dead */
PHP_SOLR_API void solr_destroy_param_value(solr_param_t *param, solr_param_value_t *param_value);
/* }}} */

#ifdef PHP_7
    #define field_copy_constructor field_copy_constructor_zv
#else
    #define field_copy_constructor field_copy_constructor_ex
#endif

/* {{{ used for SolrDocument field manipulations */
PHP_SOLR_API int solr_document_insert_field_value_ex(solr_field_list_t *queue, const solr_char_t *field_value, double field_boost, int modifier);
PHP_SOLR_API void field_copy_constructor_ex(solr_field_list_t **original_field_queue);
PHP_SOLR_API void field_copy_constructor_zv(zval *field_queue_zv);

/* }}} */

/* {{{ Used for comparison of document fields */
#if PHP_VERSION_ID < 80000
PHP_SOLR_API int solr_compare_field_name (const void *a, const void *b);
PHP_SOLR_API int solr_rcompare_field_name(const void *a, const void *b);

PHP_SOLR_API int solr_compare_field_value_count (const void *a, const void *b);
PHP_SOLR_API int solr_rcompare_field_value_count(const void *a, const void *b);

PHP_SOLR_API int solr_compare_field_boost_value (const void *a, const void *b);
PHP_SOLR_API int solr_rcompare_field_boost_value(const void *a, const void *b);
#else
PHP_SOLR_API int solr_compare_field_name (Bucket *a, Bucket *b);
PHP_SOLR_API int solr_rcompare_field_name(Bucket *a, Bucket *b);

PHP_SOLR_API int solr_compare_field_value_count (Bucket *a, Bucket *b);
PHP_SOLR_API int solr_rcompare_field_value_count(Bucket *a, Bucket *b);

PHP_SOLR_API int solr_compare_field_boost_value (Bucket *a, Bucket *b);
PHP_SOLR_API int solr_rcompare_field_boost_value(Bucket *a, Bucket *b);
#endif
/* }}} */

/* {{{ Functions for SolrParams Parameters */
PHP_SOLR_API solr_param_t *solr_create_new_param(const solr_char_t *param_name, size_t param_name_len, solr_param_type_t param_type, solr_bool allow_multiple, solr_param_value_equal_func_t value_equal_func, solr_param_fetch_func_t param_fetch_func, solr_param_value_free_func_t value_free_func, solr_char_t delimiter, solr_char_t arg_separator);

PHP_SOLR_API int solr_params_insert_param_value(solr_param_t *param, solr_param_value_t *param_value);
PHP_SOLR_API int solr_params_delete_param_value(solr_param_t *param, const solr_param_value_t *target_value);
PHP_SOLR_API int solr_delete_solr_parameter(zval *objptr, solr_char_t *name, size_t name_length);

PHP_SOLR_API int solr_add_or_set_normal_param(zval *objptr, solr_char_t *pname, size_t pname_length, solr_char_t *pvalue, size_t pvalue_length, zend_bool allow_multiple);
PHP_SOLR_API int solr_add_simple_list_param(zval *objptr, solr_char_t *pname, size_t pname_length, solr_char_t *pvalue, size_t pvalue_length);
PHP_SOLR_API int solr_add_simple_list_param_ex(zval *objptr, solr_char_t *pname, size_t pname_length, solr_char_t *pvalue, size_t pvalue_length, solr_char_t *separator);
PHP_SOLR_API int solr_add_arg_list_param(zval *objptr, solr_char_t *pname, size_t pname_length, solr_char_t *pvalue, size_t pvalue_length, solr_char_t *avalue, size_t avalue_length, solr_char_t delimiter, solr_char_t arg_separator);
PHP_SOLR_API int solr_add_arg_list_param_ex(zval *objptr, solr_char_t *pname, size_t pname_length, solr_char_t *pvalue, size_t pvalue_length, solr_char_t *avalue, size_t avalue_length, solr_char_t delimiter, solr_char_t arg_separator, solr_char_t delimiter_override);
PHP_SOLR_API solr_param_value_t* create_parameter_value_arg_list(solr_char_t *pvalue, size_t pvalue_length, solr_char_t *avalue, size_t avalue_length, solr_char_t *delimiter_override, solr_bool delimiter_overriden);

#define solr_set_normal_param(objptr, pname, pname_length, pvalue, pvalue_length) solr_add_or_set_normal_param((objptr), (pname), (pname_length), (pvalue), (pvalue_length), 0)
#define solr_add_normal_param(objptr, pname, pname_length, pvalue, pvalue_length) solr_add_or_set_normal_param((objptr), (pname), (pname_length), (pvalue), (pvalue_length), 1)

PHP_SOLR_API int solr_normal_param_value_equal(const solr_param_value_t *a, const solr_param_value_t *b);
PHP_SOLR_API int solr_simple_list_param_value_equal(const solr_param_value_t *a, const solr_param_value_t *b);
PHP_SOLR_API int solr_arg_list_param_value_equal(const solr_param_value_t *a, const solr_param_value_t *b);

PHP_SOLR_API void solr_normal_param_value_fetch(solr_param_t *solr_param, solr_string_t *buffer);
PHP_SOLR_API void solr_simple_list_param_value_fetch(solr_param_t *solr_param, solr_string_t *buffer);
PHP_SOLR_API void solr_arg_list_param_value_fetch(solr_param_t *solr_param, solr_string_t *buffer);

PHP_SOLR_API void solr_normal_param_value_display(solr_param_t *solr_param, zval *param_value_array);
PHP_SOLR_API void solr_simple_list_param_value_display(solr_param_t *solr_param, zval *param_value_array);
PHP_SOLR_API void solr_arg_list_param_value_display(solr_param_t *solr_param, zval *param_value_array);

/* Used to display values where allow_multiple is false */
PHP_SOLR_API void solr_normal_param_value_display_string(solr_param_t *solr_param, zval *param_value);
PHP_SOLR_API void solr_normal_param_value_display_integer(solr_param_t *solr_param, zval *param_value);
PHP_SOLR_API void solr_normal_param_value_display_double(solr_param_t *solr_param, zval *param_value);
PHP_SOLR_API void solr_normal_param_value_display_boolean(solr_param_t *solr_param, zval *param_value);
PHP_SOLR_API void solr_normal_param_value_display_sort_type(solr_param_t *solr_param, zval *param_value);

PHP_SOLR_API int solr_param_find(zval *objptr, solr_char_t *pname, size_t pname_length, solr_param_t **solr_param);
PHP_SOLR_API solr_string_t solr_params_to_string(solr_params_t * solr_params, zend_bool url_encode);

PHP_SOLR_API void solr_normal_param_value_tostring(solr_param_t *solr_param, solr_string_t *buffer, zend_bool url_encode);
PHP_SOLR_API void solr_simple_list_param_value_tostring(solr_param_t *solr_param, solr_string_t *buffer, zend_bool url_encode);
PHP_SOLR_API void solr_arg_list_param_value_tostring(solr_param_t *solr_param, solr_string_t *buffer, zend_bool url_encode);

PHP_SOLR_API void solr_normal_param_value_free(solr_param_value_t *param_value);
PHP_SOLR_API void solr_simple_list_param_value_free(solr_param_value_t *param_value);
PHP_SOLR_API void solr_arg_list_param_value_free(solr_param_value_t *param_value);

/* Used for removing parameter values from the list of values for that param */
PHP_SOLR_API int solr_delete_normal_param_value(zval *objptr, solr_char_t *pname, size_t pname_length, solr_char_t *pvalue, size_t pvalue_length);
PHP_SOLR_API int solr_delete_simple_list_param_value(zval *objptr, solr_char_t *pname, size_t pname_length, solr_char_t *pvalue, size_t pvalue_length);
PHP_SOLR_API int solr_delete_arg_list_param_value(zval *objptr, solr_char_t *pname, size_t pname_length, solr_char_t *pvalue, size_t pvalue_length);

/* }}} */

/* {{{ Debugging functions */
/* Debug function used to print field values in the field queue */
PHP_SOLR_API void solr_debug_print_fields(const solr_field_list_t *queue);

/* Used when debugging is enabled to run in verbose mode */
PHP_SOLR_API void solr_debug_printf(const char *format, ...);
/* }}} */

/* {{{ Document utility functions */
PHP_SOLR_API void solr_generate_document_xml_from_fields(xmlNode *solr_doc_node, HashTable *document_fields);
PHP_SOLR_API void solr_create_document_field_object(solr_field_list_t *field_values, zval **field_obj);
PHP_SOLR_API void solr_add_doc_node(xmlNode *root_node, solr_document_t *doc_entry);
PHP_SOLR_API xmlDocPtr solr_xml_create_xml_doc(const xmlChar *root_node_name, xmlNode **root_node_ptr);
/* }}} */

/* {{{ identical functions used on both SolrDocument and SolrInputDocument */
PHP_SOLR_API void solr_document_get_field_names(INTERNAL_FUNCTION_PARAMETERS);
/* }}} */

/* {{{ Utility functions */
PHP_SOLR_API long solr_get_json_last_error(void);
PHP_SOLR_API solr_char_t *solr_get_json_error_msg(solr_json_error_codes_t error_code);
PHP_SOLR_API int solr_json_to_php_native(solr_string_t *buffer, const solr_char_t *json_string, size_t json_string_length);
PHP_SOLR_API int solr_is_supported_response_writer(const solr_char_t * response_writer, size_t length);
PHP_SOLR_API int solr_hashtable_get_new_index(HashTable *ht);
#if PHP_VERSION_ID < 80000
PHP_SOLR_API int solr_fetch_document_entry(zval *objptr, solr_document_t **doc_entry);
#else
PHP_SOLR_API int solr_fetch_document_entry(zend_object *objptr, solr_document_t **doc_entry);
#endif
PHP_SOLR_API int solr_fetch_client_entry(zval *objptr, solr_client_t **solr_client);
PHP_SOLR_API int solr_fetch_params_entry(zval *objptr, solr_params_t **solr_params);
PHP_SOLR_API int solr_fetch_function_entry(zval *objptr, solr_function_t **solr_params);
PHP_SOLR_API void solr_encode_generic_xml_response(solr_string_t *buffer, const solr_char_t *serialized, size_t size, long int parse_mode);
PHP_SOLR_API void solr_set_return_solr_params_object(zval *return_value_ptr, zval *current_objptr);
PHP_SOLR_API void solr_escape_query_chars(solr_string_t *sbuilder, solr_char_t *unescaped, size_t unescaped_length);

/* serialized array to serialized SolrObject */
PHP_SOLR_API int solr_sarray_to_sobject(solr_string_t *buffer);
PHP_SOLR_API int solr_sobject_to_sarray(solr_string_t *buffer);
PHP_SOLR_API void solr_response_get_response_impl(INTERNAL_FUNCTION_PARAMETERS, int return_array);
/* }}} */

/* {{{ SolrFunction Helpers (solrfunc to avoid confusion with solr_function) */
PHP_SOLR_API int  solr_solrfunc_update_string(zval *obj, solr_char_t *key, size_t key_len, solr_char_t *value, size_t value_len);
PHP_SOLR_API int  solr_solrfunc_fetch_string(zval *obj, solr_char_t *key, size_t key_len, solr_string_t **string);
PHP_SOLR_API int  solr_solrfunc_return_string(zval *obj, solr_char_t *key, size_t key_len, zval **return_value);
PHP_SOLR_API void solr_solrfunc_to_string(solr_function_t *function, solr_string_t **dest);
PHP_SOLR_API int solr_solrfunc_display_string(zval *obj, solr_char_t *key, size_t key_len, zval **return_value);

#if PHP_VERSION_ID < 80000
zend_object *solr_collapse_function_object_handler_clone(zval *object);
#else
zend_object *solr_collapse_function_object_handler_clone(zend_object *object);
#endif
/* }}} */

/* {{{ Solr Server Exception Handling */
PHP_SOLR_API int solr_get_xml_error(solr_string_t buffer, solr_exception_t *exceptionData);
PHP_SOLR_API int solr_get_json_error(solr_string_t buffer, solr_exception_t *exceptionData);
PHP_SOLR_API int solr_get_phpnative_error(solr_string_t buffer, solr_exception_t *exceptionData);
PHP_SOLR_API int hydrate_error_zval(zval *response, solr_exception_t *exceptionData);
/* }}} */

/* {{{ Solr Object Handlers */
#if PHP_VERSION_ID < 80000
#define OBJ_FOR_PROP(zv) (zv)

#if PHP_VERSION_ID < 70400
PHP_SOLR_API void solr_object_write_property(zval *object, zval *member, zval *value, void **cache_slot);
PHP_SOLR_API void solr_document_field_write_property(zval *object, zval *member, zval *value, void **cache_slot);
#else
PHP_SOLR_API zval *solr_object_write_property(zval *object, zval *member, zval *value, void **cache_slot);
PHP_SOLR_API zval *solr_document_field_write_property(zval *object, zval *member, zval *value, void **cache_slot);
#endif

PHP_SOLR_API zval *solr_object_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv);
PHP_SOLR_API void solr_object_unset_property(zval *object, zval *member, void **cache_slot);

PHP_SOLR_API void solr_object_write_dimension(zval *object, zval *offset, zval *value);
PHP_SOLR_API void solr_object_unset_dimension(zval *object, zval *offset);

PHP_SOLR_API void solr_document_field_unset_property(zval *object, zval *member, void **cache_slot);
#else
#define OBJ_FOR_PROP(zv) Z_OBJ_P(zv)

PHP_SOLR_API zval *solr_document_field_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot);
PHP_SOLR_API zval *solr_object_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot);

PHP_SOLR_API zval *solr_object_read_property(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv);
PHP_SOLR_API void solr_object_unset_property(zend_object *object, zend_string *member, void **cache_slot);

PHP_SOLR_API void solr_object_write_dimension(zend_object *object, zval *offset, zval *value);
PHP_SOLR_API void solr_object_unset_dimension(zend_object *object, zval *offset);

PHP_SOLR_API void solr_document_field_unset_property(zend_object *object, zend_string *member, void **cache_slot);
#endif
/* }}} */

int add_phrase_field(zval *obj, solr_char_t *pname, zval *boost, zval *slop, solr_char_t *field_name, COMPAT_ARG_SIZE_T field_name_len);


#define ZVAL_LONG_ASSIGN_TO_LONG(long_var,zval_in) \
    do { \
        zend_long zl_input = Z_LVAL_P(zval_in); \
        if (zl_input >= LONG_MIN && zl_input <= LONG_MAX) { \
        	long_var = (long int) zl_input; \
        } else { \
            solr_throw_exception_ex(solr_ce_SolrException, SOLR_ERROR_1008, SOLR_FILE_LINE_FUNC, "Internal Error: zend long conversion failed."); \
        } \
    } while(0)



#include "solr_macros.h"
#include "php_solr_dismax_query.h"

#endif /* HAVE_SOLR */

#endif /* SOLRCLIENT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

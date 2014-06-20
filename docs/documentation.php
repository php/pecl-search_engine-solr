<?php

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
   | Authors: Israel Ekpo <iekpo@php.net>                                 |
   |          Omar Shaban <omars@php.net>                                 |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

define('SOLR_MAJOR_VERSION', 2);
define('SOLR_MINOR_VERSION', 0);
define('SOLR_PATCH_VERSION', 0);

define('SOLR_EXTENSION_VERSION', '2.0.0b');

/**
 * Returns the current version of the Apache Solr extension
 *
 * @return string
 */
function solr_get_version()
{
    return SOLR_EXTENSION_VERSION;
}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrException extends Exception 
{

    /* Properties */
    protected  $sourceline ;
    protected  $sourcefile ;
    protected  $zif_name ;

    /* Methods */
    public function  getInternalInfo() {}
}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrClientException extends SolrException 
{
    public function getInternalInfo() {}
}

/**
 * Used for Solr Related Exceptions
 * 
 * @author Omar Shaban <omars@php.net>
 */
class SolrServerException extends SolrException
{
	public function getInternalInfo() {}
}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrIllegalArgumentException extends SolrException 
{
    public function getInternalInfo() {}
}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrIllegalOperationException extends SolrException 
{
    public function getInternalInfo() {}
}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
abstract  class SolrUtils
{
    /**
     * Parses an response XML string into a SolrObject
     * 
     * @param string $xmlresponse
     * @param int $parse_mode
     * @return SolrObject
     */
    public static function digestXmlResponse($xmlresponse, $parse_mode) {}

    public static function escapeQueryChars($str) {}

    public static function getSolrVersion() {}

    public static function queryPhrase($str) {}
}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrDocumentField 
{

    /* Properties */
    public $name ;
    public $boost ;
    public $values ;

    /* Methods */
    public function __construct() {}
    public function __destruct() {}
}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrInputDocument   
{

    const  SORT_DEFAULT = 1 ;
    const  SORT_ASC = 1 ;
    const  SORT_DESC = 2 ;
    const  SORT_FIELD_NAME = 1 ;
    const  SORT_FIELD_VALUE_COUNT = 2 ;
    const  SORT_FIELD_BOOST_VALUE = 4 ;

    public function addField($fieldName, $fieldValue, $fieldBoostValue) {}
    public function clear() {}
    public function __clone() {}
    public function __construct() {}
    public function deleteField($fieldName) {}
    public function __destruct() {}
    public function fieldExists($fieldName) {}
    public function getBoost() {}
    
    /**
     * Retrieves a field by name
     * 
     * @param string $fieldName
     * @return SolrDocumentField
     */
    public function getField($fieldName) {}
    public function getFieldBoost($fieldName) {}
    public function getFieldCount() {}
    public function getFieldNames() {}
    public function merge(SolrInputDocument &$sourceDoc,  $overwrite) {}
    public function reset() {}
    public function setBoost($documentBoostValue) {}
    public function setFieldBoost($fieldName, $fieldBoostValue) {}
    public function sort(int $sortOrderBy, $sortDirection) {}
    public function toArray() {}

}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrDocument implements ArrayAccess, Iterator, Traversable, Serializable   
{

    const SORT_DEFAULT = 1 ;
    const SORT_ASC = 1 ;
    const SORT_DESC = 2 ;
    const SORT_FIELD_NAME = 1 ;
    const SORT_FIELD_VALUE_COUNT = 2 ;
    const SORT_FIELD_BOOST_VALUE = 4 ;

    public function  addField($fieldName,  $fieldValue) {}
    public function  clear() {}
    public function  __clone() {}
    public function  __construct() {}
    public function  current() {}
    public function  deleteField($fieldName) {}
    public function  __destruct() {}
    public function  fieldExists($fieldName) {}
    public function   __get($fieldName) {}
    
    /**
     * Retrieves a field by name
     * 
     * @param string $fieldName
     * @return SolrDocumentField
     */
    public function   getField($fieldName) {}
    public function   getFieldCount() {}
    public function   getFieldNames() {}
    
    /**
     * 
     * @return SolrInputDocument
     */
    public function  getInputDocument() {}
    public function  __isset($fieldName) {}
    public function   key() {}
    public function  merge(SolrDocument &$sourceDoc, $overwrite) {}
    public function  next() {}
    public function  offsetExists($fieldName) {}
    public function   offsetGet($fieldName) {}
    public function  offsetSet($fieldName,  $fieldValue) {}
    public function  offsetUnset($fieldName) {}
    public function  reset() {}
    public function  rewind() {}
    public function   serialize() {}
    public function  __set($fieldName,  $fieldValue) {}
    public function  sort($sortOrderBy, $sortDirection) {}
    public function   toArray() {}
    public function  unserialize($serialized) {}
    public function  __unset($fieldName) {}
    public function  valid() {}
}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrObject implements ArrayAccess   
{

    /* Methods */
    public function __construct() {}
    public function   __destruct() {}
    public function   getPropertyNames() {}
    public function   offsetExists($property_name) {}
    public function   offsetGet($property_name) {}
    public function   offsetSet($property_name,  $property_value) {}
    public function   offsetUnset($property_name) {}
}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 * @author Omar Shaban <omars@php.net>
 */
class SolrClient   
{
    /* Constants */
    const SEARCH_SERVLET_TYPE = 1 ;
    const UPDATE_SERVLET_TYPE = 2 ;
    const THREADS_SERVLET_TYPE = 4 ;
    const PING_SERVLET_TYPE = 8 ;
    const TERMS_SERVLET_TYPE = 16 ;
    const SYSTEM_SERVLET_TYPE = 32;
    
    const DEFAULT_SEARCH_SERVLET = 'select' ;
    const DEFAULT_UPDATE_SERVLET = 'update' ;
    const DEFAULT_THREADS_SERVLET = 'admin/threads' ;
    const DEFAULT_PING_SERVLET = 'admin/ping' ;
    const DEFAULT_TERMS_SERVLET = 'terms' ;
    const DEFAULT_SYSTEM_SERVLET = 'admin/system' ;

    /**
     * Constructor
     * 
     * @param array $clientOptions
     */
    public function  __construct(array $clientOptions) {}
    
    public function  __destruct() {}
    
    /**
     * Adds a document to the index
     * 
     * @param SolrInputDocument $doc
     * @param bool $overwrite
     * @param int $commitWithin 0 means disabled
     * @return SolrUpdateResponse
     */
    public function addDocument(SolrInputDocument &$doc, $overwrite = true, $commitWithin = 0) {}
    
    /**
     * Adds a collection of SolrInputDocument instances to the index
     *  
     * @param array $doc An array of SolrInputDocument objects
     * @param bool $overwrite
     * @param int $commitWithin
     * @return SolrUpdateResponse
     */
    public function  addDocuments(array &$docs, $overwrite = true, $commitWithin = 0) {}
    
    
    /**
     * Finalizes all add/deletes made to the index
     * 
     * @param bool $softCommit
     * @param bool $waitSearcher
     * @param bool $expungeDeletes
     * @return SolrUpdateResponse
     */
    public function commit($softCommit = false, $waitSearcher = true, $expungeDeletes = false) {}

    /**
     * Deletes the document with the specified ID. 
     * 
     * Where ID is the value of the uniqueKey field declared in the schema 
     * 
     * @param string $id
     * @return SolrUpdateResponse
     */
    public function deleteById($id) {}
    
    /**
     * Deletes a collection of documents with the specified set of ids
     * 
     * @param array $ids
     * @return SolrUpdateResponse
     */
    public function deleteByIds(array $ids) {}
    
    /**
     * Removes all documents matching any of the queries
     * 
     * @param array $queries
     * @return SolrUpdateResponse
     */
    public function deleteByQueries(array $queries) {}
    
    /**
     * Deletes all documents matching the given query
     * 
     * @param string $query
     * @return SolrUpdateResponse
     */
    public function deleteByQuery($query) {}
    
    /**
     * Returns the debug data for the last connection attempt
     * 
     * @return string
     */
    public function getDebug() {}
    
    /**
     * Returns the client options set internally
     * 
     * @return array
     */
    public function  getOptions() {}
    
    /**
     * Defragments the index for faster search performance
     * 
     * @param int $maxSegments
     * @param int $softCommit
     * @param bool $waitSearcher
     * @return SolrUpdateResponse
     */
    public function optimize($maxSegments = 1, $softCommit = false, $waitSearcher = true) {}
    
    /**
     * Checks if Solr server is still up
     * 
     * @return SolrPingResponse
     */
    public function ping() {}
    
    /**
     * Sends a query to the server
     * 
     * @param SolrParams $query
     * @return SolrQueryResponse
     */
    public function query(SolrParams &$query) {}
    
    /**
     * Sends a raw XML update request to the server 
     * 
     * @param string $raw_request
     * @return SolrUpdateResponse
     */
    public function request($raw_request) {}
    
    /**
     * Rollbacks all add/deletes made to the index since the last commit
     *  
     * @return SolrUpdateResponse
     */
    public function rollback() {}
    
    /**
     * Changes the specified servlet type to a new value
     * 
     * @return bool
     */
    public function setServlet($type, $value) {}
    
    /**
     * 
     * @return SolrGenericResponse
     */
    public function threads() {}
    
    /**
     * Retrieve Solr Server System Information
     * 
     * @return SolrGenericResponse
     */
    public function system () {}
}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrResponse   {
    
    /* Constants */
    const PARSE_SOLR_OBJ = 0 ;
    const PARSE_SOLR_DOC = 1 ;
    
    /* Properties */
    protected  $http_status ;
    protected  $parser_mode ;
    protected  $success ;
    protected  $http_status_message ;
    protected  $http_request_url ;
    protected  $http_raw_request_headers ;
    protected  $http_raw_request ;
    protected  $http_raw_response_headers ;
    protected  $http_raw_response ;
    protected  $http_digested_response ;
    
    /* Methods */
    public function   __construct() {}
    public function   __destruct() {}
    
    public function   getDigestedResponse() {}
    public function   getHttpStatus() {}
    public function   getHttpStatusMessage() {}
    public function   getRawRequest() {}
    public function   getRawRequestHeaders() {}
    public function   getRawResponse() {}
    public function   getRawResponseHeaders() {}
    public function   getRequestUrl() {}
    public function   getResponse() {}
    public function   setParseMode($parser_mode) {}
    public function   success() {}
}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrQueryResponse extends SolrResponse 
{

}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrUpdateResponse extends SolrResponse 
{

}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrPingResponse extends SolrResponse 
{

}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrGenericResponse extends SolrResponse   
{

}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
abstract class SolrParams implements Serializable
{
    /**
     * This is an alias for SolrParams::addParam
     * 
     * @param $name
     * @param $value
     * @return SolrParams
     */
    public function add($name, $value) {}
    
    /**
     * Adds a parameter to the object
     * 
     * @param $name
     * @param $value
     * @return SolrParams
     */
    public function addParam($name, $value) {}
    
    /**
     * This is an alias for SolrParams::getParam
     * 
     * Returns an array or string depending on the type of parameter 
     * 
     * @return mixed
     */
    public function get($param_name) {}

    /**
     * Get Param
     * 
     * Returns an array or string depending on the type of parameter 
     * 
     * @return mixed
     */
    public function getParam($param_name) {}
    
    /**
     * Returns an array of non URL-encoded parameters 
     * 
     * @return array
     */
    public function getParams() {}
    
    /**
     * Returns an array on URL-encoded parameters 
     * 
     * @return array
     */
    public function getPreparedParams() {}

    /**
     * Used for custom serialization
     * 
     * @return string
     */
    public function serialize() {}
    
    /**
     * 
     * @param $name
     * @param $value
     * @return SolrParams
     */
    public function set($name, $value) {}
    
    /**
     * 
     * @param $name
     * @param $value
     * @return SolrParams
     */
    public function setParam($name, $value) {}
    
    /**
     * Returns all the name-value pair parameters in the object
     * 
     * @return string
     */
    public function toString($url_encode) {}

    /**
     * Used for Custom serialization
     * 
     * @param string $serialized
     * @return void
     */
    public function unserialize($serialized) {}
}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrModifiableParams extends  SolrParams implements Serializable 
{
     public function __construct() {}

     public function __destruct() {}
     
    /**
     * This is an alias for SolrParams::addParam
     * 
     * @param $name
     * @param $value
     * @return SolrModifiableParams
     */
    public function add($name, $value) {}
    
    /**
     * Adds a parameter to the object
     * 
     * @param $name
     * @param $value
     * @return SolrModifiableParams
     */
    public function addParam($name, $value) {}
    
    /**
     * This is an alias for SolrParams::getParam
     * 
     * Returns an array or string depending on the type of parameter 
     * 
     * @return mixed
     */
    public function get($param_name) {}

    /**
     * Get Param
     * 
     * Returns an array or string depending on the type of parameter 
     * 
     * @return mixed
     */
    public function getParam($param_name) {}
    
    /**
     * Returns an array of non URL-encoded parameters 
     * 
     * @return array
     */
    public function getParams() {}
    
    /**
     * Returns an array on URL-encoded parameters 
     * 
     * @return array
     */
    public function getPreparedParams() {}

    /**
     * Used for custom serialization
     * 
     * @return string
     */
    public function serialize() {}
    
    /**
     * 
     * @param $name
     * @param $value
     * @return SolrModifiableParams
     */
    public function set($name, $value) {}
    
    /**
     * 
     * @param $name
     * @param $value
     * @return SolrModifiableParams
     */
    public function setParam($name, $value) {}
    
    /**
     * Returns all the name-value pair parameters in the object
     * 
     * @return string
     */
    public function toString($url_encode) {}

    /**
     * Used for Custom serialization
     * 
     * @param string $serialized
     * @return void
     */
    public function unserialize($serialized) {}
}

/**
 * 
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrQuery extends SolrModifiableParams implements Serializable {

    /* Constants */
    const ORDER_ASC = 0 ;
    const ORDER_DESC = 1 ;
    const FACET_SORT_INDEX = 0 ;
    const FACET_SORT_COUNT = 1 ;
    const TERMS_SORT_INDEX = 0 ;
    const TERMS_SORT_COUNT = 1 ;
    
    /**
     * 
     * @param string $q Query string
     */
    public function  __construct($q = null) {}
    
    public function  __destruct() {}
    
    /**
     * This is an alias for SolrParams::addParam
     * 
     * @param $name
     * @param $value
     * @return SolrQuery
     */
    public function add($name, $value) {}
    
    /**
     * Adds a parameter to the object
     * 
     * @param $name
     * @param $value
     * @return SolrQuery
     */
    public function addParam($name, $value) {}
    
    /**
     * This is an alias for SolrParams::getParam
     * 
     * Returns an array or string depending on the type of parameter 
     * 
     * @return mixed
     */
    public function get($param_name) {}

    /**
     * Get Param
     * 
     * Returns an array or string depending on the type of parameter 
     * 
     * @return mixed
     */
    public function getParam($param_name) {}
    
    /**
     * Returns an array of non URL-encoded parameters 
     * 
     * @return array
     */
    public function getParams() {}
    
    /**
     * Returns an array on URL-encoded parameters 
     * 
     * @return array
     */
    public function getPreparedParams() {}

    /**
     * Used for custom serialization
     * 
     * @return string
     */
    public function serialize() {}
    
    /**
     * 
     * @param $name
     * @param $value
     * @return SolrQuery
     */
    public function set($name, $value) {}
    
    /**
     * 
     * @param $name
     * @param $value
     * @return SolrQuery
     */
    public function setParam($name, $value) {}
    
    /**
     * Returns all the name-value pair parameters in the object
     * 
     * @return string
     */
    public function toString($url_encode) {}

    /**
     * Used for Custom serialization
     * 
     * @param string $serialized
     * @return void
     */
    public function unserialize($serialized) {}

    /**
     * 
     * @return SolrQuery
     */
    public function  addFacetDateField($dateField) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  addFacetDateOther($value, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  addFacetField($field) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  addFacetQuery($facetQuery) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  addField($field) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  addFilterQuery($fq) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  addHighlightField($field) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  addMltField($field) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  addMltQueryField($field, $boost) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  addSortField($field, $order) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  addStatsFacet($field) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  addStatsField($field) {}
    
    public function  getFacet() {}
    public function  getFacetDateEnd($field_override) {}
    public function  getFacetDateFields() {}
    public function  getFacetDateGap($field_override) {}
    public function  getFacetDateHardEnd($field_override) {}
    public function  getFacetDateOther($field_override) {}
    public function  getFacetDateStart($field_override) {}
    public function  getFacetFields() {}
    public function  getFacetLimit($field_override) {}
    public function  getFacetMethod($field_override) {}
    public function  getFacetMinCount($field_override) {}
    public function  getFacetMissing($field_override) {}
    public function  getFacetOffset($field_override) {}
    public function  getFacetPrefix($field_override) {}
    public function  getFacetQueries() {}
    public function  getFacetSort($field_override) {}
    public function  getFields() {}
    public function  getFilterQueries() {}
    public function  getHighlight() {}
    public function  getHighlightAlternateField($field_override) {}
    public function  getHighlightFields() {}
    public function  getHighlightFormatter($field_override) {}
    public function  getHighlightFragmenter($field_override) {}
    public function  getHighlightFragsize($field_override) {}
    public function  getHighlightHighlightMultiTerm() {}
    public function  getHighlightMaxAlternateFieldLength($field_override) {}
    public function  getHighlightMaxAnalyzedChars() {}
    public function  getHighlightMergeContiguous($field_override) {}
    public function  getHighlightRegexMaxAnalyzedChars() {}
    public function  getHighlightRegexPattern() {}
    public function  getHighlightRegexSlop() {}
    public function  getHighlightRequireFieldMatch() {}
    public function  getHighlightSimplePost($field_override) {}
    public function  getHighlightSimplePre($field_override) {}
    public function  getHighlightSnippets($field_override) {}
    public function  getHighlightUsePhraseHighlighter() {}
    public function  getMlt() {}
    public function  getMltBoost() {}
    public function  getMltCount() {}
    public function  getMltFields() {}
    public function  getMltMaxNumQueryTerms() {}
    public function  getMltMaxNumTokens() {}
    public function  getMltMaxWordLength() {}
    public function  getMltMinDocFrequency() {}
    public function  getMltMinTermFrequency() {}
    public function  getMltMinWordLength() {}
    public function  getMltQueryFields() {}
    public function  getQuery() {}
    public function  getRows() {}
    public function  getSortFields() {}
    public function  getStart() {}
    public function  getStats() {}
    public function  getStatsFacets() {}
    public function  getStatsFields() {}
    public function  getTerms() {}
    public function  getTermsField() {}
    public function  getTermsIncludeLowerBound() {}
    public function  getTermsIncludeUpperBound() {}
    public function  getTermsLimit() {}
    public function  getTermsLowerBound() {}
    public function  getTermsMaxCount() {}
    public function  getTermsMinCount() {}
    public function  getTermsPrefix() {}
    public function  getTermsReturnRaw() {}
    public function  getTermsSort() {}
    public function  getTermsUpperBound() {}
    public function  getTimeAllowed() {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  removeFacetDateField($field) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  removeFacetDateOther($value, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  removeFacetField($field) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  removeFacetQuery($value) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  removeField($field) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  removeFilterQuery($fq) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  removeHighlightField($field) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  removeMltField($field) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  removeMltQueryField($queryField) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  removeSortField($field) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  removeStatsFacet($value) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  removeStatsField($field) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setEchoHandler($flag) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setEchoParams($type) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setExplainOther($query) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setFacet($flag) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setFacetDateEnd($value, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setFacetDateGap($value, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setFacetDateHardEnd($value, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setFacetDateStart($value, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setFacetEnumCacheMinDefaultFrequency($frequency, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setFacetLimit($limit, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setFacetMethod($method, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setFacetMinCount($mincount, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setFacetMissing($flag, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setFacetOffset($offset, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setFacetPrefix($prefix, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setFacetSort($facetSort, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlight($flag) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightAlternateField($field, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightFormatter($formatter, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightFragmenter($fragmenter, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightFragsize($size, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightHighlightMultiTerm($flag) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightMaxAlternateFieldLength($fieldLength, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightMaxAnalyzedChars($value) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightMergeContiguous($flag, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightRegexMaxAnalyzedChars($maxAnalyzedChars) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightRegexPattern($value) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightRegexSlop(float $factor) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightRequireFieldMatch($flag) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightSimplePost($simplePost, $field_override) {}
    
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightSimplePre($simplePre, $field_override) {}

    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightSnippets($value, $field_override) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setHighlightUsePhraseHighlighter($flag) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setMlt($flag) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setMltBoost($flag) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setMltCount($count) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setMltMaxNumQueryTerms($value) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setMltMaxNumTokens($value) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setMltMaxWordLength($maxWordLength) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setMltMinDocFrequency($minDocFrequency) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setMltMinTermFrequency($minTermFrequency) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setMltMinWordLength($minWordLength) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setOmitHeader($flag) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setQuery($query) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setRows($rows) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setShowDebugInfo($flag) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setStart($start) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setStats($flag) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setTerms($flag) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setTermsField($fieldname) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setTermsIncludeLowerBound($flag) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setTermsIncludeUpperBound($flag) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setTermsLimit($limit) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setTermsLowerBound($lowerBound) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setTermsMaxCount($frequency) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setTermsMinCount($frequency) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setTermsPrefix($prefix) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setTermsReturnRaw($flag) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setTermsSort($sortType) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setTermsUpperBound($upperBound) {}
    
    /**
     * 
     * @return SolrQuery
     */
    public function  setTimeAllowed($timeAllowed) {}
}


/* phpdoc -f documentation.php  --title Solr  --parseprivate on --defaultpackagename Solr  --output  "HTML:frames:phphtmllib" -t solr_phpdoc */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

<?php

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
   | Authors: Israel Ekpo <iekpo@php.net>                                 |
   |          Omar Shaban <omars@php.net>                                 |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

define('SOLR_MAJOR_VERSION', 2);
define('SOLR_MINOR_VERSION', 2);
define('SOLR_PATCH_VERSION', 0);

define('SOLR_EXTENSION_VERSION', '2.2.0');

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
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrException extends Exception
{

    /* Properties */
    protected $sourceline;

    protected $sourcefile;

    protected $zif_name;

    /* Methods */
    public function getInternalInfo() {}
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
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrIllegalArgumentException extends SolrException
{
    public function getInternalInfo() {}
}

/**
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrIllegalOperationException extends SolrException
{
    public function getInternalInfo() {}
}

/**
 * @author Omar Shaban <omars@php.net>
 */
class SolrMissingMandatoryParameterException extends SolrException
{
}


/**
 *
 * @author Israel Ekpo <iekpo@php.net>
 */
abstract class SolrUtils
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
class SolrDocument implements ArrayAccess, Iterator, Serializable
{

    const SORT_DEFAULT = 1 ;
    const SORT_ASC = 1 ;
    const SORT_DESC = 2 ;
    const SORT_FIELD_NAME = 1 ;
    const SORT_FIELD_VALUE_COUNT = 2 ;
    const SORT_FIELD_BOOST_VALUE = 4 ;

    public function addField($fieldName,  $fieldValue) {}
    public function clear() {}
    public function __clone() {}
    public function __construct() {}
    public function  current() {}
    public function deleteField($fieldName) {}
    public function __destruct() {}
    public function fieldExists($fieldName) {}
    public function __get($fieldName) {}

    /**
     * Retrieves a field by name
     *
     * @param string $fieldName
     * @return SolrDocumentField
     */
    public function getField($fieldName) {}

    public function getFieldCount() {}

    public function getFieldNames() {}

    /**
     *
     * @return SolrInputDocument
     */
    public function getInputDocument() {}

    public function __isset($fieldName) {}

    public function key()
    {}

    public function merge(SolrDocument &$sourceDoc, $overwrite)
    {}

    public function next()
    {}

    public function offsetExists($fieldName)
    {}

    public function offsetGet($fieldName)
    {}

    public function offsetSet($fieldName, $fieldValue)
    {}

    public function offsetUnset($fieldName)
    {}

    public function reset()
    {}

    public function rewind()
    {}

    public function serialize()
    {}

    public function __set($fieldName, $fieldValue)
    {}

    public function sort($sortOrderBy, $sortDirection)
    {}

    public function toArray()
    {}

    public function unserialize($serialized)
    {}

    public function __unset($fieldName)
    {}

    public function valid()
    {}
}

/**
 *
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrObject implements ArrayAccess
{

    /* Methods */
    public function __construct() {}
    public function __destruct() {}
    public function getPropertyNames() {}
    public function offsetExists($property_name) {}
    public function offsetGet($property_name) {}
    public function offsetSet($property_name,  $property_value) {}
    public function offsetUnset($property_name) {}
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
    public function addDocuments(array &$docs, $overwrite = true, $commitWithin = 0) {}


    /**
     * Finalizes all add/deletes made to the index
     *
     * @param bool $softCommit
     * @param bool $waitSearcher
     * @param bool $expungeDeletes
     * @return SolrUpdateResponse
     */
    public function commit($softCommit = false, $waitSearcher = true, $expungeDeletes = false) {}
    
    public function getById($id) {}
    
    public function getByIds(array $ids) {}

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
    public function getOptions() {}

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
    public function system() {}
}

/**
 *
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrResponse {

    /* Constants */
    const PARSE_SOLR_OBJ = 0 ;
    const PARSE_SOLR_DOC = 1 ;

    /* Properties */
    protected $http_status;

    protected $parser_mode;

    protected $success;

    protected $http_status_message;

    protected $http_request_url;

    protected $http_raw_request_headers;

    protected $http_raw_request;

    protected $http_raw_response_headers;

    protected $http_raw_response;

    protected $http_digested_response;

    /* Methods */
    public function __construct() {}
    public function __destruct() {}

    /**
     * Returns the XML response as serialized PHP data
     *
     * @return string
     * @link http://docs.php.net/manual/en/solrresponse.getdigestedresponse.php
     */
    public function getDigestedResponse() {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrresponse.gethttpstatus.php
     */
    public function getHttpStatus() {}

    /**
     * @return string
     * @link http://docs.php.net/manual/en/solrresponse.gethttpstatusmessage.php
     */
    public function getHttpStatusMessage() {}

    /**
     * @return string
     * @link http://docs.php.net/manual/en/solrresponse.getrawrequest.php
     */
    public function getRawRequest() {}

    /**
     * @return string
     * @link http://docs.php.net/manual/en/solrresponse.getrawrequestheaders.php
     */
    public function getRawRequestHeaders() {}

    /**
     * @return string
     * @link http://docs.php.net/manual/en/solrresponse.getrawresponse.php
     */
    public function getRawResponse() {}

    /**
     * Returns the raw response headers from the server
     *
     * @return string
     * @link http://docs.php.net/manual/en/solrresponse.getrawresponseheaders.php
     */
    public function getRawResponseHeaders() {}

    /**
     * Returns the full URL the request was sent to
     *
     * @return string
     * @link http://docs.php.net/manual/en/solrresponse.getrequesturl.php
     */
    public function getRequestUrl() {}

    /**
     * Returns a SolrObject representing the XML response from the server
     *
     * @return SolrObject
     * @link http://docs.php.net/manual/en/solrresponse.getresponse.php
     */
    public function getResponse() {}

    /**
     * @param int $parser_mode
     * @return bool
     * @link http://docs.php.net/manual/en/solrresponse.setparsemode.php
     */
    public function setParseMode($parser_mode) {}

    /**
     * @return bool
     * @link http://docs.php.net/manual/en/solrresponse.success.php
     */
    public function success() {}
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
     * @param string $name Param name
     * @param string $value Param value
     * @return SolrParams
     */
    public function addParam($name, $value) {}

    /**
     * This is an alias for SolrParams::getParam
     *
     * Returns an array or string depending on the type of parameter
     *
     * @param string $param_name
     *
     * @return mixed
     */
    public function get($param_name) {}

    /**
     * Returns an array or string depending on the type of parameter
     *
     * @param string $param_name
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
     * @param bool $url_encode Whether to return URL-encoded values
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
 * Represents a collection of name-value pairs sent to the Solr server during a request
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
     * @param string $name Param name
     * @param string $value Param value
     * @return SolrParams
     */
    public function addParam($name, $value) {}

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
     * @param bool $url_encode Whether to return URL-encoded values
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
 * @author Omar Shaban <omars@php.net>
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
    public function __construct($q = null) {}

    public function __destruct() {}

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
     * @param string $name Param name
     * @param string $value Param value
     * @return SolrParams
     */
    public function addParam($name, $value) {}

    /**
     * This is an alias for SolrParams::getParam
     *
     * Returns an array or string depending on the type of parameter
     *
     * @param string $param_name
     *
     * @return mixed
     */
    public function get($param_name) {}

    /**
     * Returns an array or string depending on the type of parameter
     *
     * @param string $param_name
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
     * @param bool $url_encode Whether to return URL-encoded values
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
     * @param string $dateField
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.addfacetdatefield.php
     */
    public function addFacetDateField($dateField) {}

    /**
     * Adds another facet.date.other parameter
     *
     * @param string $value
     * @param string $field_override [optional] Field name for the override
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.addfacetdateother.php
     */
    public function addFacetDateOther($value, $field_override = null) {}

    /**
     * Adds another field to the facet
     *
     * @param string $field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.addfacetfield.php
     */
    public function addFacetField($field) {}

    /**
     * @param string $facetQuery
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.addfacetquery.php
     */
    public function addFacetQuery($facetQuery) {}

    /**
     * @param string $field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.addfield.php
     */
    public function addField($field) {}

    /**
     * @param string $fq
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.addfilterquery.php
     */
    public function addFilterQuery($fq) {}

    /**
     * @param string $field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.addhighlightfield.php
     */
    public function addHighlightField($field) {}

    /**
     * @param string $field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.addmltfield.php
     */
    public function addMltField($field) {}

    /**
     * @param string $field
     * @param float  $boost
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.addmltqueryfield.php
     */
    public function addMltQueryField($field, $boost) {}

    /**
     * @param string $field
     * @param int    $order
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.addsortfield.php
     */
    public function addSortField($field, $order) {}

    /**
     * @param string $field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.addstatsfacet.php
     */
    public function addStatsFacet($field) {}

    /**
     * @param string $field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.addstatsfield.php
     */
    public function addStatsField($field) {}

    /**
     * @return bool
     * @link http://docs.php.net/manual/en/solrquery.getfacet.php
     */
    public function getFacet() {}

    /**
     * @param string $field_override [optional]
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.getfacetdateend.php
     */
    public function getFacetDateEnd($field_override = null) {}

    /**
     * @return array
     * @link http://docs.php.net/manual/en/solrquery.getfacetdatefields.php
     */
    public function getFacetDateFields() {}

    /**
     * @param string $field_override [optional]
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.getfacetdategap.php
     */
    public function getFacetDateGap($field_override = null) {}

    /**
     * @param string $field_override [optional]
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.getfacetdatehardend.php
     */
    public function getFacetDateHardEnd($field_override = null) {}

    /**
     * @param string $field_override [optional]
     * @return array
     * @link http://docs.php.net/manual/en/solrquery.getfacetdateother.php
     */
    public function getFacetDateOther($field_override = null) {}

    /**
     * @param string $field_override [optional]
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.getfacetdatestart.php
     */
    public function getFacetDateStart($field_override = null) {}

    /**
     * @return array
     * @link http://docs.php.net/manual/en/solrquery.getfacetfields.php
     */
    public function getFacetFields() {}

    /**
     * @param string $field_override [optional]
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.getfacetlimit.php
     */
    public function getFacetLimit($field_override) {}

    /**
     * @param string $field_override [optional]
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.getfacetmethod.php
     */
    public function getFacetMethod($field_override) {}

    /**
     * @param string $field_override [optional]
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.getfacetmincount.php
     */
    public function getFacetMinCount($field_override) {}

    /**
     * @param string $field_override [optional]
     *
     * @return bool
     * @link http://docs.php.net/manual/en/solrquery.getfacetmissing.php
     */
    public function getFacetMissing($field_override) {}

    /**
     * @param string $field_override [optional]
     *
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.getfacetoffset.php
     */
    public function getFacetOffset($field_override) {}

    /**
     * @param string $field_override [optional]
     *
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.getfacetprefix.php
     */
    public function getFacetPrefix($field_override) {}

    /**
     * @return array
     * @link http://docs.php.net/manual/en/solrquery.getfacetqueries.php
     */
    public function getFacetQueries() {}

    /**
     * @param string $field_override [optional]
     *
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.getfacetsort.php
     */
    public function getFacetSort($field_override) {}

    /**
     * @return array
     * @link http://docs.php.net/manual/en/solrquery.getfields.php
     */
    public function getFields() {}

    /**
     * @return array
     * @link http://docs.php.net/manual/en/solrquery.getfilterqueries.php
     */
    public function getFilterQueries() {}

    /**
     * @return bool
     * @link http://docs.php.net/manual/en/solrquery.gethighlight.php
     */
    public function getHighlight() {}

    /**
     * @param string $field_override [optional]
     *
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.gethighlightalternatefield.php
     */
    public function getHighlightAlternateField($field_override = null) {}

    /**
     * @return array
     * @link http://docs.php.net/manual/en/solrquery.gethighlightfields.php
     */
    public function getHighlightFields() {}

    /**
     * @param string $field_override [optional]
     *
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.gethighlightformatter.php
     */
    public function getHighlightFormatter($field_override = null) {}

    /**
     * @param string $field_override [optional]
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.gethighlightfragmenter.php
     */
    public function getHighlightFragmenter($field_override = null) {}

    /**
     * @param string $field_override [optional]
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.gethighlightfragsize.php
     */
    public function getHighlightFragsize($field_override = null) {}

    /**
     * @return bool
     * @link http://docs.php.net/manual/en/solrquery.gethighlighthighlightmultiterm.php
     */
    public function getHighlightHighlightMultiTerm() {}

    /**
     * @param string $field_override [optional]
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.gethighlightmaxalternatefieldlength.php
     */
    public function getHighlightMaxAlternateFieldLength($field_override = null) {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.gethighlightmaxanalyzedchars.php
     */
    public function getHighlightMaxAnalyzedChars() {}

    /**
     * @param string $field_override [optional]
     * @return bool
     * @link http://docs.php.net/manual/en/solrquery.gethighlightmergecontiguous.php
     */
    public function getHighlightMergeContiguous($field_override = null) {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.gethighlightregexmaxanalyzedchars.php
     */
    public function getHighlightRegexMaxAnalyzedChars() {}

    /**
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.gethighlightregexpattern.php
     */
    public function getHighlightRegexPattern() {}

    /**
     * @return float
     * @link http://docs.php.net/manual/en/solrquery.gethighlightregexslop.php
     */
    public function getHighlightRegexSlop() {}

    /**
     * @return bool
     * @link http://docs.php.net/manual/en/solrquery.gethighlightrequirefieldmatch.php
     */
    public function getHighlightRequireFieldMatch() {}

    /**
     * @param string $field_override [optional]
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.gethighlightsimplepost.php
     */
    public function getHighlightSimplePost($field_override = null) {}

    /**
     * @param string $field_override [optional]
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.gethighlightsimplepre.php
     */
    public function getHighlightSimplePre($field_override = null) {}

    /**
     * @param string $field_override [optional]
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.gethighlightsnippets.php
     */
    public function getHighlightSnippets($field_override = null) {}

    /**
     * @return bool
     * @link http://docs.php.net/manual/en/solrquery.gethighlightusephrasehighlighter.php
     */
    public function getHighlightUsePhraseHighlighter() {}

    /**
     * @return bool
     * @link http://docs.php.net/manual/en/solrquery.getmlt.php
     */
    public function getMlt() {}

    /**
     * @return bool
     * @link http://docs.php.net/manual/en/solrquery.getmltboost.php
     */
    public function getMltBoost() {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.getmltcount.php
     */
    public function getMltCount() {}

    /**
     * @return array
     * @link http://docs.php.net/manual/en/solrquery.getmltfields.php
     */
    public function getMltFields() {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.getmltmaxnumqueryterms.php
     */
    public function getMltMaxNumQueryTerms() {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.getmltmaxnumtokens.php
     */
    public function getMltMaxNumTokens() {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.getmltmaxwordlength.php
     */
    public function getMltMaxWordLength() {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.getmltmindocfrequency.php
     */
    public function getMltMinDocFrequency() {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.getmltmintermfrequency.php
     */
    public function getMltMinTermFrequency() {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.getmltminwordlength.php
     */
    public function getMltMinWordLength() {}

    /**
     * @return array
     * @link http://docs.php.net/manual/en/solrquery.getmltqueryfields.php
     */
    public function getMltQueryFields() {}

    /**
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.getquery.php
     */
    public function getQuery() {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.getrows.php
     */
    public function getRows() {}

    /**
     * @return array
     * @link http://docs.php.net/manual/en/solrquery.getsortfields.php
     */
    public function getSortFields() {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.getstart.php
     */
    public function getStart() {}

    /**
     * @return bool
     * @link http://docs.php.net/manual/en/solrquery.getstats.php
     */
    public function getStats() {}

    /**
     * @return array
     * @link http://docs.php.net/manual/en/solrquery.getstatsfacets.php
     */
    public function getStatsFacets() {}

    /**
     * @return array
     * @link http://docs.php.net/manual/en/solrquery.getstatsfields.php
     */
    public function getStatsFields() {}

    /**
     * @return bool
     * @link http://docs.php.net/manual/en/solrquery.getterms.php
     */
    public function getTerms() {}

    /**
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.gettermsfield.php
     */
    public function getTermsField() {}

    /**
     * @return bool
     * @link http://docs.php.net/manual/en/solrquery.gettermsincludelowerbound.php
     */
    public function getTermsIncludeLowerBound() {}

    /**
     * @return bool
     * @link http://docs.php.net/manual/en/solrquery.gettermsincludeupperbound.php
     */
    public function getTermsIncludeUpperBound() {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.gettermslimit.php
     */
    public function getTermsLimit() {}

    /**
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.gettermslowerbound.php
     */
    public function getTermsLowerBound() {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.gettermsmaxcount.php
     */
    public function getTermsMaxCount() {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.gettermsmincount.php
     */
    public function getTermsMinCount() {}

    /**
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.gettermsprefix.php
     */
    public function getTermsPrefix() {}

    /**
     * @return bool
     * @link http://docs.php.net/manual/en/solrquery.gettermsreturnraw.php
     */
    public function getTermsReturnRaw() {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.gettermssort.php
     */
    public function getTermsSort() {}

    /**
     * @return string
     * @link http://docs.php.net/manual/en/solrquery.gettermsupperbound.php
     */
    public function getTermsUpperBound() {}

    /**
     * @return int
     * @link http://docs.php.net/manual/en/solrquery.gettimeallowed.php
     */
    public function getTimeAllowed() {}

    /**
     * @param string $field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.removefacetdatefield.php
     */
    public function removeFacetDateField($field) {}

    /**
     * @param string $value
     * @param string $field_override [optional]
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.removefacetdateother.php
     */
    public function removeFacetDateOther($value, $field_override) {}

    /**
     * @param string $field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.removefacetfield.php
     */
    public function removeFacetField($field) {}

    /**
     * @param string $value
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.removefacetquery.php
     */
    public function removeFacetQuery($value) {}

    /**
     * @param string $field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.removefield.php
     */
    public function removeField($field) {}

    /**
     * @param string $fq
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.removefilterquery.php
     */
    public function removeFilterQuery($fq) {}

    /**
     * @param string $field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.removehighlightfield.php
     */
    public function removeHighlightField($field) {}

    /**
     * @param string $field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.removemltfield.php
     */
    public function removeMltField($field) {}

    /**
     * @param string $queryField
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.removemltqueryfield.php
     */
    public function removeMltQueryField($queryField) {}

    /**
     * @param string $field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.removesortfield.php
     */
    public function removeSortField($field) {}

    /**
     * @param string $value
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.removestatsfacet.php
     */
    public function removeStatsFacet($value) {}

    /**
     * @param string $field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.removestatsfield.php
     */
    public function removeStatsField($field) {}

    /**
     * @param bool $flag
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setechohandler.php
     */
    public function setEchoHandler($flag) {}

    /**
     * @param string $type
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setechoparams.php
     */
    public function setEchoParams($type) {}

    /**
     * @param string $query
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setexplainother.php
     */
    public function setExplainOther($query) {}

    /**
     * @param bool $flag
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setfacet.php
     */
    public function setFacet($flag) {}

    /**
     * @param string $value
     * @param string $field_override [optional]
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setfacetdateend.php
     */
    public function setFacetDateEnd($value, $field_override) {}

    /**
     * @param string $value
     * @param string $field_override [optional]
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setfacetdategap.php
     */
    public function setFacetDateGap($value, $field_override) {}

    /**
     * @param bool   $value
     * @param string $field_override [optional]
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setfacetdatehardend.php
     */
    public function setFacetDateHardEnd($value, $field_override) {}

    /**
     * @param string $value
     * @param string $field_override [optional]
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setfacetdatestart.php
     */
    public function setFacetDateStart($value, $field_override) {}

    /**
     * @param int    $frequency
     * @param string $field_override [optional]
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setfacetenumcachemindefaultfrequency.php
     */
    public function setFacetEnumCacheMinDefaultFrequency($frequency, $field_override = null) {}

    /**
     * @param int    $limit
     * @param string $field_override [optional]
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setfacetlimit.php
     */
    public function setFacetLimit($limit, $field_override = null) {}

    /**
     * @param string $method
     * @param string $field_override [optional]
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setfacetmethod.php
     */
    public function setFacetMethod($method, $field_override = null) {}

    /**
     * @param int    $mincount
     * @param string $field_override [optional]
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setfacetmincount.php
     */
    public function setFacetMinCount($mincount, $field_override = null) {}

    /**
     * @param bool   $flag
     * @param string $field_override [optional]
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setfacetmissing.php
     */
    public function setFacetMissing($flag, $field_override = null) {}

    /**
     * @param int    $offset
     * @param string $field_override [optional]
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setfacetoffset.php
     */
    public function setFacetOffset($offset, $field_override = null) {}

    /**
     * @param string $prefix
     * @param string $field_override [optional]
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setfacetprefix.php
     */
    public function setFacetPrefix($prefix, $field_override = null) {}

    /**
     * @param int    $facetSort
     * @param string $field_override [optional]
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.setfacetsort.php
     */
    public function setFacetSort($facetSort, $field_override = null) {}

    /**
     * Enables or disables highlighting
     *
     * @param bool $flag
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlight.php
     */
    public function setHighlight($flag) {}

    /**
     * Specifies the highlithing backup field to use
     *
     * @param string $field
     * @param string $field_override [optional]
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlightalternatefield.php
     */
    public function setHighlightAlternateField($field, $field_override = null) {}

    /**
     * Specify a formatter for the highlight output
     *
     * @param string $formatter
     * @param string $field_override [optional]
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlightformatter.php
     */
    public function setHighlightFormatter($formatter, $field_override) {}

    /**
     * Sets a text snippet generator for highlighted text
     *
     * @param string $fragmenter
     * @param string $field_override
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlightfragmenter.php
     */
    public function setHighlightFragmenter($fragmenter, $field_override = null) {}

    /**
     * The size of fragments to consider for highlighting
     *
     * @param int $size Size (in characters) of fragments to consider for highlighting
     * @param string $field_override Name of the field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlightfragsize.php
     */
    public function setHighlightFragsize($size, $field_override = null) {}

    /**
     * @param bool $flag
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlighthighlightmultiterm.php
     */
    public function setHighlightHighlightMultiTerm($flag) {}

    /**
     * Sets the maximum number of characters of the field to return
     *
     * @param int    $fieldLength Length of the field
     * @param string $field_override Name of the field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlightmaxalternatefieldlength.php
     */
    public function setHighlightMaxAlternateFieldLength($fieldLength, $field_override = null) {}

    /**
     * Specifies the number of characters into a document to look for suitable snippets
     *
     * @param int $value The number of characters into a document to look for suitable snippets
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlightmaxanalyzedchars.php
     */
    public function setHighlightMaxAnalyzedChars($value) {}

    /**
     * Sets whether or not to collapse contiguous fragments into a single fragment
     *
     * @param bool $flag Whether or not to collapse contiguous fragments into a single fragment
     * @param null $field_override
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlightmergecontiguous.php
     */
    public function setHighlightMergeContiguous($flag, $field_override = null) {}

    /**
     * Specify the maximum number of characters to analyze
     *
     * @param int $maxAnalyzedChars
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlightregexmaxanalyzedchars.php
     */
    public function setHighlightRegexMaxAnalyzedChars($maxAnalyzedChars) {}

    /**
     * Specify the regular expression for fragmenting
     *
     * @param string $value The regular expression for fragmenting. This could be used to extract sentences
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlightregexpattern.php
     */
    public function setHighlightRegexPattern($value) {}

    /**
     * Sets the factor by which the regex fragmenter can stray from the ideal fragment size
     *
     * @param float $factor The factor by which the regex fragmenter can stray from the ideal fragment size
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlightregexslop.php
     */
    public function setHighlightRegexSlop($factor) {}

    /**
     * Sets whether field matching is required when highlighting
     *
     * @param bool $flag If TRUE, then a field will only be highlighted if the query
     *                   matched in this particular field. This will only work if
     *                   SolrQuery::setHighlightUsePhraseHighlighter() was set to TRUE
     *
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlightrequirefieldmatch.php
     */
    public function setHighlightRequireFieldMatch($flag) {}

    /**
     * Sets the text which appears after a highlighted term
     *
     * @param string $simplePost
     * @param string $field_override [optional] Name of the field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlightsimplepost.php
     */
    public function setHighlightSimplePost($simplePost, $field_override = null) {}

    /**
     * Sets the text which appears before a highlighted term
     *
     * @param string $simplePre
     * @param string $field_override [optional] Name of the field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlightsimplepre.php
     */
    public function setHighlightSimplePre($simplePre, $field_override = null) {}

    /**
     * @param int $value Maximum number of highlighted snippets to generate per field
     * @param string $field_override [optional] Name of the field
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlightsnippets.php
     */
    public function setHighlightSnippets($value, $field_override = null) {}

    /**
     * Whether to highlight phrase terms only when they appear within the query phrase
     *
     * @param bool $flag
     * @return SolrQuery
     * @link http://docs.php.net/manual/en/solrquery.sethighlightusephrasehighlighter.php
     */
    public function setHighlightUsePhraseHighlighter($flag) {}

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
    
    /**
     * Collapses the result set to a single document per group before it forwards 
     * the result set to the rest of the search components.
     * So all downstream components (faceting, highlighting, etc...) will work with 
     * the collapsed result set.
     * 
     * A collapse function is passed to collapse the query
     * 
     * @param SolrCollapseFunction $function
     * @throws SolrMissingMandatoryParameterException
     * @return SolrQuery
     */
    public function collapse(SolrCollapseFunction $function) {}
    
    /**
     * Enable/Disable result grouping (group parameter)
     *
     * @param bool $value
     * @return SolrQuery
     */
    public function setGroup($value) {}
    
    /**
     * Returns true if grouping is enabled
     * @return bool
     */
    public function getGroup() {}
    
    /**
     * The name of the field by which to group results. The field must be single-valued, and either be indexed 
     * or a field type that has a value source and works in a function query, 
     * such as ExternalFileField. It must also be a string-based field, such as StrField or TextField
     *
     * @param string $value
     * @return SolrQuery
     */
    public function addGroupField($value) {}
    
    /**
     * Returns group fields (group.field parameter values)
     *
     * @return array
     */
    public function getGroupFields() {}
    
    /**
     * Adds a group function (group.func parameter)
     * Allows grouping results based on the unique values of a function query.
     *
     * @param string $value
     * @return SolrQuery
     */
    public function addGroupFunction($value) {}    
    
    /**
     * Returns group functions (group.func parameter values)
     *
     * @return array
     */
    public function getGroupFunctions () {}
    
    /**
     * Adds query to the group.query parameter 
     * Allows grouping of documents that match the given query.
     *
     * @param string $value
     * @return SolrQuery
     */
    public function addGroupQuery($value) {}
    
    /**
     * Returns all the group.query parameter values
     *
     * @return array
     */
    public function getGroupQueries() {}
    
    /**
     * Specifies the number of results to return for each group. The server default value is 1.
     *
     * @param integer $value
     * @return SolrQuery
     */
    public function setGroupLimit($value) {}
    
    /**
     * Returns the group.limit value
     * @return integer
     */
    public function getGroupLimit() {}
    
    /**
     * Sets the group.offset parameter.
     * @param integer $offset
     * @return SolrQuery
     */
    public function setGroupOffset($offset) {}
    
    /**
     * Returns the group.offset value
     *
     * @return integer
     */
    public function getGroupOffset() {}
    
    /**
     * Add a group sort field (group.sort parameter).
     *
     * @param string $sort
     * @param integer $direction
     * @return SolrQuery
     */
    public function addGroupSortField($sort, $direction) {}
    
    /**
     * Returns the group.sort value
     *
     * @return array
     */
    public function getGroupSortFields() {}

    /**
     * Sets the group.format parameter.
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setGroupFormat($value) {}
    
    /**
     * Returns the group.format value
     *
     * @return string
     */
    public function getGroupFormat() {}
    
    /**
     * 
     * @param bool $value
     * @return SolrQuery
     */
    public function setGroupMain($value) {}
    
    /**
     * Returns the group.main value
     *
     * @return bool
     */
    public function getGroupMain() {}
    
    /**
     * If true, Solr includes the number of groups that have matched the query in the results.
     * The default value is false. (grous.ngroups parameter)
     *
     * @param bool $value
     * @return SolrQuery
     */
    public function setGroupNGroups($value) {}    

    /**
     * Returns the group.ngroups value
     * @return bool
     */
    public function getGroupNGroups() {}
    
    /**
     * If true, facet counts are based on the most relevant document of each group matching the query.
     * The server default value is false.
     * group.truncate parameter
     *
     * @param bool $value
     * @return SolrQuery
     */
    public function setGroupTruncate($value) {}
    
    /**
     * Returns the group.truncate value
     *
     * @return bool
     */
    public function getGroupTruncate() {}
    
    /**
     * Determines whether to compute grouped facets for the field facets specified in facet.field parameters.
     * Grouped facets are computed based on the first specified group.
     * group.facet parameter
     *
     * @param bool $value
     * @return SolrQuery
     */
    public function setGroupFacet($value) {}
    
    /**
     * Returns the group.facet parameter
     *
     * @return bool
     */
    public function getGroupFacet() {}
    
    /**
     * Setting this parameter to a number greater than 0 enables caching for result grouping.
     * Result Grouping executes two searches; this option caches the second search. The default value is 0.
     * 
     * Testing has shown that group caching only improves search time with Boolean, wildcard, and fuzzy queries. For simple queries like term or "match all" queries, group caching degrades performance.
     * group.cache.percent parameter
     *
     * @param integer
     * @return SolrQuery
     */
    public function setGroupCachePercent($value) {}
    
    /**
     * Returns the group cache percent group.cache.percent value
     *
     * @return integer
     */
    public function getGroupCachePercent() {}
    
    /**
     * Sets the expand parameter. This enables or disables group expanding.
     *
     * @param bool $value
     * @return SolrQuery
     */
    public function setExpand($value) {}

    /**
     * Returns true if group expanding is enabled
     * @return bool
     */
    public function getExpand() {}
    
    /**
     * Orders the documents within the expanded groups (expand.sort parameter).
     *
     * @param string $sort
     * @param integer $direction
     * @return SolrQuery
     */
    public function addExpandSortField($sort, $direction) {}
    
    /**
     * Removes an expand sort field from the expand.sort parameter.
     *
     * @param string $field
     * @return SolrQuery
     */
    public function removeExpandSortField($field) {}
    
    /**
     * Returns an array of fields
     *
     * @return array
     */
    public function getExpandSortFields() {}
    
    /**
     * Sets the number of rows to display in each group (expand.rows). Server Default 5
     * @param integer $rows
     * @return SolrQuery
     */
    public function setExpandRows($rows) {}
    
    /**
     * Returns The number of rows to display in each group (expand.rows) 
     *
     * @return integer
     */
    public function getExpandRows() {}
    
    /**
     * Sets the expand.q parameter. Overrides the main q parameter,
     * determines which documents to include in the main group.
     * 
     * @param string $q
     * @return SolrQuery
     */
    public function setExpandQuery($q) {}
    
    /**
     * Returns the expand query expand.q parameter
     *
     * @return string
     */
    public function getExpandQuery() {}
    
    /**
     * Overrides main fq's, determines which documents to include in the main group.
     *
     * @param string $fq
     * @return SolrQuery
     */
    public function addExpandFilterQuery($fq) {}
    
    /**
     * Removes an expand filter query.
     *
     * @param string $fq
     * @return SolrQuery
     */
    public function removeExpandFilterQuery($fq) {}
    
    /**
     * Returns the expand filter queries
     *
     * @return array
     */
    public function getExpandFilterQueries() {}

}

/**
 * SolrDisMaxQuery Makes use of the Solr's DisMax query parser
 * and eases the use of it using class methods
 *
 * @author Omar Shaban <omars@php.net>
 */
class SolrDisMaxQuery extends SolrQuery {

    public function __construct($q = null) {}

    /**
     * Switch Query Parser to dismax
     */
    public function useDisMaxQueryParser() {}

    /**
     * Switch Query Parser to edismax
     */
    public function useEDisMaxQueryParser() {}

    /**
     * Set Query Alternate (q.alt parameter)
     * When the main q parameter is not specified or is blank. The q.alt parameter is used
     */
    public function setQueryAlt($q) {}

    /**
     * Add a query field with optional boost (qf parameter)
     *
     * @see https://cwiki.apache.org/confluence/display/solr/The+DisMax+Query+Parser#TheDisMaxQueryParser-Theqf%28QueryFields%29Parameter
     * @param string $field
     * @param string $boost
     * @return SolrDisMaxQuery
     */
    public function addQueryField ($field, $boost=null) {}

    /**
     * Remove query field (qf parameter)
     *
     * @param string $field
     * @return SolrDisMaxQuery
     */
    public function removeQueryField($field) {}

    /**
     * Add a phrase field (pf parameter)
     * output format: field~slop^boost
     *
     * Sample output: title~2^4
     *
     * @see https://cwiki.apache.org/confluence/display/solr/The+DisMax+Query+Parser#TheDisMaxQueryParser-Thepf%28PhraseFields%29Parameter
     * @param string $field
     * @param float $boost
     * @param integer $slop
     * @return SolrDisMaxQuery
     */
    public function addPhraseField($field, $boost, $slop=null) {}

    /**
     * Removes a phrase field (pf parameter)
     * @param string $field
     * @return SolrDisMaxQuery
     */
    public function removePhraseField($field) {}

    /**
     * Set Phrase Fields (pf parameter)
     * @param string $fields
     * @return SolrDisMaxQuery
     */
    public function setPhraseFields($fields) {}

    /**
     * Set Phrase Slop (ps parameter)
     * @see https://cwiki.apache.org/confluence/display/solr/The+DisMax+Query+Parser#TheDisMaxQueryParser-Theps%28PhraseSlop%29Parameter
     * @param integer $slop
     * @return SolrDisMaxQuery
     */
    public function setPhraseSlop($slop) {}

    /**
     * Set Query Phrase Slop (qs parameter)
     *
     * @see https://cwiki.apache.org/confluence/display/solr/The+DisMax+Query+Parser#TheDisMaxQueryParser-Theqs%28QueryPhraseSlop%29Parameter
     * @param integer $slop
     * @return SolrDisMaxQuery
     */
    public function setQueryPhraseSlop($slop) {}

    /**
     * Add a boost query field with value and boost
     * Sample Output: type:lucene^2
     *
     * @see https://cwiki.apache.org/confluence/display/solr/The+DisMax+Query+Parser#TheDisMaxQueryParser-Thebq%28BoostQuery%29Parameter
     *
     * @param string $field
     * @param string $value
     * @param string $boost
     * @return SolrDisMaxQuery
     */
    public function addBoostQuery($field, $value, $boost=null) {}

    /**
     * Remove a boost query field
     *
     * @param string $field
     * @return SolrDisMaxQuery
     */
    public function removeBoostQuery($field) {}

    /**
     * Sets Boost Query Parameter (bq)
     *
     * @see https://cwiki.apache.org/confluence/display/solr/The+DisMax+Query+Parser#TheDisMaxQueryParser-Thebq%28BoostQuery%29Parameter
     *
     * @param string $q
     * @return SolrDisMaxQuery
     *
     */
    public function setBoostQuery($q) {}

    /**
     * Sets the boost function (bf)
     *
     * @see https://cwiki.apache.org/confluence/display/solr/The+DisMax+Query+Parser#TheDisMaxQueryParser-Thebf%28BoostFunctions%29Parameter
     *
     * @param string $function
     * @return SolrDisMaxQuery
     */
    public function setBoostFunction($function) {}

    /**
     * Set Tie Minimum *Should* Match parameter (mm)
     *
     * @see https://cwiki.apache.org/confluence/display/solr/The+DisMax+Query+Parser#TheDisMaxQueryParser-Themm%28MinimumShouldMatch%29Parameter
     *
     * @param mixed $value
     * @return SolrDisMaxQuery
     */
    public function setMinimumMatch($value) {}

    /**
     * Set Tie Breaker parameter (tie)
     *
     * @see https://cwiki.apache.org/confluence/display/solr/The+DisMax+Query+Parser#TheDisMaxQueryParser-Thetie%28TieBreaker%29Parameter
     * @param float $tieBreaker
     * @return SolrDisMaxQuery
     */
    public function setTieBreaker($tieBreaker) {}

    /**
     * Set Bigram Phrase Slop (ps2 parameter)
     *
     * @see https://cwiki.apache.org/confluence/display/solr/The+Extended+DisMax+Query+Parser
     *
     * @param integer $slop
     * @return SolrDisMaxQuery
     */
    public function setBigramPhraseSlop($slop) {}

    /**
     * Add a phrase Bigram field (pf2 parameter)
     * output format: field~slop^boost
     *
     * Sample output: title~2^4
     *
     * @see https://cwiki.apache.org/confluence/display/solr/The+DisMax+Query+Parser#TheDisMaxQueryParser-Thepf%28PhraseFields%29Parameter
     *
     * @param string $field
     * @param float $boost
     * @param integer $slop
     * @return SolrDisMaxQuery
     */
    public function addBigramPhraseField($field, $boost, $slop=null) {}

    /**
     * Removes phrase bigram field (pf2 parameter)
     *
     * @param string $field
     * @return SolrDisMaxQuery
     */
    public function removeBigramPhraseField($field) {}

    /**
     * Sets pf2 parameter
     *
     * @param string $fields
     * @return SolrDisMaxQuery
     */
    public function setBigramPhraseFields($fields) {}

    /**
     * Add a Trigram Phrase Field (pf3 parameter)
     * output format: field~slop^boost
     *
     * Sample output: title~2^4
     *
     * @see https://cwiki.apache.org/confluence/display/solr/The+DisMax+Query+Parser#TheDisMaxQueryParser-Thepf%28PhraseFields%29Parameter
     * @param string $field
     * @param float $boost
     * @param integer $slop
     * @return SolrDisMaxQuery
     */
    public function addTrigramPhraseField($field, $boost, $slop=null) {}

    /**
     * Removes a Trigram Phrase Field (pf3 parameter)
     * @param string $field
     * @return SolrDisMaxQuery
     */
    public function removeTrigramPhraseField($field) {}

    /**
     * Sets pf3 parameter
     *
     * @param string $fields
     * @return SolrDisMaxQuery
     */
    public function setTrigramPhraseFields($fields) {}

    /**
     * Set Trigram Phrase Slop (ps3 parameter)
     *
     * @see https://cwiki.apache.org/confluence/display/solr/The+Extended+DisMax+Query+Parser
     *
     * @param integer $slop
     * @return SolrDisMaxQuery
     */
    public function setTrigramPhraseSlop ($slop) {}

    /**
     * Adds a field to User Fields Parameter (uf)
     *
     * Specifies which schema fields the end user shall be allowed to query for explicitly.
     * This parameter supports wildcards.
     *
     * @param string $field
     * @return SolrDisMaxQuery
     */
    public function addUserField($field){}

    /**
     * Removes a field from User Fields Parameter (uf)
     *
     * @param string $field
     * @return SolrDisMaxQuery
     */
    public function removeUserField($field){}

    /**
     * Sets User Fields parameter (uf)
     *
     * Specifies which schema fields the end user shall be allowed to query for explicitly.
     * This parameter supports wildcards.
     *
     * @param string $fields
     * @return SolrDisMaxQuery
     */
    public function setUserFields($fields){}

}

/**
 * Collapses the result set to a single document per group before it forwards 
 * the result set to the rest of the search components.
 * So all downstream components (faceting, highlighting, etc...) will work with 
 * the collapsed result set.
 * 
 * @see https://cwiki.apache.org/confluence/display/solr/Collapse+and+Expand+Results
 * 
 * @author Omar Shaban <omars@php.net>
 */
class SolrCollapseFunction
{

    const NULLPOLICY_IGNORE = 'ignore';

    const NULLPOLICY_EXPAND = 'expand';

    const NULLPOLICY_COLLAPSE = 'collapse';

    /**
     * Accepts the field to collapse on.
     *
     * @param string $field
     */
    public function __construct($field = null) {}

    /**
     * Set the field that is being collapsed on.
     * The field must be a single valued String, Int or Float.
     *
     * @param string $field
     * @return SolrCollapseFunction
     */
    public function setField($field) {}

    /**
     * Get the field that is being collapsed on
     * 
     * @return string
     */
    public function getField() {}

    /**
     * Selects the group heads by the max value of a numeric field or function query.
     *
     * @param string $max            
     * @return SolrCollapseFunction
     */
    public function setMax($max) {}

    /**
     * Get max
     * 
     * @return string
     */
    public function getMax() {}

    /**
     * Sets the initial size of the collapse data structures when collapsing on a numeric field only
     *
     * @param string $min
     * @return SolrCollapseFunction
     */
    public function setMin($min) {}

    /**
     * Return min parameter
     * 
     * @return string
     */
    public function getMin() {}

    /**
     * Currently there is only one hint available "top_fc", which stands for top level FieldCache
     * 
     * @param string $hint
     * @return SolrCollapseFunction
     */
    public function setHint($hint) {}

    /**
     * Get collapse hint
     * 
     * @return string
     */
    public function getHint() {}

    /**
     * Sets the NULL Policy.
     * Accepts ignore, expand, or collapse
     *
     * @param string $nullPolicy
     * @return SolrCollapseFunction
     */
    public function setNullPolicy($nullPolicy) {}

    /**
     * Returns null policy
     * 
     * @return string
     */
    public function getNullPolicy() {}

    /**
     * Sets the initial size of the collapse data structures when collapsing on a numeric field only
     * 
     * @param integer $size 
     * @return SolrCollapseFunction
     */
    public function setSize($size) {}

    /**
     * Gets the initial size of the collapse data structures when collapsing on a numeric field only
     * 
     * @return integer
     */
    public function getSize() {}

    public function __toString() {}
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

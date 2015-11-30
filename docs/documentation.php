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
define('SOLR_MINOR_VERSION', 3);
define('SOLR_PATCH_VERSION', 0);

define('SOLR_EXTENSION_VERSION', '2.3.0');

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
 * This is the base class for all exception thrown by the Solr extension classes.
 *
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrException extends Exception
{

    /* Properties */
    protected $sourceline;

    protected $sourcefile;

    protected $zif_name;

    /**
     * Returns internal information where the Exception was thrown
     * @return array
     * @link http://docs.php.net/manual/en/solrexception.getinternalinfo.php
     */
    public function getInternalInfo() {}
}

/**
 * An exception thrown when there is an error while making a request to the server from the client.
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrClientException extends SolrException
{
    /**
     * Returns internal information where the Exception was thrown
     *
     * @return array
     * @link http://docs.php.net/manual/en/solrclientexception.getinternalinfo.php
     */
    public function getInternalInfo() {}
}

/**
 * Used for Solr Related Exceptions
 *
 * @author Omar Shaban <omars@php.net>
 */
class SolrServerException extends SolrException
{
    /**
     * Returns internal information where the Exception was thrown
     *
     * @return array
     * @link http://docs.php.net/manual/en/solrserverexception.getinternalinfo.php
     */
    public function getInternalInfo() {}
}

/**
 * This object is thrown when an illeglal or invalid argument is passed to a method.
 *
 * @link http://docs.php.net/manual/en/class.solrillegalargumentexception.php
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrIllegalArgumentException extends SolrException
{
    /**
     * Returns internal information where the Exception was thrown
     * @return string
     * @link http://docs.php.net/manual/en/solrillegalargumentexception.getinternalinfo.php
     */
    public function getInternalInfo() {}
}

/**
 * @link http://docs.php.net/manual/en/class.solrillegaloperationexception.php
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrIllegalOperationException extends SolrException
{
    /**
     * Returns internal information where the Exception was thrown
     *
     * @return string
     * @link http://docs.php.net/manual/en/solrillegaloperationexception.getinternalinfo.php
     */
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
     * @link http://docs.php.net/manual/en/solrutils.digestxmlresponse.php
     */
    public static function digestXmlResponse($xmlresponse, $parse_mode = 0) {}

    /**
     * Escapes a lucene query string
     *
     * @param string $str String to be escaped
     * @return string
     * @link http://docs.php.net/manual/en/solrutils.escapequerychars.php
     */
    public static function escapeQueryChars($str) {}

    /**
     * Returns the current version of the Solr extension
     * @return string
     * @link http://docs.php.net/manual/en/solrutils.getsolrversion.php
     */
    public static function getSolrVersion() {}

    /**
     * Prepares a phrase from an unescaped lucene string
     *
     * @param string $str
     * @return string
     * @link http://docs.php.net/manual/en/solrutils.queryphrase.php
     */
    public static function queryPhrase($str) {}
}

/**
 * Represents a field in a Solr document. All its properties are read-only.
 *
 * @author Israel Ekpo <iekpo@php.net>
 */
class SolrDocumentField
{

    /**
     * The name of the field
     *
     * @var string
     */
    public $name;

    /**
     * The boost value for the field
     *
     * @var float
     */
    public $boost;

    /**
     * An array of values for this field
     * @var array
     */
    public $values;

    /**
     * Constructor
     */
    public function __construct() {}

    /**
     * Destructor
     */
    public function __destruct() {}
}

/**
 * Represents a Solr document that is about to be submitted to the Solr index
 *
 * @link http://docs.php.net/manual/en/class.solrinputdocument.php
 * @author Israel Ekpo <iekpo@php.net>
 */
final class SolrInputDocument
{
    /**
     * Sorts the fields in ascending order
     */
    const SORT_DEFAULT = 1 ;

    /**
     * Sorts the fields in ascending order
     */
    const SORT_ASC = 1 ;

    /**
     * Sorts the fields in descending order
     */
    const SORT_DESC = 2 ;

    /**
     * Sorts the fields by name
     */
    const SORT_FIELD_NAME = 1 ;

    /**
     * Sorts the fields by number of values
     */
    const SORT_FIELD_VALUE_COUNT = 2 ;

    /**
     * Sorts the fields by boost value
     */
    const SORT_FIELD_BOOST_VALUE = 4 ;

    /**
     * Adds a field to the document
     *
     * @param string $fieldName The name of the field
     * @param string $fieldValue The value for the field
     * @param float $fieldBoostValue The index time boost for the field. Though this cannot be negative, you can still pass values less than 1.0 but they must be greater than zero.
     * @link http://docs.php.net/manual/en/solrinputdocument.addfield.php
     */
    public function addField($fieldName, $fieldValue, $fieldBoostValue = 0.0) {}

    /**
     * Resets the document by dropping all the fields and resets the document boost to zero
     *
     * @link http://docs.php.net/manual/en/solrinputdocument.clear.php
     * @return bool Returns TRUE on success or FALSE on failure
     */
    public function clear() {}

    public function __clone() {}
    public function __construct() {}
    public function __destruct() {}

    /**
     * Removes a field from the document
     * @param string $fieldName
     * @link http://docs.php.net/manual/en/solrinputdocument.deletefield.php
     */
    public function deleteField($fieldName) {}

    /**
     * Checks if a field exists
     *
     * @param $fieldName
     * @return bool
     * @link http://docs.php.net/manual/en/solrinputdocument.fieldexists.php
     */
    public function fieldExists($fieldName) {}

    /**
     * Retrieves the current boost value for the document
     *
     * @return float
     * @link http://docs.php.net/manual/en/solrinputdocument.getboost.php
     */
    public function getBoost() {}

    /**
     * Retrieves a field by name
     *
     * @param string $fieldName
     * @return SolrDocumentField
     */
    public function getField($fieldName) {}

    /**
     * Retrieves the boost value for a particular field
     *
     * @param string $fieldName
     * @return float
     * @link http://docs.php.net/manual/en/solrinputdocument.getfieldboost.php
     */
    public function getFieldBoost($fieldName) {}

    /**
     * Returns the number of fields in the document
     *
     * @return int
     * @link http://docs.php.net/manual/en/solrinputdocument.getfieldcount.php
     */
    public function getFieldCount() {}

    /**
     * Returns an array containing all the fields in the document
     *
     * @return array
     * @link http://docs.php.net/manual/en/solrinputdocument.getfieldnames.php
     */
    public function getFieldNames() {}

    /**
     * Merges one input document into another
     *
     * @param SolrInputDocument $sourceDoc
     * @param bool              $overwrite
     * @link http://docs.php.net/manual/en/solrinputdocument.merge.php
     */
    public function merge(SolrInputDocument $sourceDoc, $overwrite = true) {}

    /**
     * This is an alias of SolrInputDocument::clear
     *
     * @return bool
     * @link http://docs.php.net/manual/en/solrinputdocument.reset.php
     */
    public function reset() {}

    /**
     * Sets the boost value for this document
     *
     * @param float $documentBoostValue
     * @link http://docs.php.net/manual/en/solrinputdocument.setboost.php
     */
    public function setBoost($documentBoostValue) {}

    /**
     * Sets the index-time boost value for a field
     *
     * @param string $fieldName
     * @param float  $fieldBoostValue
     * @link http://docs.php.net/manual/en/solrinputdocument.setfieldboost.php
     */
    public function setFieldBoost($fieldName, $fieldBoostValue) {}

    /**
     * Sorts the fields within the document
     *
     * @param int $sortOrderBy
     * @param int $sortDirection One of the SolrInputDocument::SORT_* constants
     * @link http://docs.php.net/manual/en/solrinputdocument.sort.php
     */
    public function sort($sortOrderBy, $sortDirection = SolrInputDocument::SORT_ASC) {}

    /**
     * Returns an array representation of the input document
     *
     * @return array
     * @link http://docs.php.net/manual/en/solrinputdocument.toarray.php
     */
    public function toArray() {}

    /**
     * Adds a child document
     *
     * @param SolrInputDocument $child
     * @return void
     * @throws SolrIllegalArgumentException
     * @throws SolrException
     */
    public function addChildDocument(SolrInputDocument $child) {}
    
    /**
     * Adds child documents
     *
     * @param array $children
     * @return void
     * @throws SolrIllegalArgumentException
     * @throws SolrException
     */
    public function addChildDocuments(array $children) {}

    /**
     * Whether this input document has child documents
     *
     * @return bool
     */
    public function hasChildDocuments() {}
    
    /**
     * Returns an array of child documents (SolrInputDocument)
     *
     * @return array
     */
    public function getChildDocuments() {}

    /**
     * Returns the number of child documents
     *
     * @return int
     */
    public function getChildDocumentsCount() {}
}

/**
 * Represents a Solr document retrieved from a query response
 *
 * @link http://docs.php.net/manual/en/class.solrdocument.php
 * @author Israel Ekpo <iekpo@php.net>
 * @author Omar Shaban <omars@php.net>
 */
final class SolrDocument implements ArrayAccess, Iterator, Serializable
{
    const SORT_DEFAULT = 1 ;
    const SORT_ASC = 1 ;
    const SORT_DESC = 2 ;
    const SORT_FIELD_NAME = 1 ;
    const SORT_FIELD_VALUE_COUNT = 2 ;
    const SORT_FIELD_BOOST_VALUE = 4 ;

    public function __construct() {}
    public function __clone() {}
    public function __destruct() {}

    /**
     * Adds a field to the document
     *
     * @param string $fieldName
     * @param string $fieldValue
     * @return Returns TRUE on success or FALSE on failure
     * @link http://docs.php.net/manual/en/solrdocument.addfield.php
     */
    public function addField($fieldName,  $fieldValue) {}

    /**
     * Drops all the fields in the document
     *
     * @return Returns TRUE on success or FALSE on failure
     * @link http://docs.php.net/manual/en/solrdocument.addfield.php
     */
    public function clear() {}

    /**
     * Retrieves the current field
     *
     * @return SolrDocumentField
     * @link http://docs.php.net/manual/en/solrdocument.current.php
     */
    public function current() {}

    /**
     * Removes a field from the document
     *
     * @param string $fieldName
     * @link http://docs.php.net/manual/en/solrdocument.deletefield.php
     */
    public function deleteField($fieldName) {}

    /**
     * Checks if a field exists in the document
     * @param string $fieldName
     * @return Returns TRUE if the field is present and FALSE if it does not
     * @link http://docs.php.net/manual/en/solrdocument.fieldexists.php
     */
    public function fieldExists($fieldName) {}

    /**
     * Magic method for accessing the field as a property
     *
     * @param string $fieldName
     * @link http://docs.php.net/manual/en/solrdocument.get.php
     */
    public function __get($fieldName) {}

    /**
     * Retrieves a field by name
     *
     * @param string $fieldName
     * @return SolrDocumentField
     */
    public function getField($fieldName) {}

    /**
     * Returns the number of fields in this document. Multi-value fields are only counted once.
     *
     * @return int
     * @link http://docs.php.net/manual/en/solrdocument.getfieldcount.php
     */
    public function getFieldCount() {}

    /**
     * Returns an array of fields names in the document
     *
     * @return array
     * @link http://docs.php.net/manual/en/solrdocument.getfieldcount.php
     */
    public function getFieldNames() {}

    /**
     * Returns a SolrInputDocument equivalent of the object
     *
     * @return SolrInputDocument
     * @link http://docs.php.net/manual/en/solrdocument.getinputdocument.php
     */
    public function getInputDocument() {}

    public function __isset($fieldName) {}

    public function key() {}

    /**
     * Merges source to the current SolrDocument
     *
     * @param SolrDocument $sourceDoc
     * @param bool         $overwrite
     * @link http://docs.php.net/manual/en/solrdocument.merge.php
     */
    public function merge(SolrDocument $sourceDoc, $overwrite = true) {}

    public function next() {}

    public function offsetExists($fieldName) {}

    public function offsetGet($fieldName) {}

    public function offsetSet($fieldName, $fieldValue) {}

    public function offsetUnset($fieldName) {}

    public function reset() {}

    public function rewind() {}

    public function serialize() {}

    public function __set($fieldName, $fieldValue) {}

    public function sort($sortOrderBy, $sortDirection) {}

    public function toArray() {}

    public function unserialize($serialized) {}

    public function __unset($fieldName) {}

    public function valid() {}

    /**
     * Checks whether this document contains child documents
     *
     * @return bool
     */
    public function hasChildDocuments() {}

    /**
     * Returns an array of child documents (SolrDocument)
     *
     * @return array
     */
    public function getChildDocuments() {}

    /**
     * Returns the number of child documents
     *
     * @return int
     */
    public function getChildDocumentsCount() {}
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
final class SolrClient
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
     * @param array $docs An array of SolrInputDocument objects
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
	
    /**
     * Get Document By Id. Utilizes Solr Realtime Get (RTG).
     *
     * @param string $id
     * @return SolrQueryResponse
     */
    public function getById($id) {}

    /**
     * Get Documents by their Ids. Utilizes Solr Realtime Get (RTG).
     *
     * @param array $ids
     * @return SolrQueryResponse
     */
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
     * @param bool $softCommit
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
    public function query(SolrParams $query) {}

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
     * @param int    $type
     * @param string $value
     *
     * @return bool
     * @link http://docs.php.net/manual/en/solrclient.setservlet.php
     */
    public function setServlet($type, $value) {}

    /**
     * Checks the threads status
     *
     * @return SolrGenericResponse
     * @link http://docs.php.net/manual/en/solrclient.threads.php
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
     * Enables or disables moreLikeThis
     *
     * @param bool $flag TRUE enables it and FALSE turns it off
     *
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setmlt.php
     */
    public function setMlt($flag) {}

    /**
     * Set if the query will be boosted by the interesting term relevance
     *
     * @param bool $flag
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setmltboost.php
     */
    public function setMltBoost($flag) {}

    /**
     * Set the number of similar documents to return for each result
     *
     * @param int $count
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setmltcount.php
     */
    public function setMltCount($count) {}

    /**
     * Sets the maximum number of query terms included
     *
     * @param int $value The maximum number of query terms that will be included in any generated query
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setmltmaxnumqueryterms.php
     */
    public function setMltMaxNumQueryTerms($value) {}

    /**
     * Specifies the maximum number of tokens to parse
     *
     * @param int $value The maximum number of tokens to parse
     *
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setmltmaxnumtokens.php
     */
    public function setMltMaxNumTokens($value) {}

    /**
     * Sets the maximum word length
     *
     * @param int $maxWordLength The maximum word length above which words will be ignored
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setmltmaxwordlength.php
     */
    public function setMltMaxWordLength($maxWordLength) {}

    /**
     * The frequency at which words will be ignored which do not occur in at least this many docs
     *
     * @param int $minDocFrequency
     *
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setmltmindocfrequency.php
     */
    public function setMltMinDocFrequency($minDocFrequency) {}

    /**
     * Sets the frequency below which terms will be ignored in the source docs
     *
     * @param int $minTermFrequency
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setmltmintermfrequency.php
     */
    public function setMltMinTermFrequency($minTermFrequency) {}

    /**
     * Sets the minimum word length below which words will be ignored
     *
     * @param int $minWordLength
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setmltminwordlength.php
     */
    public function setMltMinWordLength($minWordLength) {}

    /**
     * Exclude the header from the returned results
     *
     * @param bool $flag TRUE excludes the header from the result
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setomitheader.php
     */
    public function setOmitHeader($flag) {}

    /**
     * Sets the search query
     *
     * @param string $query
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setquery.php
     */
    public function setQuery($query) {}

    /**
     * Specifies the maximum number of rows to return in the result
     *
     * @param int $rows
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setrows.php
     */
    public function setRows($rows) {}

    /**
     * Flag to show debug information
     *
     * @param bool $flag
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setshowdebuginfo.php
     */
    public function setShowDebugInfo($flag) {}

    /**
     * Specifies the number of rows to skip
     *
     * @param int $start
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setstart.php
     */
    public function setStart($start) {}

    /**
     * Enables or disables the Stats component
     *
     * @param bool $flag
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setstats.php
     */
    public function setStats($flag) {}

    /**
     * Enables or disables the TermsComponent
     *
     * @param bool $flag
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.setterms.php
     */
    public function setTerms($flag) {}

    /**
     * Sets the name of the field to get the Terms from
     *
     * @param string $fieldname
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.settermsfield.php
     */
    public function setTermsField($fieldname) {}

    /**
     * Sets whether to include the lower bound term in the result set
     *
     * @param bool $flag
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.settermsincludelowerbound.php
     */
    public function setTermsIncludeLowerBound($flag) {}

    /**
     * Include the upper bound term in the result set
     *
     * @param bool $flag
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.settermsincludeupperbound.php
     */
    public function setTermsIncludeUpperBound($flag) {}

    /**
     * Sets the maximum number of terms to return
     *
     * @param int $limit
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.settermslimit.php
     */
    public function setTermsLimit($limit) {}

    /**
     * Specifies the Term to start from
     *
     * @param string $lowerBound
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.settermslowerbound.php
     */
    public function setTermsLowerBound($lowerBound) {}

    /**
     * Sets the maximum document frequency
     *
     * @param int $frequency
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.settermsmaxcount.php
     */
    public function setTermsMaxCount($frequency) {}

    /**
     * Sets the minimum document frequency
     *
     * @param int $frequency
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.settermsmincount.php
     */
    public function setTermsMinCount($frequency) {}

    /**
     * Restrict matches to terms that start with the prefix
     *
     * @param string $prefix
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.settermsprefix.php
     */
    public function setTermsPrefix($prefix) {}

    /**
     * Return the raw characters of the indexed term
     *
     * @param bool $flag
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.settermsreturnraw.php
     */
    public function setTermsReturnRaw($flag) {}

    /**
     * Specifies how to sort the returned terms
     *
     * @param int $sortType If SolrQuery::TERMS_SORT_COUNT, sorts the terms by the term frequency (highest count first). If SolrQuery::TERMS_SORT_INDEX, returns the terms in index order
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.settermssort.php
     */
    public function setTermsSort($sortType) {}

    /**
     * Sets the term to stop at
     *
     * @param string $upperBound
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.settermsupperbound.php
     */
    public function setTermsUpperBound($upperBound) {}

    /**
     * The time allowed for search to finish
     *
     * @param int $timeAllowed Time in milliseconds
     * @return SolrQuery Returns the current SolrQuery object
     * @link http://docs.php.net/manual/en/solrquery.settimeallowed.php
     */
    public function setTimeAllowed($timeAllowed) {}

    /**
     * Collapses the result set to a single document per group before it forwards
     * the result set to the rest of the search components.
     * So all downstream components (faceting, highlighting, etc...) will work with
     * the collapsed result set.
     *
     * A collapse function object is passed to collapse the query
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
     * Adds a group sort field (group.sort parameter).
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
     * If this parameter is set to simple, the grouped documents are presented in a single flat list, and the start and 
     * rows parameters affect the numbers of documents instead of groups.
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
     * If true, the result of the first field grouping command is used as the main result list in the response, using group.format=simple.
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
     * The default value is false. (group.ngroups parameter)
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
     * Returns the group.facet parameter value
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
     * @throws SolrIllegalArgumentException
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
     * @param integer $direction defaults to DESC
     * @return SolrQuery
     */
    public function addExpandSortField($sort, $direction = SolrQuery::ORDER_DESC) {}

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
     *
     * @param string $q
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
     * In order to collapse a result. The field type must be a single valued String, Int or Float.
     *
     * @param string $field
     * @return SolrCollapseFunction
     */
    public function setField($field) {}

    /**
     * Get the field that is being collapsed on.
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
     * Sets the initial size of the collapse data structures when collapsing on a numeric field only.
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
     * Currently there is only one hint available "top_fc", which stands for top level FieldCache.
     *
     * @param string $hint
     * @return SolrCollapseFunction
     */
    public function setHint($hint) {}

    /**
     * Get collapse hint.
     *
     * @return string
     */
    public function getHint() {}

    /**
     * Sets the NULL Policy.
     * Accepts ignore, expand, or collapse.
     *
     * @param string $policy
     * @return SolrCollapseFunction
     */
    public function setNullPolicy($policy) {}

    /**
     * Returns null policy
     *
     * @return string
     */
    public function getNullPolicy() {}

    /**
     * Sets the initial size of the collapse data structures when collapsing on a numeric field only.
     *
     * @param integer $size
     * @return SolrCollapseFunction
     */
    public function setSize($size) {}

    /**
     * Gets the initial size of the collapse data structures when collapsing on a numeric field only.
     *
     * @return integer
     */
    public function getSize() {}

    /**
     * A string representation (Solr LocalParams) of the function.
     * @return string
     */
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

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
   | Author: Israel Ekpo <iekpo@php.net>                                  |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

/* {{{ class SolrException extends Exception */
class SolrException extends Exception
{

}
/* }}} */

/* {{{ class SolrIllegalOperationException extends SolrException */
class SolrIllegalOperationException extends SolrException
{

}
/* }}} */

/* {{{ class SolrIllegalArgumentException extends SolrException */
class SolrIllegalArgumentException extends SolrException
{

}
/* }}} */

/* {{{ class SolrClientException extends SolrException */
class SolrClientException extends SolrException
{

}
/* }}} */

 /* {{{ class SolrObject implements ArrayAccess */
class SolrObject implements ArrayAccess
{
    /**
     * Returns the requested property
     *
     * @return mixed
     */
    public function __get($property_name)
    {

    }

    /**
     * Sets the property to the target value
     *
     * @param string $property_name
     * @param mixed $value
     */
    public function __set($property_name, $value)
    {

    }

    /**
     * Checks if $property_name exists
     *
     * @return bool
     */
    public function __isset($property_name)
    {

    }

    /**
     * Removes $property_name
     *
     * @return void
     */
    public function __unset($property_name)
    {

    }

    /**
     * Sets the $key to $value
     *
     * @param string $key
     * @param mixed $value
     */
    public function offsetSet($key, $value)
    {

    }

    /**
     * Returns the requested $key
     *
     * @param string $key
     * @return mixed
     */
    public function offsetGet($key)
    {

    }

    /**
     * Checks if the request key exists
     *
     * @param string $key
     * @return bool
     */
    public function offsetExists($key)
    {

    }

    /**
     * Removes the specified key
     *
     * @param string $key
     * @return bool
     */
    public function offsetUnset($key)
    {

    }

    /**
     * Returns the property names for this object
     *
     * @return array
     */
    public function getPropertyNames()
    {

    }
}
/* }}} */

/* {{{ abstract class SolrResponse */
abstract class SolrResponse
{
    /**
     * To treat documents as SolrObject instances
     */
    const PARSE_SOLR_OBJ = 0;

    /**
     * To treat documents as SolrDocument instances
     */
    const PARSE_SOLR_DOC = 1;

    /**
     * Returns the HTTP status
     *
     * @return int The HTTP status of the Solr server.
     */
    public function getHttpStatus()
    {

    }

    /**
     * Returns the HTTP status message
     *
     * @return string
     */
    public function getHttpStatusMessage()
    {

    }

    /**
     * Returns a value to indicate if the request as successfull
     *
     * @return bool
     */
    public function success()
    {

    }

    /**
     * Returns the requested URL
     *
     * @return string
     */
    public function getRequestUrl()
    {

    }

    /**
     * Returns the headers
     *
     * @return string
     */
    public function getRawRequestHeaders()
    {

    }

    /**
     * Returns the raw request
     *
     * @return string
     */
    public function getRawRequest()
    {

    }

    /**
     * Returns the raw response headers
     *
     * @return string
     */
    public function getRawResponseHeaders()
    {

    }

    /**
     * Returns raw request
     *
     * @return response
     */
    public function getRawResponse()
    {

    }

    /**
     * Returns digested response
     *
     * @return response
     */
    public function getDigestedResponse()
    {

    }

    /**
     * Retuns the SolrObject response object.
     *
     * @return SolrObject
     */
    public function getResponse()
    {

    }
}
/* }}} */

/* {{{ final class SolrQueryResponse extends SolrResponse */
final class SolrQueryResponse extends SolrResponse
{

}
/* }}} */

/* {{{ final class SolrUpdateResponse extends SolrResponse */
final class SolrUpdateResponse extends SolrResponse
{

}
/* }}} */

/* {{{ final class SolrPingResponse extends SolrResponse */
final class SolrPingResponse extends SolrResponse
{
    /**
     * Ping requests do not return any response.
     *
     * @return null
     */
    public function getResponse()
    {

    }
}
/* }}} */

/* {{{ final class SolrGenericResponse extends SolrResponse */
final class SolrGenericResponse extends SolrResponse
{

}
/* }}} */

/* {{{ abstract class SolrUtils */
abstract class SolrUtils
{
    /**
     * Escapes the string for use in a lucene query
     *
     * @param string $unescaped
     * @return string The escaped string
     */
    public function escapeQueryChars($unescaped)
    {

    }

    /**
     * Prepares a phrase for use in a Lucene query
     *
     * @param string $unescaped
     * @return string The phrase
     */
    public function queryPhrase($unescaped)
    {

    }

    /**
     * Accepts an XML string and returns a serialized SolrObject
     *
     * When $parse_mode is SolrResponse::PARSE_SOLR_OBJ, solr documents are parsed
     * as SolrObject objects. When it is SolrResponse::PARSE_SOLR_DOC, they are parsed
     * as SolrDocument objects.
     *
     * @param string $xml_string The xml string
     * @param int $parse_mode
     * @return string The serialized SolrObject
     */
    public function digestXmlResponse($xml_string, $parse_mode = SolrResponse::PARSE_SOLR_DOC)
    {

    }

    /**
     * Returns the current Solr extension version
     *
     * @return string
     */
    public function getSolrVersion()
    {

    }

    /**
     * Returns stats info for the current request/thread
     *
     * It returns an array containing information about number of documents,
     * clients or parameter objects.
     *
     * @return array
     */
    public function getSolrStats()
    {

    }
}
/* }}} */

 /* {{{ final class SolrDocumentField */
final class SolrDocumentField
{
    /**
     * Field name
     *
     * @var string $name The name of the field
     */
    public $name;

    /**
     * Boost value
     *
     * @var float $boost The boost value for this field
     */
    public $boost;

    /**
     * Field Values
     *
     * All values are strings.
     *
     * @var array $values An array of values for this field.
     */
    public $values;
}
/* }}} */

/* {{{ final class SolrDocument implements ArrayAccess, Iterator, Serializable */
final class SolrDocument implements ArrayAccess, Iterator, Serializable
{
    const SORT_DEFAULT = 0;

    const SORT_ASC = 0;

    const SORT_DESC = 1;

    const SORT_FIELD_NAME = 1;

    const SORT_FIELD_VALUE_COUNT = 2;

    const SORT_FIELD_BOOST_VALUE = 4;

    public function __construct()
    {

    }

    public function __destruct()
    {

    }

    public function __clone()
    {

    }

    /**
     * Returns the field
     *
     * @param string $field_name
     * @return SolrDocumentField
     */
    public function __get($field_name)
    {

    }

    /**
     * Adds a value to a field
     *
     * @param string $field_name
     * @param string $value
     */
    public function __set($field_name, $value)
    {

    }

    /**
     * Checks if a particular field exists
     *
     * @param string $field_name
     * @return bool
     */
    public function __isset($field_name)
    {

    }

    /**
     * Removes the field
     *
     * @param string $field_name
     */
    public function __unset($field_name)
    {

    }

    /**
     * Adds a value to a field
     *
     * @param string $field_name
     * @param string $value
     */
    public function offsetSet($field_name, $value)
    {

    }

    /**
     * Returns the field
     *
     * @param string $field_name
     * @return SolrDocumentField
     */
    public function offsetGet($field_name)
    {

    }

    /**
     * Checks if a particular field exists
     *
     * @param string $field_name
     * @return bool
     */
    public function offsetExists($field_name)
    {

    }

    /**
     * Removes the field
     *
     * @param string $field_name
     */
    public function offsetUnset($field_name)
    {

    }

    /**
     * Returns the current field
     *
     * @return SolrDocumentField
     */
    public function current()
    {

    }

    /**
     * Returns the current key
     *
     * @return string
     */
    public function key()
    {

    }

    /**
     * Moves the internal pointer to the next field
     *
     * @return void
     */
    public function next()
    {

    }

    /**
     * Resets the internal pointer
     *
     * @return void
     */
    public function rewind()
    {

    }

    /**
     * Checks if the current position is still valid
     *
	 * @return bool
     */
    public function valid()
    {
    	return true;
    }

    /**
     * Used for custom serialization
     *
     * @return string
     */
    public function serialize()
    {
        return "";
    }

    /**
     * Used for custom serialization
     *
     * Accepts the serialized XML string and springs the object back to live
     *
     * @param string $serialized
     * @return void
     */
    public function unserialize($serialized)
    {

    }

    /**
     * Discards all the fields in this object and resets
     * the document boost value to zero.
     *
     * @return bool
     */
    public function clear()
    {
        return true;
    }

    /**
     * An alias of clear()
     *
     * @see SolrDocument::clear()
     *
     * @return bool
     */
    public function reset()
    {
        return true;
    }

    /**
     * Adds a field to this document
     *
     * @param string $fieldname
     * @param string $value
     */
    public function addField($fieldname, $value)
    {
        return true;
    }

    /**
     * Returns an array of fields in the document
     *
     * @return array
     */
    public function getFieldNames()
    {
        return array('');
    }

    /**
     * Returns the number of fields in this document
     *
     * @return int
     */
    public function getFieldCount()
    {
        return 0;
    }

    /**
     * Returns the specified field
     *
     * @param string $field_name
     * @return SolrDocumentField
     */
    public function getField($field_name)
    {
        return new SolrDocumentField();
    }

    /**
     * Returns an array representation of the document
     *
     * @return array
     */
    public function toArray()
    {
        return array();
    }

    /**
     * Checks if the specified field exists in this document
     *
     * @param string $field_name
     * @return bool
     */
    public function fieldExists($field_name)
    {
        return true;
    }

    /**
     * Removes a particular field from the document
     *
     * @param string $field_name
     * @return bool
     */
    public function deleteField($field_name)
    {
        return true;
    }

    /**
     * Rearranges the fields in the document
     *
     * The fields are rearranged according to the specified criteria and
     * sort direction
     *
     * Fields can be sorted by boost values, field names and number of values.
     *
     * The $order_by parameter must be one of :
     *
     * - SolrDocument::SORT_FIELD_NAME
     * - SolrDocument::SORT_FIELD_BOOST_VALUE
     * - SolrDocument::SORT_FIELD_VALUE_COUNT
     *
     * The sort direction can be one of :
     *
     * - SolrDocument::SORT_DEFAULT
     * - SolrDocument::SORT_ASC
     * - SolrDocument::SORT_DESC
     *
     * @param int $order_by The sort criterion
     * @param int $sort_direction The sort direction
     * @return bool
     */
    public function sort($order_by, $sort_direction = SolrDocument::SORT_DEFAULT)
    {
        return true;
    }

    /**
     * Merges the source document into the current object
     *
     * Source document should not be empty
     *
     * If $overwrite is true, then matching fields in the target document will be
     * replaced with the ones from the source.
     *
     * @param SolrDocument $source_document
     * @param bool $overwrite
     * @return bool
     */
    public function merge($source_document, $overwrite = false)
    {
        return true;
    }

    /**
     * Returns a SolrInputDocument equivalent of this object
     *
     * @return SolrInputDocument
     */
    public function getInputDocument()
    {
        return new SolrInputDocument();
    }
}
/* }}} */

 /* {{{ final class SolrInputDocument */
final class SolrInputDocument
{
    const SORT_DEFAULT = 0;

    const SORT_ASC = 0;

    const SORT_DESC = 1;

    const SORT_FIELD_NAME = 1;

    const SORT_FIELD_VALUE_COUNT = 2;

    const SORT_FIELD_BOOST_VALUE = 4;

    public function __construct()
    {

    }

    public function __destruct()
    {

    }

    public function __clone()
    {

    }

    /**
     * Sets the boost value for the document
     *
     * @param float $document_boost
     * @return bool
     */
    public function setBoost($document_boost)
    {
        return true;
    }

    /**
     * Retrieves the boost value for the document
     *
     * @return float
     */
    public function getBoost()
    {

    }

    /**
     * Discards all the fields in this object and resets
     * the document boost value to zero.
     *
     * @return bool
     */
    public function clear()
    {
        return true;
    }

    /**
     * An alias of clear()
     *
     * @see SolrInputDocument::clear()
     *
     * @return bool
     */
    public function reset()
    {
        return true;
    }

    /**
     * Adds a field to this document
     *
     * @param string $fieldname
     * @param string $value
     * @param float $field_boost
     */
    public function addField($fieldname, $value, $field_boost = 0.0)
    {
        return true;
    }

    /**
     * Returns an array of fields in the document
     *
     * @return array
     */
    public function getFieldNames()
    {
        return array('');
    }

    /**
     * Returns the number of fields in this document
     *
     * @return int
     */
    public function getFieldCount()
    {
        return 0;
    }

    /**
     * Returns the specified field
     *
     * @param string $field_name
     * @return SolrDocumentField
     */
    public function getField($field_name)
    {
        return new SolrDocumentField();
    }

    /**
     * Returns an array representation of the document
     *
     * @return array
     */
    public function toArray()
    {
        return array();
    }

    /**
     * Checks if the specified field exists in this document
     *
     * @param string $field_name
     * @return bool
     */
    public function fieldExists($field_name)
    {
        return true;
    }

    /**
     * Removes a particular field from the document
     *
     * @param string $field_name
     * @return bool
     */
    public function deleteField($field_name)
    {
        return true;
    }

    /**
     * Rearranges the fields in the document
     *
     * The fields are rearranged according to the specified criteria and
     * sort direction
     *
     * Fields can be sorted by boost values, field names and number of values.
     *
     * The $order_by parameter must be one of :
     *
     * - SolrInputDocument::SORT_FIELD_NAME
     * - SolrInputDocument::SORT_FIELD_BOOST_VALUE
     * - SolrInputDocument::SORT_FIELD_VALUE_COUNT
     *
     * The sort direction can be one of :
     *
     * - SolrInputDocument::SORT_DEFAULT
     * - SolrInputDocument::SORT_ASC
     * - SolrInputDocument::SORT_DESC
     *
     * @param int $order_by The sort criterion
     * @param int $sort_direction The sort direction
     * @return bool
     */
    public function sort($order_by, $sort_direction = SolrInputDocument::SORT_DEFAULT)
    {
        return true;
    }

    /**
     * Merges the source document into the current object
     *
     * Source document should not be empty
     *
     * If $overwrite is true, then matching fields in the target document will be
     * replaced with the ones from the source.
     *
     * @param SolrInputDocument $source_document
     * @param bool $overwrite
     * @return bool
     */
    public function merge($source_document, $overwrite = false)
    {
        return true;
    }
}
/* }}} */

/* {{{ abstract class SolrParams implements Serializable */
abstract class SolrParams implements Serializable
{
    /**
     * Used for custom serialization
     *
     * @return string
     */
    public function serialize()
    {
        return "";
    }

    /**
     * Used for custom serialization
     *
     * @param string $serialized
     */
    public function unserialize($serialized)
    {

    }

    /**
     * Sets the parameter to the specified value
     *
     * @param string $param_name
     * @param string $value
     * @return SolrParams
     */
    public function setParam($param_name, $value)
    {

    }

    /**
     * Adds another parameter of the same name to the name-value request
     *
     * @param string $param_name
     * @param string $value
     * @return SolrParams
     */
    public function addParam($param_name, $value)
    {

    }

    /**
     * Returns an array of the parameter and thier values
     * without URLencoding the values.
     *
     * @return array
     */
    public function getParams()
    {

    }

    /**
     * Returns a serialized SolrParams object
     *
     * @return string
     */
    public function __toString()
    {

    }

    /**
     * Returns an array of all the parameters and thier values with
     * all the values Urlencoded
     *
     * @return array
     */
    public function getPreparedParams()
    {

    }
}
/* }}} */

/* {{{ class SolrModifiableParams extends SolrParams */
class SolrModifiableParams extends SolrParams
{
    /*
     * Constructor
     *
     */
    public function __construct()
    {

    }

    /**
     * Destructor
     */
    public function __destruct()
    {

    }
}
/* }}} */

/* {{{ class SolrQuery extends SolrModifiableParams */
class SolrQuery extends SolrModifiableParams
{
    const ORDER_ASC = 0;

    const ORDER_DESC = 1;

    const FACET_SORT_INDEX = 0;

    const FACET_SORT_COUNT = 1;

    const TERMS_SORT_INDEX = 0;

    const TERMS_SORT_COUNT = 1;

    /**
     * Constructor
     */
    public function __construct()
    {

    }

    /**
     * Destructor
     */
    public function __destruct()
    {

    }

    /**
     * Sets the q parameter
     *
     * @param string $q
     * @return SolrQuery
     */
    public function setQuery($q)
    {

    }

    /**
     * Sets the start parameter
     *
     * @param string $start
     * @return SolrQuery
     */
    public function setStart($start)
    {

    }

    /**
     * Sets the rows parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setRows($value)
    {

    }

    /**
     * Adds an fl parameter to the object
     *
     * @param string $field
     * @return SolrQuery
     */
    public function addField($field)
    {

    }

    /**
     * Removes an fl parameter from the object
     *
     * @param string $field
     * @return SolrQuery
     */
    public function removeField($field)
    {

    }

    /**
     * Adds a sort parameter to the object
     *
     * @param string $field Name of the sort field
     * @param int $sort_direction SolrQuery::SORT_ASC or SolrQuery::SORT_DESC
     * @return SolrQuery
     */
    public function addSortField($field, $sort_direction)
    {

    }

    /**
     * Removes one of the sort fields
     *
     * @param string $value
     * @return SolrQuery
     */
    public function removeSortField($field)
    {

    }

    /**
     * Removes one of the fiter query
     *
     * @param string $fq
     * @return SolrQuery
     */
    public function addFilterQuery($fq)
    {

    }

    /**
     * Remoes one of the filter queries
     *
     * @param string $value
     * @return SolrQuery
     */
    public function removeFilterQuery($fq)
    {

    }

    /**
     * Enables of disables debugging
     *
     * @param bool $flag
     * @return SolrQuery
     */
    public function setShowDebugInfo($flag)
    {

    }

    /**
     * Sets the explainOther parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setExplainOther($value)
    {

    }

    /**
     * Sets the maximum allowed time for the query in milliseconds
     *
     * @param string $timeAllowed
     * @return SolrQuery
     */
    public function setTimeAllowed($timeAllowed)
    {

    }

    /**
     * Sets the omit Header parameter
     *
     * @param bool $flag
     * @return SolrQuery
     */
    public function setOmitHeader($flag)
    {

    }

    /**
     * Sets the echoHandler parameter
     *
     * @param bool $flag
     * @return SolrQuery
     */
    public function setEchoHandler($flag)
    {

    }

    /**
     * Sets the echoParams parameter
     *
     * The echoParams parameter tells Solr what kinds of Request parameters
     * should be included in the response for debugging purposes,
     * legal values include:
     *
     * - none - don't include any request parameters for debugging
     * - explicit - include the parameters explicitly specified by the client in the request
     * - all - include all parameters involved in this request, either specified explicitly
     * by the client, or implicit because of the request handler configuration.
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setEchoParams($value)
    {

    }

    /**
     * Enables or disables faceting
     *
     * @param bool $flag
     * @return SolrQuery
     */
    public function setFacet($flag)
    {

    }

    /**
     * Adds a facet field to the object
     *
     * @param string $field
     * @return SolrQuery
     */
    public function addFacetField($field)
    {

    }

    /**
     * Removes a facet field
     *
     * @param string $field
     * @return SolrQuery
     */
    public function removeFacetField($field)
    {

    }

    /**
     * Adds a facet query
     *
     * @param string $query
     * @return SolrQuery
     */
    public function addFacetQuery($query)
    {

    }

    /**
     * Removes a facet query
     *
     * @param string $query
     * @return SolrQuery
     */
    public function removeFacetQuery($query)
    {

    }

    /**
     * Sets a facet prefix
     *
     * Accepts an optional field override
     *
     * @param string $prefix
     * @param string $field_override
     * @return SolrQuery
     */
    public function setFacetPrefix($prefix, $field_override = null)
    {

    }

    /**
     * Sets the facet.sort parameter
     *
     * Accepts an optional field override
     *
     * $value must be one of SolrQuery::FACET_SORT_INDEX or SolrQuery::FACET_SORT_COUNT
     *
     * @param int $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setFacetSort($value, $field_override = null)
    {

    }

    /**
     * Sets the facet.limit parameter
     *
     * Accepts an optional field override
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setFacetLimit($value, $field_override = null)
    {

    }

    /**
     * Sets the facet.offset parameter
     *
     * Accepts an optional field override
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setFacetOffset($value, $field_override = null)
    {

    }

    /**
     * Sets the facet.mincount parameter
     *
     * Accepts an optional field override
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setFacetMinCount($value, $field_override = null)
    {

    }

    /**
     * Sets the facet.missing parameter
     *
     * Accepts an optional field override
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setFacetMissing($value, $field_override = null)
    {

    }

    /**
     * Sets the facet.method parameter
     *
     * Accepts an optional field override
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setFacetMethod($value, $field_override = null)
    {

    }

    /**
     * Sets the facet.enum.cache.minDf parameter
     *
     * Accepts an optional field override
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setFacetEnumCacheMinDefaultFrequency($value, $field_override = null)
    {

    }

    /**
     * Adds another date.facet parameter
     *
     * This is the name of the date field
     *
     * @param string $field
     * @return SolrQuery
     */
    public function addFacetDateField($field)
    {

    }

    /**
     * Removes one of the date.facet parameters
     *
     * @param string $field
     * @return SolrQuery
     */
    public function removeFacetDateField($field)
    {

    }

    /**
     * Sets the facet.date.start parameter
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setFacetDateStart($value, $field_override = null)
    {

    }

    /**
     * Sets the facet.date.end parameter
     *
     * Accepts an optional field override.
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setFacetDateEnd($value, $field_override = null)
    {

    }

    /**
     * Sets the facet.date.gap parameter
     *
     * Accepts an optional field override.
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setFacetDateGap($value, $field_override = null)
    {

    }

    /**
     * Sets the facet.date.hardend parameter
     *
     * Accepts an optional field override.
     *
     * @param bool $flag
     * @param string $field_override
     * @return SolrQuery
     */
    public function setFacetDateHardEnd($flag, $field_override = null)
    {

    }

    /**
     * Adds a facet.date.other parameter to the object
     *
     * Accepts an optional field override.
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function addFacetDateOther($value, $field_override = null)
    {

    }

    /**
     * Removes one of the facet.date.other parameter
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function removeFacetDateOther($value, $field_override = null)
    {

    }

    /**
     * Enables or disables highlighting
     *
     * @param bool $flag
     * @return SolrQuery
     */
    public function setHighlight($flag)
    {

    }

    /**
     * Adds a highlight field to the object
     *
     * @param string $field
     * @return SolrQuery
     */
    public function addHighlightField($field)
    {

    }

    /**
     * Removes on of the hl.fl parameters
     *
     * @param string $field
     * @return SolrQuery
     */
    public function removeHighlightField($field)
    {

    }

    /**
     * Sets the hl.snippets parameter
     *
     * Accepts an optional field override
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setHighlightSnippets($value, $field_override = null)
    {

    }

    /**
     * Sets the hl.fragsize parameter
     *
     * Accepts an optional field override.
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setHighlightFragsize($value, $field_override = null)
    {

    }

    /**
     * Sets the hl.mergeContinous parameter
     *
     * Accepts an optional field override
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setHighlightMergeContiguous($value, $field_override = null)
    {

    }

    /**
     * Sets the hl.requireFieldMatch parameter
     *
     * @param bool $flag
     * @return SolrQuery
     */
    public function setHighlightRequireFieldMatch($flag)
    {

    }

    /**
     * Sets the hl.maxAnalyzedChars parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setHighlightMaxAnalyzedChars($value)
    {

    }

    /**
     * Sets the hl.alternateField parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setHighlightAlternateField($value)
    {

    }

    /**
     * Sets the hl.maxAlternateFieldLength parameter
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setHighlightMaxAlternateFieldLength($value, $field_override = null)
    {

    }

    /**
     * Sets the hl.formatter parameter
     *
     * As of Solr 1.4 now the only valid value is 'simple'
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setHighlightFormatter($value, $field_override = null)
    {

    }

    /**
     * Sets the hl.simple.pre parameter
     *
     * Accepts an optional field override
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setHighlightSimplePre($value, $field_override = null)
    {

    }

    /**
     * Sets the hl.simple.post parameter
     *
     * Accepts an optional field override
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setHighlightSimplePost($value, $field_override = null)
    {

    }

    /**
     * Sets the hl.fragmenter parameter
     *
     * @param string $value
     * @param string $field_override
     * @return SolrQuery
     */
    public function setHighlightFragmenter($value, $field_override = null)
    {

    }

    /**
     * Sets the hl.usePhraseHighlighter parameter
     *
     * @param bool $flag
     * @return SolrQuery
     */
    public function setHighlightUsePhraseHighlighter($flag)
    {

    }

    /**
     * Sets the hl.highlightMultiTerm parameter
     *
     * @param bool $flag
     * @return SolrQuery
     */
    public function setHighlightHighlightMultiTerm($flag)
    {

    }

    /**
     * Sets the hl.regex.slop parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setHighlightRegexSlop($value)
    {

    }

    /**
     * Sets the hl.regex.pattern parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setHighlightRegexPattern($value)
    {

    }

    /**
     * Sets the hl.regex.maxAnalyzedChars parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setHighlightRegexMaxAnalyzedChars($value)
    {

    }

    /**
     * Enable or disable the stats component
     *
     * @param bool $flag
     * @return SolrQuery
     */
    public function setStats($flag)
    {

    }

    /**
     * Adds a stats field
     *
     * @param string $field
     * @return SolrQuery
     */
    public function addStatsField($field)
    {

    }

    /**
     * Removes the stats field
     *
     * @param string $field
     * @return SolrQuery
     */
    public function removeStatsField($field)
    {

    }

    /**
     *  Adds a stats.facet parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function addStatsFacet($value)
    {

    }

    /**
     * Removes a stats.facet parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function removeStatsFacet($value)
    {

    }

    /**
     * Enables or disables the moreLikeThis component
     *
     * @param bool $flag
     * @return SolrQuery
     */
    public function setMlt($flag)
    {

    }

    /**
     * Sets the mlt.count parameter
     * @param string $value
     * @return SolrQuery
     */
    public function setMltCount($value)
    {

    }

    /**
     * Adds another mlt.fl parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function addMltField($value)
    {

    }

    /**
     * Removes one of the mlt.fl parameters
     *
     * @param string $value
     * @return SolrQuery
     */
    public function removeMltField($value)
    {

    }

    /**
     * Adds a query field parameter
     *
     * @param string $value
     * @param string $boost_value
     * @return SolrQuery
     */
    public function addMltQueryField($value, $boost_value)
    {

    }

    /**
     * Removes a query field parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function removeMltQueryField($value)
    {

    }

    /**
     * Sets the mlt.mintf parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setMltMinTermFrequency($value)
    {

    }

    /**
     * Sets the mlt.mindf parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setMltMinDocFrequency($value)
    {

    }

    /**
     * Sets the mlt.minwl parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setMltMinWordLength($value)
    {

    }

    /**
     * Sets the mlt.maxwl parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setMltMaxWordLength($value)
    {

    }

    /**
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setMltMaxNumTokens($value)
    {

    }

    /**
     * Sets the mlt.maxntp parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setMltMaxNumQueryTerms($value)
    {

    }

    /**
     * Sets the mlt.maxqt parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setMltBoost($value)
    {

    }

    /**
     * Enables or disables the TermsComponent
     *
     * @param bool $flag
     * @return SolrQuery
     */
    public function setTerms($flag)
    {

    }

    /**
     * Sets the field to be used by the TermsComponent
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setTermsField($field)
    {

    }

    /**
     * Sets the terms.lower parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setTermsLowerBound($value)
    {

    }

    /**
     * Sets the terms.upper parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setTermsUpperBound($value)
    {

    }

    /**
     * Sets the terms.lower.incl parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setTermsIncludeLowerBound($value)
    {

    }

    /**
     * Sets the terms.upper.incl parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setTermsIncludeUpperBound($value)
    {

    }

    /**
     * Sets the terms.mincount parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setTermsMinCount($value)
    {

    }

    /**
     * Sets the terms.maxcount parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setTermsMaxCount($value)
    {

    }

    /**
     * Sets the terms.prefix parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setTermsPrefix($value)
    {

    }

    /**
     * Sets the terms.limit parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setTermsLimit($value)
    {

    }

    /**
     * Sets the terms.raw parameter
     *
     * @param string $value
     * @return SolrQuery
     */
    public function setTermsReturnRaw($value)
    {

    }

    /**
     * Sets the terms.sort parameter
     *
     * $value has to be one of SolrQuery::TERMS_SORT_COUNT or SolrQuery::TERMS_SORT_INDEX
     *
     * @param int $value
     * @return SolrQuery
     */
    public function setTermsSort($value)
    {

    }
}
/* }}} */

 /* {{{ final class SolrClient */
final class SolrClient
{
    const SEARCH_SERVLET_TYPE = 1;

    const UPDATE_SERVLET_TYPE = 2;

    const THREADS_SERVLET_TYPE = 4;

    const PING_SERVLET_TYPE = 8;

    const TERMS_SERVLET_TYPE = 16;

    /**
     * Constructor
     *
     * The array of options includes the following keys
     *
     * - hostname
     * - port
     * - login (for HTTP Authentication)
     * - password (for HTTP Authentication)
     * - path (the path to Solr)
     * - proxy_host
     * - proxy_port
     * - proxy_login
     * - proxy_password
     *
     * @param array $options
     *
     */
    public function __construct($options)
    {

    }

    /**
     * Destructor
     *
     */
    public function __destruct()
    {

    }

    /**
     * Adds a document to the index
     *
     * @param SolrInputDocument $doc
     * @param bool $allowDups
     * @param int $commitWithin Number of milliseconds to wait before commiting.
     * @return SolrUpdateResponse
     */
    public function addDocument(SolrInputDocument $doc, $allowDups = false, $commitWithin = 0)
    {
        return new SolrUpdateResponse();
    }

    /**
     * Adds an array of documents to the index
     *
     * @param array $docs
     * @param bool $allowDups
     * @param int $commitWithin Number of milliseconds to wait before commiting.
     * @return SolrUpdateResponse
     */
    public function addDocuments($docs, $allowDups = false, $commitWithin = 0)
    {
         return new SolrUpdateResponse();
    }

    /**
     * Commits the changes to the index
     *
     * @param bool $waitFlush
     * @param bool $waitSearcher
     * @return SolrUpdateResponse
     */
    public function commit($waitFlush = true, $waitSearcher = true)
    {
        return new SolrUpdateResponse();
    }

    /**
     * Defragments and optimizes the index
     *
     * @param bool $waitFlush
     * @param bool $waitSearcher
     * @return SolrUpdateResponse
     */
    public function optimize($waitFlush = true, $waitSearcher = true)
    {
        return new SolrUpdateResponse();
    }

    /**
     * Rolls back the changes before the last commit
     *
     * @return SolrUpdateResponse
     */
    public function rollback()
    {
        return new SolrUpdateResponse();
    }

    /**
     * Deletes by id
     *
     * @param string $id The value for the ID (uniqueKey) field
     * @return SolrUpdateResponse
     */
    public function deleteById($id)
    {
        return new SolrUpdateResponse();
    }

    /**
     * Delete by ids
     *
     * Deletes an array of ids
     *
     * @param array $ids
     * @return SolrUpdateResponse
     */
    public function deleteByIds($ids)
    {
        return new SolrUpdateResponse();
    }

    /**
     * Delete by Query
     *
     * @param string $q
     * @return SolrUpdateResponse
     */
    public function deleteByQuery($q)
    {
        return new SolrUpdateResponse();
    }

    /**
     * Delete by Queries
     *
     * @param array $queries
     * @return SolrUpdateResponse
     */
    public function deleteByQueries(array $queries)
    {
        return new SolrUpdateResponse();
    }

    /**
     * Sends a name-value pair request to the Solr server
     *
     * @param SolrParams $q
     * @return SolrQueryResponse
     */
    public function query(SolrParams $q)
    {
        return new SolrQueryResponse();
    }

    /**
     * Sends a head request to the Solr Server
     *
     * This can be used to check if the server is still up
     *
     * @return SolrPingResponse
     */
    public function ping()
    {
        return new SolrPingResponse();
    }

    /**
     * Returns the threads status
     *
     * @return SolrGenericResponse
     */
    public function threads()
    {
        return new SolrGenericResponse();
    }

    /**
     * Sends an XML update request to the server.
     *
     * @param string $xml_update_request
     * @return SolrUpdateResponse
     */
    public function request($xml_update_request)
    {
        return new SolrUpdateResponse();
    }

    /**
     * Changes the value of the specified servlet
     *
     * $servlet_type must be one of the following
     *
     * - SolrClient::SEARCH_SERVLET_TYPE
     * - SolrClient::UPDATE_SERVLET_TYPE
     * - SolrClient::PING_SERVLET_TYPE
     * - SolrClient::THREADS_SERVLET_YPE
     * - SolrClient::TERMS_SERVLET_TYPE
     *
     * $new_value is the value for the new servlet location without the trailing slash
     *
     * @param int $servlet_type
     * @param string $new_value
     * @return bool
     */
    public function setServlet($servlet_type, $new_value)
    {
        return true;
    }
}
/* }}} */

/* phpdoc -f documentation.php  --title Solr  --parseprivate on --defaultpackagename Solr  --output  "HTML:frames:phphtmllib" -t solr_phpdoc */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

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

define('SOLR_MAJOR_VERSION', 0);
define('SOLR_MINOR_VERSION', 9);
define('SOLR_PATCH_VERSION', 7);

define('SOLR_EXTENSION_VERSION', '0.9.7');

/**
 * Returns the current version of the extension
 *
 * @return string
 */
function solr_get_version()
{
    return SOLR_EXTENSION_VERSION;
}

abstract  class SolrUtils
{
    public static function digestXmlResponse ( $xmlresponse , $parse_mode )
    {}

    public static function escapeQueryChars ( $str )
    {}

    public static function getSolrVersion()
    {}

    public static function queryPhrase ($str)
    {}
}


final class SolrDocumentField {

    /* Properties */
    public $name ;
    public $boost ;
    public $values ;

    /* Methods */
    public function __construct () {}
    public function __destruct () {}
}

final class SolrInputDocument   {

    const  SORT_DEFAULT = 1 ;
    const  SORT_ASC = 1 ;
    const  SORT_DESC = 2 ;
    const  SORT_FIELD_NAME = 1 ;
    const  SORT_FIELD_VALUE_COUNT = 2 ;
    const  SORT_FIELD_BOOST_VALUE = 4 ;

    public function addField ( $fieldName , $fieldValue , $fieldBoostValue  ) { }
    public function clear (  ) { }
    public function __clone (  ) { }
    public function __construct (  ) { }
    public function deleteField (  $fieldName ) { }
    public function __destruct (  ) { }
    public function fieldExists (  $fieldName ) { }
    public function getBoost (  ) { }
    public function getField (  $fieldName ) { }
    public function getFieldBoost (  $fieldName ) { }
    public function getFieldCount (  ) { }
    public function getFieldNames (  ) { }
    public function merge ( SolrInputDocument &$sourceDoc,  $overwrite ) { }
    public function reset (  ) { }
    public function setBoost ( $documentBoostValue ) { }
    public function setFieldBoost ( $fieldName , $fieldBoostValue ) { }
    public function sort ( int $sortOrderBy , $sortDirection  ) { }
    public function toArray (  ) { }

}

final class SolrDocument implements ArrayAccess, Iterator, Traversable, Serializable   {

    const SORT_DEFAULT = 1 ;
    const SORT_ASC = 1 ;
    const SORT_DESC = 2 ;
    const SORT_FIELD_NAME = 1 ;
    const SORT_FIELD_VALUE_COUNT = 2 ;
    const SORT_FIELD_BOOST_VALUE = 4 ;

    public function  addField (  $fieldName ,  $fieldValue ) { }
    public function  clear ( ) { }
    public function  __clone ( ) { }
    public function  __construct ( ) { }
    public function  current ( ) { }
    public function  deleteField (  $fieldName ) { }
    public function  __destruct ( ) { }
    public function  fieldExists (  $fieldName ) { }
    public function   __get (  $fieldName ) { }
    public function   getField (  $fieldName ) { }
    public function   getFieldCount ( ) { }
    public function   getFieldNames ( ) { }
    public function  getInputDocument ( ) { }
    public function  __isset (  $fieldName ) { }
    public function   key ( ) { }
    public function  merge ( SolrDocument &$sourceDoc , $overwrite  ) { }
    public function  next ( ) { }
    public function  offsetExists (  $fieldName ) { }
    public function   offsetGet (  $fieldName ) { }
    public function  offsetSet (  $fieldName ,  $fieldValue ) { }
    public function  offsetUnset (  $fieldName ) { }
    public function  reset ( ) { }
    public function  rewind ( ) { }
    public function   serialize ( ) { }
    public function  __set (  $fieldName ,  $fieldValue ) { }
    public function  sort ( $sortOrderBy , $sortDirection  ) { }
    public function   toArray ( ) { }
    public function  unserialize (  $serialized ) { }
    public function  __unset (  $fieldName ) { }
    public function  valid ( ) { }
}


final class SolrObject implements ArrayAccess   {

    /* Methods */
    public function __construct (  ) { }
    public function   __destruct (  ) { }
    public function   getPropertyNames (  ) { }
    public function   offsetExists (  $property_name ) { }
    public function   offsetGet (  $property_name ) { }
    public function   offsetSet (  $property_name ,  $property_value ) { }
    public function   offsetUnset (  $property_name ) { }
}


final  class SolrClient   {
    /* Constants */
    const SEARCH_SERVLET_TYPE = 1 ;
    const UPDATE_SERVLET_TYPE = 2 ;
    const THREADS_SERVLET_TYPE = 4 ;
    const PING_SERVLET_TYPE = 8 ;
    const TERMS_SERVLET_TYPE = 16 ;
    const DEFAULT_SEARCH_SERVLET = 'select' ;
    const DEFAULT_UPDATE_SERVLET = 'update' ;
    const DEFAULT_THREADS_SERVLET = 'admin/threads' ;
    const DEFAULT_PING_SERVLET = 'admin/ping' ;
    const DEFAULT_TERMS_SERVLET = 'terms' ;

    /* Methods */
    public function    addDocument ( SolrInputDocument &$doc  ,   $allowDups  ,   $commitWithin    ) { }
    public function    addDocuments ( array &$docs  ,   $allowDups  ,   $commitWithin    ) { }
    public function    commit (    $maxSegments  ,   $waitFlush  ,   $waitSearcher ) { }
    public function  __construct ( array $clientOptions ) { }
    public function    deleteById (   $id ) { }
    public function    deleteByIds ( array $ids ) { }
    public function    deleteByQueries ( array $queries ) { }
    public function    deleteByQuery (   $query ) { }
    public function    __destruct (   ) { }
    public function    getDebug (   ) { }
    public function  getOptions (   ) { }
    public function    optimize (    $maxSegments  ,   $waitFlush  ,   $waitSearcher     ) { }
    public function   ping (   ) { }
    public function   query ( SolrParams &$query ) { }
    public function    request (   $raw_request ) { }
    public function    rollback (   ) { }
    public function    setServlet (   $type ,   $value ) { }
    public function    threads (   ) { }
}


abstract  class SolrResponse   {
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
    public function   getDigestedResponse (  ) { }
    public function   getHttpStatus (  ) { }
    public function   getHttpStatusMessage (  ) { }
    public function   getRawRequest (  ) { }
    public function   getRawRequestHeaders (  ) { }
    public function   getRawResponse (  ) { }
    public function   getRawResponseHeaders (  ) { }
    public function   getRequestUrl (  ) { }
    public function   getResponse (  ) { }
    public function   setParseMode (  $parser_mode  ) { }
    public function   success (  ) { }
}

final  class SolrQueryResponse extends SolrResponse   {

}

final  class SolrUpdateResponse extends SolrResponse   {

}

final  class SolrPingResponse extends SolrResponse   {

}

final  class SolrGenericResponse extends SolrResponse   {

}

abstract class SolrParams implements Serializable
{
    /* Methods */
    final public function  add (   $name ,   $value ) { }
    public function  addParam (   $name ,   $value ) { }
    final public function   get (   $param_name ) { }
    final public function   getParam (   $param_name ) { }
    final public function   getParams (  ) { }
    final public function   getPreparedParams (  ) { }
    final public function    serialize (  ) { }
    final public function   set (   $name ,   $value ) { }
    public function   setParam ( $name ,   $value ) { }
    final public function    toString (  $url_encode  ) { }
    final public function   unserialize ( $serialized ) { }
}

 class SolrModifiableParams extends  SolrParams implements Serializable {

     public function __construct() {}

     public function __destruct() {}
 }

class  SolrQuery extends SolrModifiableParams implements Serializable {

    /* Constants */
    const ORDER_ASC = 0 ;
    const ORDER_DESC = 1 ;
    const FACET_SORT_INDEX = 0 ;
    const FACET_SORT_COUNT = 1 ;
    const TERMS_SORT_INDEX = 0 ;
    const TERMS_SORT_COUNT = 1 ;


    /* Methods */
    public function  addFacetDateField ( $dateField ) { }
    public function  addFacetDateOther ( $value , $field_override  ) { }
    public function  addFacetField ( $field ) { }
    public function  addFacetQuery ( $facetQuery ) { }
    public function  addField ( $field ) { }
    public function  addFilterQuery ( $fq ) { }
    public function  addHighlightField ( $field ) { }
    public function  addMltField ( $field ) { }
    public function  addMltQueryField ( $field , float $boost ) { }
    public function  addSortField ( $field , $order  ) { }
    public function  addStatsFacet ( $field ) { }
    public function  addStatsField ( $field ) { }
    public function  __construct ( $q  ) { }
    public function  __destruct (  ) { }
    public function  getFacet (  ) { }
    public function  getFacetDateEnd ( $field_override  ) { }
    public function  getFacetDateFields (  ) { }
    public function  getFacetDateGap ( $field_override  ) { }
    public function  getFacetDateHardEnd ( $field_override  ) { }
    public function  getFacetDateOther ( $field_override  ) { }
    public function  getFacetDateStart ( $field_override  ) { }
    public function  getFacetFields (  ) { }
    public function  getFacetLimit ( $field_override  ) { }
    public function  getFacetMethod ( $field_override  ) { }
    public function  getFacetMinCount ( $field_override  ) { }
    public function  getFacetMissing ( $field_override  ) { }
    public function  getFacetOffset ( $field_override  ) { }
    public function  getFacetPrefix ( $field_override  ) { }
    public function  getFacetQueries (  ) { }
    public function  getFacetSort ( $field_override  ) { }
    public function  getFields (  ) { }
    public function  getFilterQueries (  ) { }
    public function  getHighlight (  ) { }
    public function  getHighlightAlternateField ( $field_override  ) { }
    public function  getHighlightFields (  ) { }
    public function  getHighlightFormatter ( $field_override  ) { }
    public function  getHighlightFragmenter ( $field_override  ) { }
    public function  getHighlightFragsize ( $field_override  ) { }
    public function  getHighlightHighlightMultiTerm (  ) { }
    public function  getHighlightMaxAlternateFieldLength ( $field_override  ) { }
    public function  getHighlightMaxAnalyzedChars (  ) { }
    public function  getHighlightMergeContiguous ( $field_override  ) { }
    public function  getHighlightRegexMaxAnalyzedChars (  ) { }
    public function  getHighlightRegexPattern (  ) { }
    public function  getHighlightRegexSlop (  ) { }
    public function  getHighlightRequireFieldMatch (  ) { }
    public function  getHighlightSimplePost ( $field_override  ) { }
    public function  getHighlightSimplePre ( $field_override  ) { }
    public function  getHighlightSnippets ( $field_override  ) { }
    public function  getHighlightUsePhraseHighlighter (  ) { }
    public function  getMlt (  ) { }
    public function  getMltBoost (  ) { }
    public function  getMltCount (  ) { }
    public function  getMltFields (  ) { }
    public function  getMltMaxNumQueryTerms (  ) { }
    public function  getMltMaxNumTokens (  ) { }
    public function  getMltMaxWordLength (  ) { }
    public function  getMltMinDocFrequency (  ) { }
    public function  getMltMinTermFrequency (  ) { }
    public function  getMltMinWordLength (  ) { }
    public function  getMltQueryFields (  ) { }
    public function  getQuery (  ) { }
    public function  getRows (  ) { }
    public function  getSortFields (  ) { }
    public function  getStart (  ) { }
    public function  getStats (  ) { }
    public function  getStatsFacets (  ) { }
    public function  getStatsFields (  ) { }
    public function  getTerms (  ) { }
    public function  getTermsField (  ) { }
    public function  getTermsIncludeLowerBound (  ) { }
    public function  getTermsIncludeUpperBound (  ) { }
    public function  getTermsLimit (  ) { }
    public function  getTermsLowerBound (  ) { }
    public function  getTermsMaxCount (  ) { }
    public function  getTermsMinCount (  ) { }
    public function  getTermsPrefix (  ) { }
    public function  getTermsReturnRaw (  ) { }
    public function  getTermsSort (  ) { }
    public function  getTermsUpperBound (  ) { }
    public function  getTimeAllowed (  ) { }
    public function  removeFacetDateField ( $field ) { }
    public function  removeFacetDateOther ( $value , $field_override  ) { }
    public function  removeFacetField ( $field ) { }
    public function  removeFacetQuery ( $value ) { }
    public function  removeField ( $field ) { }
    public function  removeFilterQuery ( $fq ) { }
    public function  removeHighlightField ( $field ) { }
    public function  removeMltField ( $field ) { }
    public function  removeMltQueryField ( $queryField ) { }
    public function  removeSortField ( $field ) { }
    public function  removeStatsFacet ( $value ) { }
    public function  removeStatsField ( $field ) { }
    public function  setEchoHandler ( $flag ) { }
    public function  setEchoParams ( $type ) { }
    public function  setExplainOther ( $query ) { }
    public function  setFacet ( $flag ) { }
    public function  setFacetDateEnd ( $value , $field_override  ) { }
    public function  setFacetDateGap ( $value , $field_override  ) { }
    public function  setFacetDateHardEnd ( $value , $field_override  ) { }
    public function  setFacetDateStart ( $value , $field_override  ) { }
    public function  setFacetEnumCacheMinDefaultFrequency ( $frequency , $field_override  ) { }
    public function  setFacetLimit ( $limit , $field_override  ) { }
    public function  setFacetMethod ( $method , $field_override  ) { }
    public function  setFacetMinCount ( $mincount , $field_override  ) { }
    public function  setFacetMissing ( $flag , $field_override  ) { }
    public function  setFacetOffset ( $offset , $field_override  ) { }
    public function  setFacetPrefix ( $prefix , $field_override  ) { }
    public function  setFacetSort ( $facetSort , $field_override  ) { }
    public function  setHighlight ( $flag ) { }
    public function  setHighlightAlternateField ( $field , $field_override  ) { }
    public function  setHighlightFormatter ( $formatter , $field_override  ) { }
    public function  setHighlightFragmenter ( $fragmenter , $field_override  ) { }
    public function  setHighlightFragsize ( $size , $field_override  ) { }
    public function  setHighlightHighlightMultiTerm ( $flag ) { }
    public function  setHighlightMaxAlternateFieldLength ( $fieldLength , $field_override  ) { }
    public function  setHighlightMaxAnalyzedChars ( $value ) { }
    public function  setHighlightMergeContiguous ( $flag , $field_override  ) { }
    public function  setHighlightRegexMaxAnalyzedChars ( $maxAnalyzedChars ) { }
    public function  setHighlightRegexPattern ( $value ) { }
    public function  setHighlightRegexSlop ( float $factor ) { }
    public function  setHighlightRequireFieldMatch ( $flag ) { }
    public function  setHighlightSimplePost ( $simplePost , $field_override  ) { }
    public function  setHighlightSimplePre ( $simplePre , $field_override  ) { }
    public function  setHighlightSnippets ( $value , $field_override  ) { }
    public function  setHighlightUsePhraseHighlighter ( $flag ) { }
    public function  setMlt ( $flag ) { }
    public function  setMltBoost ( $flag ) { }
    public function  setMltCount ( $count ) { }
    public function  setMltMaxNumQueryTerms ( $value ) { }
    public function  setMltMaxNumTokens ( $value ) { }
    public function  setMltMaxWordLength ( $maxWordLength ) { }
    public function  setMltMinDocFrequency ( $minDocFrequency ) { }
    public function  setMltMinTermFrequency ( $minTermFrequency ) { }
    public function  setMltMinWordLength ( $minWordLength ) { }
    public function  setOmitHeader ( $flag ) { }
    public function  setQuery ( $query ) { }
    public function  setRows ( $rows ) { }
    public function  setShowDebugInfo ( $flag ) { }
    public function  setStart ( $start ) { }
    public function  setStats ( $flag ) { }
    public function  setTerms ( $flag ) { }
    public function  setTermsField ( $fieldname ) { }
    public function  setTermsIncludeLowerBound ( $flag ) { }
    public function  setTermsIncludeUpperBound ( $flag ) { }
    public function  setTermsLimit ( $limit ) { }
    public function  setTermsLowerBound ( $lowerBound ) { }
    public function  setTermsMaxCount ( $frequency ) { }
    public function  setTermsMinCount ( $frequency ) { }
    public function  setTermsPrefix ( $prefix ) { }
    public function  setTermsReturnRaw ( $flag ) { }
    public function  setTermsSort ( $sortType ) { }
    public function  setTermsUpperBound ( $upperBound ) { }
    public function  setTimeAllowed ( $timeAllowed ) { }

}

class SolrException extends Exception {

    /* Properties */
    protected  $sourceline ;
    protected  $sourcefile ;
    protected  $zif_name ;

    /* Methods */
    public function  getInternalInfo () { }
}

class SolrClientException extends SolrException {

    public function getInternalInfo () {}
}

class SolrIllegalArgumentException extends SolrException {

    public function getInternalInfo () {}
}

class SolrIllegalOperationException extends SolrException {

    public function getInternalInfo () {}
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

--TEST--
SolrDocument::fieldExists
--FILE--
<?php

require_once "bootstrap.inc";

$fixtureXml = file_get_contents(EXAMPLE_RESPONSE_XML_2);

$response = SolrUtils::digestXmlResponse($fixtureXml, SolrResponse::PARSE_SOLR_DOC);


$doc = new SolrDocument();

$doc->check = 1;

var_dump($doc->fieldExists('check'));
var_dump($doc->fieldExists('nonExistingField'));
?>
--EXPECT--
bool(true)
bool(false)
--TEST--
SolrDocument::clear - Remove all fields from the document
--FILE--
<?php

require_once "bootstrap.inc";

$fixtureXml = file_get_contents(EXAMPLE_RESPONSE_XML_2);

$response = SolrUtils::digestXmlResponse($fixtureXml, SolrResponse::PARSE_SOLR_DOC);


$doc = new SolrDocument();

$doc->check = 1;

var_dump($doc->getFieldCount());
$doc->clear();
var_dump($doc->getFieldCount());
?>
--EXPECTF--
int(1)
int(0)
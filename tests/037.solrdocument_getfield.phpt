--TEST--
SolrDocument::getField
--FILE--
<?php

require_once "bootstrap.inc";

$fixtureXml = file_get_contents(EXAMPLE_RESPONSE_XML_2);

$response = SolrUtils::digestXmlResponse($fixtureXml, SolrResponse::PARSE_SOLR_DOC);


$doc = new SolrDocument();

$doc->check = 1;

var_dump($doc->getField('check') instanceof SolrDocumentField);
?>
--EXPECT--
bool(true)
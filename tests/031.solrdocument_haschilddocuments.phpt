--TEST--
SolrDocument::hasChildDocuments() - Method test
--FILE--
<?php

require_once "bootstrap.inc";

$fixtureXml = file_get_contents(EXAMPLE_RESPONSE_XML_2);

$response = SolrUtils::digestXmlResponse($fixtureXml, SolrResponse::PARSE_SOLR_DOC);
var_dump($response->response->docs[0]->hasChildDocuments());
?>
--EXPECT--
bool(true)
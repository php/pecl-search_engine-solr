--TEST--
SolrObject - test property access
--FILE--
<?php

require_once "bootstrap.inc";

$xml_reponse = file_get_contents(EXAMPLE_RESPONSE_XML_1);

$solrObject = SolrUtils::digestXMLResponse($xml_reponse);

$header = $solrObject->responseHeader;

$system = $solrObject->system;

var_dump(isset($solrObject['system']));
var_dump(property_exists($solrObject, 'system'));
?>
--EXPECT--
bool(true)
bool(true)
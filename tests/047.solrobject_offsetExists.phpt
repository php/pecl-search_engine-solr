--TEST--
SolrObject::offsetExists
--FILE--
<?php

require_once "bootstrap.inc";

$constructedSolrObject = new SolrObject();
var_dump(isset($constructedSolrObject['responseHeader']));

$xml_reponse = file_get_contents(EXAMPLE_RESPONSE_XML_1);
$solrObject = SolrUtils::digestXMLResponse($xml_reponse);

var_dump(isset($solrObject['responseHeader']));
var_dump(isset($solrObject['nonexisting']));

?>
--EXPECT--
bool(false)
bool(true)
bool(false)
--TEST--
SolrObject - SolrObject::getPropertyNames()
--FILE--
<?php

$solrObject = new SolrObject();

var_dump($solrObject->getPropertyNames());

require_once "bootstrap.inc";

$xml_reponse = file_get_contents(EXAMPLE_RESPONSE_XML_1);

$solrObject = SolrUtils::digestXMLResponse($xml_reponse);

var_dump($solrObject->getPropertyNames());
?>
--EXPECT--
array(0) {
}
array(2) {
  [0]=>
  string(14) "responseHeader"
  [1]=>
  string(6) "system"
}

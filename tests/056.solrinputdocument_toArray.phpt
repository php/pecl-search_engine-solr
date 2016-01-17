--TEST--
SolrInputDocument::toArray - Array conversion
--FILE--
<?php

require_once "bootstrap.inc";

$doc = new SolrInputDocument();

$doc->addField('field_1', 4, 3.4);
$doc->addField('field_2', 1);

var_dump($doc->toArray());
?>
--EXPECT--

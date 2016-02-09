--TEST--
SolrInputDocument::fieldExists
--FILE--
<?php

require_once "bootstrap.inc";

$doc = new SolrInputDocument();
$doc->addField('id', 1123);

var_dump($doc->fieldExists('id'));
var_dump($doc->fieldExists('features'));
?>
--EXPECT--
bool(true)
bool(false)
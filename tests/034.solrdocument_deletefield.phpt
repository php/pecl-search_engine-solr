--TEST--
SolrDocument::deleteField
--FILE--
<?php

require_once "bootstrap.inc";

$doc = new SolrDocument();

$doc->check = 1;

var_dump($doc->getFieldCount());
$doc->deleteField('check');
var_dump($doc->getFieldCount());
?>
--EXPECTF--
int(1)
int(0)
--TEST--
SolrDocument - magic __isset/__unset/__get/__set
--FILE--
<?php

require_once "bootstrap.inc";

$doc = new SolrDocument();

$doc->check = 1;
$doc->deleteMe = 1;

var_dump(isset($doc->check));
var_dump(isset($doc->doesNotExist));


var_dump(isset($doc->deleteMe));
unset($doc->deleteMe);
var_dump(isset($doc->deleteMe));

$doc->addField('id', 1);

var_dump($doc->id instanceof SolrDocumentField);
?>
--EXPECTF--
bool(true)
bool(false)
bool(true)
bool(false)
bool(true)
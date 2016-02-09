--TEST--
SolrInputDocument::getFieldCount
--FILE--
<?php

require_once "bootstrap.inc";
$doc = new SolrInputDocument();

$doc->addField('id', 123);
$doc->addField('cat', 'Software');
$doc->addField('cat', 'Search Server');
$doc->addField('features', 'Software');

var_dump($doc->getFieldCount());

?>
--EXPECT--
int(3)
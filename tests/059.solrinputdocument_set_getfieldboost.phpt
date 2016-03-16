--TEST--
SolrInputDocument::getFieldBoost
--FILE--
<?php

require_once "bootstrap.inc";
$doc = new SolrInputDocument();

$doc->addField('id', 123);
$doc->addField('cat', 'Software');

$doc->setFieldBoost('cat', 2.1);
var_dump($doc->getFieldBoost('cat'));

?>
--EXPECT--
float(2.1)
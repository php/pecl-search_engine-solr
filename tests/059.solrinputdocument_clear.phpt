--TEST--
SolrInputDocument::clear - Clear document fields
--FILE--
<?php

require_once "bootstrap.inc";
$doc = new SolrInputDocument();


$doc->addField('id', 334455);
$doc->addField('cat', 'Software');
$doc->addField('cat', 'Lucene');
$doc->addField('z1', 'z1val');

$doc->clear();

var_dump($doc->toArray());
?>
--EXPECT--
array(3) {
  ["document_boost"]=>
  float(0)
  ["field_count"]=>
  int(0)
  ["fields"]=>
  array(0) {
  }
}

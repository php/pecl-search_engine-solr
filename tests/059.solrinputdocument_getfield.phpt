--TEST--
SolrInputDocument::getField
--FILE--
<?php

require_once "bootstrap.inc";
$doc = new SolrInputDocument();

$doc->addField('id', 123);
$doc->addField('cat', 'Software');

var_dump($doc->getField('id'));
var_dump($doc->getField('non_existing_field'));
?>
--EXPECT--
object(SolrDocumentField)#2 (3) {
  ["name"]=>
  string(2) "id"
  ["boost"]=>
  float(0)
  ["values"]=>
  array(1) {
    [0]=>
    string(3) "123"
  }
}
bool(false)

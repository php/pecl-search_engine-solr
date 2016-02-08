--TEST--
SolrInputDocument::getFieldNames - Test document fieldnames
--FILE--
<?php

require_once "bootstrap.inc";
$doc = new SolrInputDocument();

$doc->addField('id', 334455);
$doc->addField('manu_id_s', 'apache');
$doc->addField('cat', 'Software');

print_r($doc->getFieldNames());
?>
--EXPECT--
Array
(
    [0] => id
    [1] => manu_id_s
    [2] => cat
)

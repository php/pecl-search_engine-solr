--TEST--
SolrDocumentField::__construct
--FILE--
<?php

require_once "bootstrap.inc";
$field = new SolrDocumentField();

print_r($field);
?>
--EXPECT--
SolrDocumentField Object
(
    [name] =>  
    [boost] => 0
    [values] => 
)

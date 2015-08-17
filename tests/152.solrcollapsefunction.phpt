--TEST--
SolrCollapseFunction
--FILE--
<?php
$func = new SolrCollapseFunction('field');
$func->setMax('max');
$func->setMin('min');
$func->setSize(1000);
$func->setHint('hint');
$func->setNullPolicy('null-policy');

var_dump($func->getField());
var_dump($func->getMax());
var_dump($func->getMin());
var_dump($func->getSize());
var_dump($func->getHint());
var_dump($func->getNullPolicy());

var_dump((string)$func);
?>
--EXPECTF--
string(5) "field"
string(3) "max"
string(3) "min"
string(4) "1000"
string(4) "hint"
string(11) "null-policy"
string(82) "{!collapse field=field max=max min=min size=1000 hint=hint nullPolicy=null-policy}"

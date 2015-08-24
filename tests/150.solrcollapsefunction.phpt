--TEST--
SolrCollapseFunction
--FILE--
<?php

$func = new SolrCollapseFunction('field');

try {
	$tmp = clone $func;
} catch (SolrIllegalOperationException $e) {
	echo PHP_EOL . sprintf('Code %d: %s', $e->getCode(), $e->getMessage()).PHP_EOL;
}

$func->setMax('max');
$func->setMin('min');
$func->setSize(1000);
$func->setHint('hint');
$func->setNullPolicy(SolrCollapseFunction::NULLPOLICY_EXPAND);

var_dump($func->getField());
var_dump($func->getMax());
var_dump($func->getMin());
var_dump($func->getSize());
var_dump($func->getHint());
var_dump($func->getNullPolicy());

var_dump((string)$func);
$func->setMax('with space');
var_dump((string)$func);

try {
	// known issue, object corruption
	$tmp = serialize($func); 
} catch (SolrIllegalOperationException $e) {
	echo PHP_EOL . sprintf('Code %d: %s', $e->getCode(), $e->getMessage()).PHP_EOL;
}

?>
--EXPECTF--
Code 4001: Cloning of SolrCollapseFunction objects is currently not supported
string(5) "field"
string(3) "max"
string(3) "min"
string(4) "1000"
string(4) "hint"
string(6) "expand"
string(77) "{!collapse field=field max=max min=min size=1000 hint=hint nullPolicy=expand}"
string(86) "{!collapse field=field max='with space' min=min size=1000 hint=hint nullPolicy=expand}"

Code 1001: Serialization of SolrCollapseFunction objects is currently not supported

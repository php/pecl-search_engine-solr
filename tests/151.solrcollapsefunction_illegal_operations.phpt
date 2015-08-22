--TEST--
SolrCollapseFunction - Illegal Operations
--FILE--
<?php

$func = new SolrCollapseFunction('field');

try {
	$tmp = clone $func;
} catch (SolrIllegalOperationException $e) {
	echo PHP_EOL . sprintf('Code %d: %s', $e->getCode(), $e->getMessage()).PHP_EOL;
}

$func->setMax('max');

try {
	// known issue, object corruption
	$tmp = serialize($func); 
} catch (SolrIllegalOperationException $e) {
	echo PHP_EOL . sprintf('Code %d: %s', $e->getCode(), $e->getMessage()).PHP_EOL;
}

?>
--EXPECTF--
Code 4001: Cloning of SolrCollapseFunction objects is currently not supported

Code 1001: Serialization of SolrCollapseFunction objects is currently not supported


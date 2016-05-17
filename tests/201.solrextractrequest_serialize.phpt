--TEST--
SolrExtractRequest - serialize [exception]
--FILE--
<?php

$params = new SolrModifiableParams();

$request = SolrExtractRequest::createFromFile('test', $params);

try {
	var_dump(serialize($request));
} catch (SolrIllegalOperationException $e) {
	echo sprintf("Exception %d: %s", $e->getCode(), $e->getMessage()).PHP_EOL;
}
?>
--EXPECTF--
Exception 4001: SolrExtractRequest objects cannot be serialized or unserialized

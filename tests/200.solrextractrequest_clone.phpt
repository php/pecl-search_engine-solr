--TEST--
SolrExtractRequest - clone [exception]
--FILE--
<?php

$params = new SolrModifiableParams();

$request = SolrExtractRequest::createFromFile('test', $params);

try {
	$request2 = clone $request;
} catch (SolrIllegalOperationException $e) {
	echo sprintf("Exception %d: %s", $e->getCode(), $e->getMessage()).PHP_EOL;
}

?>
--EXPECTF--
Exception 4001: Cloning of SolrExtractRequest objects is currently not supported

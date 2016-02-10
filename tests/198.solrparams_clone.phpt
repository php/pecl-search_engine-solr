--TEST--
SolrParams - clone [exception]
--FILE--
<?php

$params = new SolrModifiableParams();

$params
	->setParam('q', 'lucene')
	->setParam('start', 0)
	->setParam('rows', 10)
	->addParam('fq', 'popularity:[10 TO *]')
	->addParam('fq', 'section:0')
;

try {
	$params2 = clone $params;
} catch (SolrIllegalOperationException $e) {
	echo sprintf("Exception %d: %s", $e->getCode(), $e->getMessage()).PHP_EOL;
}

?>
--EXPECTF--
Exception 4001: Cloning of SolrParams object instances is currently not supported

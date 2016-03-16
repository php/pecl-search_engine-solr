--TEST--
SolrParams::setParam()
--FILE--
<?php

$params = new SolrModifiableParams();

$params
	->setParam('q', 'lucene')
	->setParam('start', 0)
	->setParam('rows', 10)
;

echo $params;
?>
--EXPECTF--
q=lucene&start=0&rows=10

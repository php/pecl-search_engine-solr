--TEST--
SolrParams::toString()
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

echo $params->toString().PHP_EOL;
echo $params->toString(true);
?>
--EXPECTF--
q=lucene&start=0&rows=10&fq=popularity:[10 TO *]&fq=section:0
q=lucene&start=0&rows=10&fq=popularity%3A%5B10%20TO%20%2A%5D&fq=section%3A0
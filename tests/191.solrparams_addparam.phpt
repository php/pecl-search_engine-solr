--TEST--
SolrParams::addParam()
--FILE--
<?php

$params = new SolrModifiableParams();

$params
	->addParam('fq', 'popularity:[10 TO *]')
	->addParam('fq', 'section:0')
;

echo $params;
?>
--EXPECTF--
fq=popularity:[10 TO *]&fq=section:0

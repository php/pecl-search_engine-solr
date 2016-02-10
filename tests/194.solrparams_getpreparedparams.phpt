--TEST--
SolrParams::getPreparedParams()
--FILE--
<?php

$params = new SolrModifiableParams();

$params
	->set('q', 'lucene')
	->addParam('fq', 'popularity:[10 TO *]')
	->addParam('fq', 'section:0')
;

var_dump($params->getPreparedParams());
?>
--EXPECT--
array(2) {
  ["q"]=>
  string(8) "q=lucene"
  ["fq"]=>
  string(50) "fq=popularity%3A%5B10%20TO%20%2A%5D&fq=section%3A0"
}

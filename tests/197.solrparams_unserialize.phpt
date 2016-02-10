--TEST--
SolrParams::unserialize()
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

$serializedString = serialize($params);

$unserializedObject = unserialize($serializedString);
echo $unserializedObject;
?>
--EXPECTF--
q=lucene&start=0&rows=10&fq=popularity:[10 TO *]&fq=section:0

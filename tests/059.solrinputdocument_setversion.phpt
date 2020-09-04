--TEST--
SolrInputDocument::setVersion - Set document version
--SKIPIF--
<?php require_once 'skip.if.server_not_configured.inc'; ?>
--FILE--
<?php

require_once "bootstrap.inc";

$doc = new SolrInputDocument();

$doc->addField('id', 'IW-02');

$doc->setVersion(SolrInputDocument::VERSION_ASSERT_EXISTS);
var_dump($doc->getVersion());

$doc->setVersion(SolrInputDocument::VERSION_ASSERT_NOT_EXISTS);
var_dump($doc->getVersion());

$doc->setVersion(SolrInputDocument::VERSION_ASSERT_NONE);
var_dump($doc->getVersion());

$doc->setVersion(1498562624496861184);
var_dump($doc->getVersion());

try {
	$doc->setVersion('AAAA-3333');
} catch (SolrIllegalArgumentException $e) {
	echo $e->getMessage();
} catch (TypeError $e) {
	echo $e->getMessage();
}

?>
--EXPECTF--
int(1)
int(-1)
int(0)
int(1498562624496861184)
%slrInputDocument::setVersion()%s, string given

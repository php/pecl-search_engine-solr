--TEST--
SolrInputDocument::getChildDocumentsCount() - test
--FILE--
<?php

require_once "bootstrap.inc";

$doc = new SolrInputDocument();

$secondDoc = new SolrInputDocument();

$doc->addField('id', 1123);
$doc->addField('features', "PHP Client Side");
$doc->addField('features', "Fast development cycles");
$doc->cat   = 'Information Technology';

$secondDoc->addField('cat', 'Lucene Search');
$secondDoc->cat = 'Custom Search';

$doc->addChildDocument($secondDoc);

var_dump($doc->getChildDocumentsCount());
var_dump($secondDoc->getChildDocumentsCount());
?>
--EXPECT--
int(1)
int(0)
--TEST--
SolrInputDocument::addChildDocuments() - add child documents
--FILE--
<?php

require_once "bootstrap.inc";

$doc = new SolrInputDocument();

$doc2 = new SolrInputDocument();
$doc3 = new SolrInputDocument();

$doc->addField('id', 1123);
$doc->addField('features', "PHP Client Side");
$doc->addField('features', "Fast development cycles");
$doc->cat   = 'Information Technology';

$doc2->addField('cat', 'Lucene Search');
$doc2->cat = 'Custom Search';

$doc2->addField('cat', 'Lucene Search');
$doc2->cat = 'Custom Search';

$doc3->addField('cat', 'Lucene Search');
$doc3->cat = 'Custom Search';
$docs = array($doc2, $doc3);
$doc->addChildDocuments($docs);

var_dump($doc->getChildDocumentsCount());
?>
--EXPECT--
int(2)
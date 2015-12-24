--TEST--
SolrInputDocument::addChildDocument()/SolrInputDocument::addChildDocuments() - Expected SolrIllegalArgumentException
--FILE--
<?php

require_once "bootstrap.inc";

$doc = new SolrInputDocument();

$child1 = new SolrInputDocument();
$child2 = new SolrInputDocument();

$doc->addField('id', 1123);
$doc->addField('features', "PHP Client Side");
$doc->addField('features', "Fast development cycles");
$doc->cat   = 'Information Technology';
try {
	$doc->addChildDocument($child1);
} catch (SolrIllegalArgumentException $e) {
	echo $e->getMessage(). PHP_EOL;
}

$children = array($child1, $child2);
try {
	$doc->addChildDocuments($children);
} catch (SolrIllegalArgumentException $e) {
	echo $e->getMessage(). PHP_EOL;
}
?>
--EXPECT--
Child document has no fields
SolrInputDocument number 1 has no fields
--TEST--
SolrInputDocument::addChildDocument() - add child document
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

var_dump($doc->hasChildDocuments(), $secondDoc->hasChildDocuments());

$childs = $doc->getChildDocuments();
print_r($childs[0]->getField('cat'));

?>
--EXPECT--
bool(true)
bool(false)
SolrDocumentField Object
(
    [name] => cat
    [boost] => 0
    [values] => Array
        (
            [0] => Lucene Search
        )

)

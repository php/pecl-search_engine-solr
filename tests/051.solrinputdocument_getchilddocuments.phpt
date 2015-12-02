--TEST--
SolrInputDocument::getChildDocuments() - test
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

$childs = $doc->getChildDocuments();
print_r($childs[0]->getField('cat'));

?>
--EXPECT--
SolrDocumentField Object
(
    [name] => cat
    [boost] => 0
    [values] => Array
        (
            [0] => Lucene Search
        )

)
--TEST--
SolrInputDocument - clone
--FILE--
<?php

require_once "bootstrap.inc";
$doc = new SolrInputDocument();
$doc->setBoost(4);
$doc->addField('id', 334455);
$doc->addField('cat', 'Software', 4);
$doc->addField('cat', 'Lucene');

$doc2 = clone $doc;
$doc2->deleteField('id');
$doc2->addField('id', '88', 8);

print_r($doc->toArray());
print_r($doc2->toArray());
?>
--EXPECTF--
Array
(
    [document_boost] => 4
    [field_count] => 2
    [fields] => Array
        (
            [0] => SolrDocumentField Object
                (
                    [name] => id
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => 334455
                        )

                )

            [1] => SolrDocumentField Object
                (
                    [name] => cat
                    [boost] => 4
                    [values] => Array
                        (
                            [0] => Software
                            [1] => Lucene
                        )

                )

        )

)
Array
(
    [document_boost] => 4
    [field_count] => 2
    [fields] => Array
        (
            [0] => SolrDocumentField Object
                (
                    [name] => cat
                    [boost] => 4
                    [values] => Array
                        (
                            [0] => Software
                            [1] => Lucene
                        )

                )

            [1] => SolrDocumentField Object
                (
                    [name] => id
                    [boost] => 8
                    [values] => Array
                        (
                            [0] => 88
                        )

                )

        )

)

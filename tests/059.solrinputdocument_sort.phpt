--TEST--
SolrInputDocument::sort - Sort Document fields
--FILE--
<?php

require_once "bootstrap.inc";
$doc = new SolrInputDocument();


$doc->addField('z1', 'z1val');
$doc->addField('id', 334455);
$doc->addField('cat', 'Software');
$doc->addField('cat', 'Lucene');

$doc->sort(SolrDocument::SORT_ASC);
print_r($doc->toArray());
$doc->sort(SolrDocument::SORT_DESC);
print_r($doc->toArray());
?>
--EXPECT--
Array
(
    [document_boost] => 0
    [field_count] => 3
    [fields] => Array
        (
            [0] => SolrDocumentField Object
                (
                    [name] => cat
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => Software
                            [1] => Lucene
                        )

                )

            [1] => SolrDocumentField Object
                (
                    [name] => id
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => 334455
                        )

                )

            [2] => SolrDocumentField Object
                (
                    [name] => z1
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => z1val
                        )

                )

        )

)
Array
(
    [document_boost] => 0
    [field_count] => 3
    [fields] => Array
        (
            [0] => SolrDocumentField Object
                (
                    [name] => z1
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => z1val
                        )

                )

            [1] => SolrDocumentField Object
                (
                    [name] => id
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => 334455
                        )

                )

            [2] => SolrDocumentField Object
                (
                    [name] => cat
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => Software
                            [1] => Lucene
                        )

                )

        )

)
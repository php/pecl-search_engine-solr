--TEST--
SolrInputDocument::deleteField - Delete a field from SolrInputDocument
--FILE--
<?php

require_once "bootstrap.inc";
$doc = new SolrInputDocument();

$doc->addField('id', 334455);
$doc->addField('cat', 'Software');
$doc->addField('cat', 'Lucene');
$doc->addField('deleteme', 'Lucene');
$doc->deleteField('deleteme');

print_r($doc->toArray());
?>
--EXPECT--
Array
(
    [document_boost] => 0
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
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => Software
                            [1] => Lucene
                        )

                )

        )

)

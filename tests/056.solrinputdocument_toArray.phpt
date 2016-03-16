--TEST--
SolrInputDocument::toArray - Array conversion
--FILE--
<?php

require_once "bootstrap.inc";

$doc = new SolrInputDocument();

$doc->addField('field_1', 4, 3.4);
$doc->addField('field_2', 1);

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
                    [name] => field_1
                    [boost] => 3.4
                    [values] => Array
                        (
                            [0] => 4
                        )

                )

            [1] => SolrDocumentField Object
                (
                    [name] => field_2
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => 1
                        )

                )

        )

)

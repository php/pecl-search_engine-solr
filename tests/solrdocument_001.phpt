--TEST--
SolrDocument - checking dimension and magic property sets.
--FILE--
<?php

require_once "bootstrap.inc";

$doc = new SolrDocument();

$doc->addField('id', 1123);

$doc->features = "PHP Client Side";
$doc->features = "Fast development cycles";

$doc['cat'] = 'Software';
$doc['cat'] = 'Custom Search';
$doc->cat   = 'Information Technology';

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
                    [name] => id
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => 1123
                        )

                )

            [1] => SolrDocumentField Object
                (
                    [name] => features
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => PHP Client Side
                            [1] => Fast development cycles
                        )

                )

            [2] => SolrDocumentField Object
                (
                    [name] => cat
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => Software
                            [1] => Custom Search
                            [2] => Information Technology
                        )

                )

        )

)

--TEST--
SolrDocument::merge() - merging source document into current document
--FILE--
<?php

require_once "bootstrap.inc";

$doc = new SolrDocument();

$second_doc = new SolrDocument();

$doc->addField('id', 1123);

$doc->features = "PHP Client Side";
$doc->features = "Fast development cycles";

$doc['cat'] = 'Software';
$doc['cat'] = 'Custom Search';
$doc->cat   = 'Information Technology';

$second_doc->addField('cat', 'Lucene Search');

$second_doc->merge($doc, true);

print_r($second_doc->toArray());


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
                            [1] => Custom Search
                            [2] => Information Technology
                        )

                )

            [1] => SolrDocumentField Object
                (
                    [name] => id
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => 1123
                        )

                )

            [2] => SolrDocumentField Object
                (
                    [name] => features
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => PHP Client Side
                            [1] => Fast development cycles
                        )

                )

        )

)

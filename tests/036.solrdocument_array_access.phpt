--TEST--
SolrDocument - Array Access
--FILE--
<?php

require_once "bootstrap.inc";
$doc = new SolrDocument();

$doc->addField('id', 334455);
$doc->addField('manu_id_s', 'apache');
// set
$doc['cat'] = 'Software';

// get
var_dump($doc['cat']->values[0]);

// exists
var_dump(isset($doc['cat']));

// unset
unset($doc['cat']);
print_r($doc->toArray());
?>
--EXPECT--
string(8) "Software"
bool(true)
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
                    [name] => manu_id_s
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => apache
                        )

                )

        )

)

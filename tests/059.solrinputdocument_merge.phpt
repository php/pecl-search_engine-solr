--TEST--
SolrInputDocument::merge - Merge 2 docs
--FILE--
<?php

require_once "bootstrap.inc";

$doc = new SolrInputDocument();
$doc->addField('id', 1123);
$doc->addField('features', "PHP Client Side", 4);
$doc->addField('features', "Fast development cycles");
$doc->addField('cat', 'Information Technology');

separator('original document');
print_r($doc->toArray());

$doc2 = new SolrInputDocument();
$doc2->addField('cat', 'Lucene Search');
$doc2->merge($doc, true); // merge doc into doc2, overwrite cat

separator('merge overwrite (cat field merged ?)');
print_r($doc->getField('cat')->values);

var_dump($doc->fieldExists('features'));
print_r($doc2->toArray());

$doc3 = new SolrInputDocument();
$doc3->addField('manu_s_id', 'apache');
$doc3->addField('id', '124');

$doc3->merge($doc, false); // do not overwrite
separator('merge without overwrite');
print_r($doc3->getField('id')->values);
separator('END');
?>
--EXPECT--
============================== original document ===============================
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
                    [boost] => 4
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
                            [0] => Information Technology
                        )

                )

        )

)
===================== merge overwrite (cat field merged ?) =====================
Array
(
    [0] => Information Technology
)
bool(true)
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
                            [0] => Information Technology
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
                    [boost] => 4
                    [values] => Array
                        (
                            [0] => PHP Client Side
                            [1] => Fast development cycles
                        )

                )

        )

)
=========================== merge without overwrite ============================
Array
(
    [0] => 124
)
===================================== END ======================================
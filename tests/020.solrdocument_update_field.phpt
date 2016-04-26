--TEST--
SolrInputDocument::updateField
--FILE--
<?php

require_once 'bootstrap.inc';

$doc = new SolrInputDocument();

$doc->addField('id', 1123);

$doc->updateField('field1', SolrInputDocument::UPDATE_MODIFIER_ADD, 'val1');
$doc->updateField('field2_s', SolrInputDocument::UPDATE_MODIFIER_SET, 'val2');
$doc->updateField('field3_i', SolrInputDocument::UPDATE_MODIFIER_INC, 5);
$doc->updateField('field1', SolrInputDocument::UPDATE_MODIFIER_REMOVE, 'val0');
$doc->updateField('field1', SolrInputDocument::UPDATE_MODIFIER_REMOVEREGEX, '[\d]{2}/[\d]{2}/[\d]{4}');

try {
	$doc->updateField('arr2', 6, 'not gonna happen');
} catch (SolrIllegalArgumentException $e) {
	print_exception($e);
}

try {
	$doc->updateField('arr3', 0, 'not gonna happen');
} catch (SolrIllegalArgumentException $e) {
	print_exception($e);
}

print_r($doc->toArray());

?>
--EXPECT--
SolrIllegalArgumentException 4003: Invalid field value modifier.
SolrIllegalArgumentException 4003: Invalid field value modifier.
Array
(
    [document_boost] => 0
    [field_count] => 4
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
                    [name] => field1
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => val1
                            [1] => val0
                            [2] => [\d]{2}/[\d]{2}/[\d]{4}
                        )

                )

            [2] => SolrDocumentField Object
                (
                    [name] => field2_s
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => val2
                        )

                )

            [3] => SolrDocumentField Object
                (
                    [name] => field3_i
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => 5
                        )

                )

        )

)

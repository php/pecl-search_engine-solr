--TEST--
SolrDocument - checking Iterator interface implementation
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

foreach ($doc as $fieldname => $fieldvalues)
{
    print "$fieldname\n";

    print_r($fieldvalues);
}

?>
--EXPECT--
id
SolrDocumentField Object
(
    [name] => id
    [boost] => 0
    [values] => Array
        (
            [0] => 1123
        )

)
features
SolrDocumentField Object
(
    [name] => features
    [boost] => 0
    [values] => Array
        (
            [0] => PHP Client Side
            [1] => Fast development cycles
        )

)
cat
SolrDocumentField Object
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

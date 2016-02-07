--TEST--
SolrInputDocument::sort - Sort Document fields
--FILE--
<?php

require_once "bootstrap.inc";
$doc = new SolrInputDocument();


$doc->addField('z1', 'z1val', 1);
$doc->addField('z1', 'z1val2');
$doc->addField('z1', 'z1val3');

$doc->addField('id', 334455, 2);
$doc->addField('cat', 'Software', 3);
$doc->addField('cat', 'Lucene');

printf("---------------- %s --------------------\n", 'unsorted');
print_r($doc->getFieldNames());

printf("---------------- %s --------------------\n", 'field ASC');
$doc->sort(SolrDocument::SORT_FIELD_NAME, SolrDocument::SORT_ASC);
print_r($doc->getFieldNames());
printf("---------------- %s --------------------\n", 'field DESC');
$doc->sort(SolrDocument::SORT_FIELD_NAME, SolrDocument::SORT_DESC);
print_r($doc->getFieldNames());
printf("---------------- %s --------------------\n", 'boost ASC');
$doc->sort(SolrDocument::SORT_FIELD_BOOST_VALUE, SolrDocument::SORT_ASC);
print_r($doc->getFieldNames());
printf("---------------- %s --------------------\n", 'boost DESC');
$doc->sort(SolrDocument::SORT_FIELD_BOOST_VALUE, SolrDocument::SORT_DESC);
print_r($doc->getFieldNames());

printf("---------------- %s --------------------\n", 'value ASC');
$doc->sort(SolrDocument::SORT_FIELD_VALUE_COUNT, SolrDocument::SORT_ASC);
print_r($doc->getFieldNames());
printf("---------------- %s --------------------\n", 'value DESC');
$doc->sort(SolrDocument::SORT_FIELD_VALUE_COUNT, SolrDocument::SORT_DESC);
print_r($doc->getFieldNames());
?>
--EXPECT--
---------------- unsorted --------------------
Array
(
    [0] => z1
    [1] => id
    [2] => cat
)
---------------- field ASC --------------------
Array
(
    [0] => cat
    [1] => id
    [2] => z1
)
---------------- field DESC --------------------
Array
(
    [0] => z1
    [1] => id
    [2] => cat
)
---------------- boost ASC --------------------
Array
(
    [0] => z1
    [1] => id
    [2] => cat
)
---------------- boost DESC --------------------
Array
(
    [0] => cat
    [1] => id
    [2] => z1
)
---------------- value ASC --------------------
Array
(
    [0] => id
    [1] => cat
    [2] => z1
)
---------------- value DESC --------------------
Array
(
    [0] => z1
    [1] => cat
    [2] => id
)

--TEST--
SolrDocument::sort - Sort Document fields
--FILE--
<?php

require_once "bootstrap.inc";
$doc = new SolrDocument();


$doc->addField('z1', 'z1val');
$doc->addField('z1', 'z1val2');
$doc->addField('z1', 'z1val3');

$doc->addField('id', 334455);
$doc->addField('cat', 'Software');
$doc->addField('cat', 'Lucene');

separator('unsorted');
print_r($doc->getFieldNames());

separator('field ASC');
$doc->sort(SolrDocument::SORT_FIELD_NAME, SolrDocument::SORT_ASC);
print_r($doc->getFieldNames());
separator('field DESC');
$doc->sort(SolrDocument::SORT_FIELD_NAME, SolrDocument::SORT_DESC);
print_r($doc->getFieldNames());

separator('value ASC');
$doc->sort(SolrDocument::SORT_FIELD_VALUE_COUNT, SolrDocument::SORT_ASC);
print_r($doc->getFieldNames());
separator('value DESC');
$doc->sort(SolrDocument::SORT_FIELD_VALUE_COUNT, SolrDocument::SORT_DESC);
print_r($doc->getFieldNames());
?>
--EXPECT--
=================================== unsorted ===================================
Array
(
    [0] => z1
    [1] => id
    [2] => cat
)
================================== field ASC ===================================
Array
(
    [0] => cat
    [1] => id
    [2] => z1
)
================================== field DESC ==================================
Array
(
    [0] => z1
    [1] => id
    [2] => cat
)
================================== value ASC ===================================
Array
(
    [0] => id
    [1] => cat
    [2] => z1
)
================================== value DESC ==================================
Array
(
    [0] => z1
    [1] => cat
    [2] => id
)

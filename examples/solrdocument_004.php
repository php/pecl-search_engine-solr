<?php

include "bootstrap.php";

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
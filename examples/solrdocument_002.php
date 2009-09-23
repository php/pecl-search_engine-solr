<?php

include "bootstrap.php";

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
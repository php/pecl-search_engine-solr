--TEST--
SolrQuery - testing CommonQueryParameters
--FILE--
<?php

$query = new SolrQuery();

$query->setParam('a', 1);
$query->setParam('b', 2);
$query->setParam('c', 3);

$query->setStart(4)->setQuery('solr')->setTimeAllowed(500)->setRows(17);

$query->addField('israel')->addField('joshua')->addField('june');

$query->addSortField('cat', 0);

$query->addFilterQuery('solr')->addFilterQuery('solr1')->addFilterQuery('solr2');

echo $query;
echo "\n";

?>
--EXPECTF--
a=1&b=2&c=3&start=4&q=solr&timeAllowed=500&rows=17&fl=israel,joshua,june&sort=cat asc&fq=solr&fq=solr1&fq=solr2
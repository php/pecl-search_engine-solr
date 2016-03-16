--TEST--
SolrQuery - testing CommonQueryParameters
--FILE--
<?php

$query = new SolrQuery();
ob_start();
var_dump(
	$query->getQuery(),
	$query->getTimeAllowed(),
	$query->getStart(),
	$query->getRows(),
	$query->getFields(),
	$query->getFilterQueries(),
	$query->getSortFields()
);
$nullOutput = ob_get_clean();

$query->setParam('a', 1);
$query->setParam('b', 2);
$query->setParam('c', 3);

$query->setStart(4)->setQuery('solr')->setTimeAllowed(500)->setRows(17);

$query->addField('israel')->addField('joshua')->addField('june');

$query->addSortField('cat', SolrQuery::ORDER_ASC);

$query->addFilterQuery('solr')->addFilterQuery('solr1')->addFilterQuery('solr2');

$query
	->setShowDebugInfo(true)
	->setExplainOther('id:SOL*')
	->setOmitHeader(false)
	->setEchoHandler(true)
	->setEchoParams('all')
;

echo $query . PHP_EOL . PHP_EOL;

var_dump(
	$query->getQuery(),
	$query->getTimeAllowed(),
	$query->getStart(),
	$query->getRows(),
	$query->getFields(),
	$query->getFilterQueries(),
	$query->getSortFields()
);

echo $nullOutput;
?>
--EXPECT--
a=1&b=2&c=3&start=4&q=solr&timeAllowed=500&rows=17&fl=israel,joshua,june&sort=cat asc&fq=solr&fq=solr1&fq=solr2&debugQuery=true&explainOther=id:SOL*&omitHeader=false&echoHandler=true&echoParams=all

string(4) "solr"
int(500)
int(4)
int(17)
array(3) {
  [0]=>
  string(6) "israel"
  [1]=>
  string(6) "joshua"
  [2]=>
  string(4) "june"
}
array(3) {
  [0]=>
  string(4) "solr"
  [1]=>
  string(5) "solr1"
  [2]=>
  string(5) "solr2"
}
array(1) {
  [0]=>
  string(7) "cat asc"
}
NULL
NULL
NULL
NULL
NULL
NULL
NULL
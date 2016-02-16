--TEST--
SolrQuery - testing StatsComponent
--FILE--
<?php

$query = new SolrQuery();
ob_start();
var_dump(
	$query->getStats(),
	$query->getStatsFields(),
	$query->getStatsFacets()
);

$nullOutput = ob_get_clean();

$query->setStats(0);

$query
	->addStatsField('hello')
	->removeStatsField('hello')
	->addStatsField('june')
	->addStatsField('july')
;

$query
	->addStatsFacet('world')
	->removeStatsFacet('world')
	->addStatsFacet('pear')
	->addStatsFacet('pecl')
;

echo $query . PHP_EOL . PHP_EOL;

var_dump(
	$query->getStats(),
	$query->getStatsFields(),
	$query->getStatsFacets()
);
echo $nullOutput;
?>
--EXPECTF--
stats=false&stats.field=june&stats.field=july&stats.facet=pear&stats.facet=pecl

bool(false)
array(2) {
  [0]=>
  string(4) "june"
  [1]=>
  string(4) "july"
}
array(2) {
  [0]=>
  string(4) "pear"
  [1]=>
  string(4) "pecl"
}
NULL
NULL
NULL
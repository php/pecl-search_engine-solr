--TEST--
SolrQuery - Result Grouping (Group Parameters)
--FILE--
<?php

$query = new SolrQuery();

$query->setGroup(true);

$query->addGroupField('category')->addGroupField('featured');

$query->addGroupFunction('ceil(internalScore)');

$query->addGroupQuery('silk')->addGroupQuery('name:june');

$query->setGroupLimit(98);

$query->setGroupOffset(110);

$query->addGroupSortField('count', SolrQuery::ORDER_ASC);
$query->addGroupSortField('name', SolrQuery::ORDER_DESC);

$query->setGroupFormat('simple');

$query->setGroupMain(false);

$query->setGroupNGroups(false);

$query->setGroupTruncate(true);

$query->setGroupFacet(true);


$query->setGroupCachePercent(100);

echo PHP_EOL . "-- Query String --".PHP_EOL;
echo $query.PHP_EOL;

echo PHP_EOL . "-- Integer --".PHP_EOL;
var_dump($query->getGroupOffset(), $query->getGroupLimit(), $query->getGroupCachePercent(0));
echo PHP_EOL . "-- String --".PHP_EOL;
var_dump($query->getGroupFormat());
echo PHP_EOL . "-- Array --".PHP_EOL;
var_dump($query->getGroupFields());
var_dump($query->getGroupFunctions());
var_dump($query->getGroupQueries());
var_dump($query->getGroupSortFields());

echo PHP_EOL . "-- BOOL --".PHP_EOL;
var_dump($query->getGroup(), $query->getGroupMain(), $query->getGroupNGroups(), $query->getGroupTruncate(), $query->getGroupFacet());
echo PHP_EOL;

try {
	$query->setGroupCachePercent(-1);
} catch (SolrIllegalArgumentException $e) {
	echo sprintf("Exception Caught %d: %s", $e->getCode(), $e->getMessage()).PHP_EOL;
}
?>
--EXPECTF--
-- Query String --
group=true&group.field=category&group.field=featured&group.func=ceil(internalScore)&group.query=silk&group.query=name:june&group.limit=98&group.offset=110&group.sort=count asc,name desc&group.format=simple&group.main=false&group.ngroups=false&group.truncate=true&group.facet=true&group.cache.percent=100

-- Integer --
int(110)
int(98)
int(100)

-- String --
string(6) "simple"

-- Array --
array(2) {
  [0]=>
  string(8) "category"
  [1]=>
  string(8) "featured"
}
array(1) {
  [0]=>
  string(19) "ceil(internalScore)"
}
array(2) {
  [0]=>
  string(4) "silk"
  [1]=>
  string(9) "name:june"
}
array(2) {
  [0]=>
  string(9) "count asc"
  [1]=>
  string(9) "name desc"
}

-- BOOL --
bool(true)
bool(false)
bool(false)
bool(true)
bool(true)

Exception Caught 4000: Group cache percent must be between 0 and 100
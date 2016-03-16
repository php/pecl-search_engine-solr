--TEST--
SolrQuery - testing SimpleFacetParameters
--FILE--
<?php

$query = new SolrQuery();

$query->setFacet(0);

$query->addFacetField('israel')->addFacetField('israel2');

$query->addFacetQuery('silk')->addFacetQuery('name:june');

$query->setFacetPrefix('A')->setFacetPrefix('C', 'june');

$query->setFacetSort(1)->setFacetSort(0, 'june');

$query->setFacetLimit(98)->setFacetLimit(44, 'june');

$query->setFacetOffset(110)->setFacetOffset(12, 'june');

$query->setFacetMinCount(4)->setFacetMinCount(30, 'june');

$query->setFacetMissing(1)->setFacetMissing(0, 'june');

$query->setFacetMethod('enum')->setFacetMethod('fc', 'june');

$query->setFacetEnumCacheMinDefaultFrequency(25);

echo $query . PHP_EOL . PHP_EOL;

var_dump(
	$query->getFacet(),
	$query->getFacetFields(),
	$query->getFacetQueries(),
	$query->getFacetPrefix(),
	$query->getFacetPrefix('june'),
	$query->getFacetSort(),
	$query->getFacetSort('june'),
	$query->getFacetLimit(),
	$query->getFacetLimit('june'),
	$query->getFacetOffset(),
	$query->getFacetOffset('june'),
	$query->getFacetMinCount(),
	$query->getFacetMinCount('june'),
	$query->getFacetMissing(),
	$query->getFacetMissing('june'),
	$query->getFacetMethod(),
	$query->getFacetMethod('june')
);
?>
--EXPECTF--
facet=false&facet.field=israel&facet.field=israel2&facet.query=silk&facet.query=name:june&facet.prefix=A&f.june.facet.prefix=C&facet.sort=count&f.june.facet.sort=index&facet.limit=98&f.june.facet.limit=44&facet.offset=110&f.june.facet.offset=12&facet.mincount=4&f.june.facet.mincount=30&facet.missing=true&f.june.facet.missing=false&facet.method=enum&f.june.facet.method=fc&facet.enum.cache.minDf=25

bool(false)
array(2) {
  [0]=>
  string(6) "israel"
  [1]=>
  string(7) "israel2"
}
array(2) {
  [0]=>
  string(4) "silk"
  [1]=>
  string(9) "name:june"
}
string(1) "A"
string(1) "C"
int(1)
int(0)
int(98)
int(44)
int(110)
int(12)
int(4)
int(30)
bool(true)
bool(false)
string(4) "enum"
string(2) "fc"

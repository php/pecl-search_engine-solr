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

echo $query;
echo "\n";

?>
--EXPECTF--
facet=false&facet.field=israel&facet.field=israel2&facet.query=silk&facet.query=name:june&facet.prefix=A&f.june.facet.prefix=C&facet.sort=count&f.june.facet.sort=index&facet.limit=98&f.june.facet.limit=44&facet.offset=110&f.june.facet.offset=12&facet.mincount=4&f.june.facet.mincount=30&facet.missing=true&f.june.facet.missing=false&facet.method=enum&f.june.facet.method=fc
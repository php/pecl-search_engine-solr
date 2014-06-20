<?php

$query = new SolrQuery();

$query->setFacet(0);

$query->addFacetField('israel')->addFacetField('israel2');

$query->addFacetQuery('silk')->addFacetQuery('name:june');

$query->setFacetPrefix('A')->setFacetPrefix('C', 'june');

$query->setFacetSort(1)->setFacetSort(0, 'june');

//
$query->setFacetLimit(98)->setFacetLimit(44, 'june');

$query->setFacetOffset(110)->setFacetOffset(12, 'june');

$query->setFacetMinCount(4)->setFacetMinCount(30, 'june');

$query->setFacetMissing(1)->setFacetMissing(0, 'june');

$query->setFacetMethod('enum')->setFacetMethod('fc', 'june');

echo $query;
echo "\n";
<?php

$query = new SolrQuery();

$query->addFacetDateField('israel')->addFacetDateField('israel');

$query->setFacetDateStart('January')->setFacetDateStart('Feb', 'june');

$query->setFacetDateEnd('Jan')->setFacetDateEnd('Febr', 'israel');

$query->setFacetDateGap('AOL')->setFacetDateGap('YAHOO', 'june');

$query->setFacetDateHardEnd(1)->setFacetDateHardEnd(0,'june');

$query->addFacetDateOther('Google')->addFacetDateOther('Yahoos','june');

echo $query;
echo "\n";

--TEST--
SolrQuery - Testing Date facet parameters
--FILE--
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

?>
--EXPECTF--
facet.date=israel&facet.date=israel&facet.date.start=January&f.june.facet.date.start=Feb&facet.date.end=Jan&f.israel.facet.date.end=Febr&facet.date.gap=AOL&f.june.facet.date.gap=YAHOO&facet.date.hardend=true&f.june.facet.date.hardend=false&facet.date.other=Google&f.june.facet.date.other=Yahoos
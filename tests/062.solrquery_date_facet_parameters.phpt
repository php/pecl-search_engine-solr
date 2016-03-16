--TEST--
SolrQuery - Testing Date facet parameters
--FILE--
<?php

$query = new SolrQuery();

ob_start();
var_dump(
	$query->getFacetDateFields(),
	$query->getFacetDateStart(),
	$query->getFacetDateStart('june'),
	$query->getFacetDateEnd(),
	$query->getFacetDateEnd('israel'),
	$query->getFacetDateGap(),
	$query->getFacetDateGap('june'),
	$query->getFacetDateHardEnd(),
	$query->getFacetDateHardEnd('june'),
	$query->getFacetDateOther(),
	$query->getFacetDateOther('june')
);

$nullOutput = ob_get_clean();



$query->addFacetDateField('israel')
->addFacetDateField('israel')
->removeFacetDateField('israel')
;

$query->setFacetDateStart('January')->setFacetDateStart('Feb', 'june');

$query->setFacetDateEnd('Jan')->setFacetDateEnd('Febr', 'israel');

$query->setFacetDateGap('AOL')->setFacetDateGap('YAHOO', 'june');

$query->setFacetDateHardEnd(1)->setFacetDateHardEnd(0,'june');

$query->addFacetDateOther('Google')
->addFacetDateOther('Yahoos','june')
->addFacetDateOther('removeme')
->removeFacetDateOther('removeme');

echo $query. PHP_EOL . PHP_EOL;

var_dump(
	$query->getFacetDateFields(),
	$query->getFacetDateStart(),
	$query->getFacetDateStart('june'),
	$query->getFacetDateEnd(),
	$query->getFacetDateEnd('israel'),
	$query->getFacetDateGap(),
	$query->getFacetDateGap('june'),
	$query->getFacetDateHardEnd(),
	$query->getFacetDateHardEnd('june'),
	$query->getFacetDateOther(),
	$query->getFacetDateOther('june')
);

echo $nullOutput;
?>
--EXPECTF--
facet.date=israel&facet.date.start=January&f.june.facet.date.start=Feb&facet.date.end=Jan&f.israel.facet.date.end=Febr&facet.date.gap=AOL&f.june.facet.date.gap=YAHOO&facet.date.hardend=true&f.june.facet.date.hardend=false&f.june.facet.date.other=Yahoos

array(1) {
  [0]=>
  string(6) "israel"
}
string(7) "January"
string(3) "Feb"
string(3) "Jan"
string(4) "Febr"
string(3) "AOL"
string(5) "YAHOO"
bool(true)
bool(false)
NULL
array(1) {
  [0]=>
  string(6) "Yahoos"
}
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
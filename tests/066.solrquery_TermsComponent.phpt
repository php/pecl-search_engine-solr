--TEST--
SolrQuery - testing TermsComponent
--FILE--
<?php

$query = new SolrQuery();

$query->setTerms(true);

$query->setTermsField('israel');

$query->setTermsLowerBound('june');

$query->setTermsUpperBound('joshua');

$query->setTermsIncludeLowerBound(false);

$query->setTermsIncludeUpperBound(0);

$query->setTermsMinCount(50);

$query->setTermsMaxCount(200);

$query->setTermsPrefix('A');

$query->setTermsLimit(45);

$query->setTermsReturnRaw(false);

$query->setTermsSort(0);

echo $query;
echo "\n";

?>
--EXPECTF--
terms=true&terms.fl=israel&terms.lower=june&terms.upper=joshua&terms.lower.incl=false&terms.upper.incl=false&terms.mincount=50&terms.maxcount=200&terms.prefix=A&terms.limit=45&terms.raw=false&terms.sort=index
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

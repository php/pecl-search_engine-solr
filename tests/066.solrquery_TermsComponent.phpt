--TEST--
SolrQuery - testing TermsComponent
--FILE--
<?php

$query = new SolrQuery();

$dumpVars = function () use ($query) {
	var_dump(
		$query->getTerms(),
		$query->getTermsField(),
		$query->getTermsLowerBound(),
		$query->getTermsUpperBound(),
		$query->getTermsIncludeLowerBound(),
		$query->getTermsIncludeUpperBound(),
		$query->getTermsMinCount(),
		$query->getTermsMaxCount(),
		$query->getTermsPrefix(),
		$query->getTermsLimit(),
		$query->getTermsReturnRaw(),
		$query->getTermsSort()
	);
};

ob_start();
$dumpVars();
$nullOutput = ob_get_clean();

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

$query->setTermsSort(SolrQuery::TERMS_SORT_INDEX);

echo $query . PHP_EOL . PHP_EOL;

$dumpVars();


$query->setTermsSort(SolrQuery::TERMS_SORT_COUNT);
echo PHP_EOL . $query . PHP_EOL . PHP_EOL;

var_dump(
	$query->getTermsSort()
);

echo $nullOutput;
?>
--EXPECTF--
terms=true&terms.fl=israel&terms.lower=june&terms.upper=joshua&terms.lower.incl=false&terms.upper.incl=false&terms.mincount=50&terms.maxcount=200&terms.prefix=A&terms.limit=45&terms.raw=false&terms.sort=index

bool(true)
string(6) "israel"
string(4) "june"
string(6) "joshua"
bool(false)
bool(false)
int(50)
int(200)
string(1) "A"
int(45)
bool(false)
int(0)

terms=true&terms.fl=israel&terms.lower=june&terms.upper=joshua&terms.lower.incl=false&terms.upper.incl=false&terms.mincount=50&terms.maxcount=200&terms.prefix=A&terms.limit=45&terms.raw=false&terms.sort=count

int(1)
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
NULL

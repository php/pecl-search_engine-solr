--TEST--
SolrQuery - testing MoreLikeThis component
--FILE--
<?php

$query = new SolrQuery();

ob_start();

var_dump(
	$query->getMlt(),
	$query->getMltCount(),
	$query->getMltFields(),
	$query->getMltQueryFields(),
	$query->getMltMinTermFrequency(),
	$query->getMltMinDocFrequency(),
	$query->getMltMinWordLength(),
	$query->getMltMaxWordLength(),
	$query->getMltMaxNumTokens(),
	$query->getMltMaxNumQueryTerms(),
	$query->getMltBoost()
);
$nullOutput = ob_get_clean();

$query->setMlt(1);

$query->setMltCount(55)->setMltCount(90);

$query->addMltField('june')->addMltField('joshua')->addMltField('mom')->removeMltField('joshua');

$query->addMltQueryField('june', 0.0)->addMltQueryField('israel', 9.558)
	->addMltQueryField('removeme', 0.0)
	->removeMltQueryField('removeme')
;

$query->setMltMinTermFrequency(9);

$query->setMltMinDocFrequency(5);

$query->setMltMinWordLength(8);

$query->setMltMaxWordLength(99);

$query->setMltMaxNumTokens(6);

$query->setMltMaxNumQueryTerms(2);

$query->setMltBoost(true);

echo $query . PHP_EOL . PHP_EOL;

var_dump(
	$query->getMlt(),
	$query->getMltCount(),
	$query->getMltFields(),
	$query->getMltQueryFields(),
	$query->getMltMinTermFrequency(),
	$query->getMltMinDocFrequency(),
	$query->getMltMinWordLength(),
	$query->getMltMaxWordLength(),
	$query->getMltMaxNumTokens(),
	$query->getMltMaxNumQueryTerms(),
	$query->getMltBoost()
);

echo $nullOutput;

?>
--EXPECTF--
mlt=true&mlt.count=90&mlt.fl=june,mom&mlt.qf=june^0 israel^9.558&mlt.mintf=9&mlt.mindf=5&mlt.minwl=8&mlt.maxwl=99&mlt.maxntp=6&mlt.maxqt=2&mlt.boost=true

bool(true)
int(90)
array(2) {
  [0]=>
  string(4) "june"
  [1]=>
  string(3) "mom"
}
array(2) {
  [0]=>
  string(6) "june^0"
  [1]=>
  string(12) "israel^9.558"
}
int(9)
int(5)
int(8)
int(99)
int(6)
int(2)
bool(true)
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
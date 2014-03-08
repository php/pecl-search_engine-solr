--TEST--
SolrQuery - testing MoreLikeThis component
--FILE--
<?php

$query = new SolrQuery();

$query->setMlt(1);

$query->setMltCount(55)->setMltCount(90);

$query->addMltField('june')->addMltField('joshua')->addMltField('mom')->removeMltField('joshua');

$query->addMltQueryField('june', 0.0)->addMltQueryField('israel', 9.558);

$query->setMltMinTermFrequency(9);

$query->setMltMinDocFrequency(5);

$query->setMltMinWordLength(8);

$query->setMltMaxWordLength(99);

$query->setMltMaxNumTokens(6);

$query->setMltMaxNumQueryTerms(2);

$query->setMltBoost(true);

echo $query;
echo "\n";

?>
--EXPECTF--
mlt=true&mlt.count=90&mlt.fl=june,mom&mlt.qf=june^0 israel^9.558&mlt.mintf=9&mlt.mindf=5&mlt.minwl=8&mlt.maxwl=99&mlt.maxntp=6&mlt.maxqt=2&mlt.boost=true
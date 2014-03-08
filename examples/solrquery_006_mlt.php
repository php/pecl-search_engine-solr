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


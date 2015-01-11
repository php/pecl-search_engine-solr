--TEST--
SolrDisMaxQuery - BigramFields and slop (addBigramPhraseField, removeBigramPhraseField, setBigramPhraseFields)
--FILE--
<?php

$dismaxQuery = new SolrDisMaxQuery('lucene');
$dismaxQuery
->addBigramPhraseField('cat', 2, 5.1)
->addBigramPhraseField('feature', 4.5)
;
echo $dismaxQuery.PHP_EOL;
// reverse
$dismaxQuery
->removeBigramPhraseField('cat');
echo $dismaxQuery.PHP_EOL;

$dismaxQuery->setBigramPhraseFields("cat~5.1^2 feature^4.5");
echo $dismaxQuery.PHP_EOL;

$dismaxQuery->setBigramPhraseSlop(2);
echo $dismaxQuery.PHP_EOL;
?>
--EXPECTF--
q=lucene&defType=%s&pf2=cat~5.1^2 feature^4.5
q=lucene&defType=%s&pf2=feature^4.5

Notice: SolrDisMaxQuery::setBigramPhraseFields(): Parameter pf2 value(s) was overwritten by this call in %s on line %d
q=lucene&defType=%s&pf2=cat~5.1^2 feature^4.5
q=lucene&defType=%s&pf2=cat~5.1^2 feature^4.5&ps2=2

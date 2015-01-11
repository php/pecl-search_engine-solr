--TEST--
SolrDisMaxQuery - TrigramFields and slop (addTrigramPhraseField, removeTrigramPhraseField, setTrigramPhraseFields)
--FILE--
<?php

$dismaxQuery = new SolrDisMaxQuery('lucene');
$dismaxQuery
->addTrigramPhraseField('cat', 2, 5.1)
->addTrigramPhraseField('feature', 4.5)
;
echo $dismaxQuery.PHP_EOL;
// reverse
$dismaxQuery
->removeTrigramPhraseField('cat');
echo $dismaxQuery.PHP_EOL;

$dismaxQuery->setTrigramPhraseFields('cat~5.1^2 feature^4.5');
echo $dismaxQuery.PHP_EOL;

$dismaxQuery->setTrigramPhraseSlop(2);
echo $dismaxQuery.PHP_EOL;
?>
--EXPECTF--
q=lucene&defType=%s&pf3=cat~5.1^2 feature^4.5
q=lucene&defType=%s&pf3=feature^4.5

Notice: SolrDisMaxQuery::setTrigramPhraseFields(): Parameter pf3 value(s) was overwritten by this call in %s on line %d
q=lucene&defType=%s&pf3=cat~5.1^2 feature^4.5
q=lucene&defType=%s&pf3=cat~5.1^2 feature^4.5&ps3=2

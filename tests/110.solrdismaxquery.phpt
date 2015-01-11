--TEST--
SolrDisMaxQuery - Methods
--FILE--
<?php

$dismaxQuery = new SolrDisMaxQuery("lucene");
$dismaxQuery
->addPhraseField('source', 55)
->addPhraseField('cat', 3, 1)
->addPhraseField('third', 4, 1)
->removePhraseField('third')
->addPhraseField('fourth', 0.5)
->addPhraseField('fifth',5.2, 7.8)
->setQueryAlt('*:*')
->addQueryField("price")
->addQueryField("location", 4)
->setPhraseSlop(2)
->setQueryPhraseSlop(3)
->setTieBreaker(0.5)
->setMinimumMatch(2)
;
// reverse
echo $dismaxQuery.PHP_EOL;
$dismaxQuery = new SolrDisMaxQuery("lucene");
$dismaxQuery
	->addQueryField("location", 4)
	->addQueryField("price")
	->addQueryField("sku")
	->addQueryField("title",3.4)
	->addPhraseField('cat', 3, 1)
	->addPhraseField('third', 4, 1)
	->addPhraseField('source', 55)
;
echo $dismaxQuery.PHP_EOL;

$dismaxQuery->setPhraseFields('source^55 cat~1^3');
echo $dismaxQuery.PHP_EOL;
$dismaxQuery = new SolrDisMaxQuery('lucene');

$dismaxQuery->addPhraseField('first', 3, 1)
->addPhraseField('second', 4, 1)
->addPhraseField('cat', 55);
echo $dismaxQuery. PHP_EOL;

echo $dismaxQuery->removePhraseField('second').PHP_EOL;

$dismaxQuery = new SolrDisMaxQuery('lucene');
$dismaxQuery->addQueryField('first', 3)
->addQueryField('second', 0.2)
->addQueryField('cat');
echo $dismaxQuery. PHP_EOL;
echo $dismaxQuery->removeQueryField('second').PHP_EOL;

$dismaxQuery = new SolrDisMaxQuery('lucene');

$dismaxQuery->setPhraseSlop(4);
echo $dismaxQuery.PHP_EOL;

?>
--EXPECTF--
q=lucene&defType=%s&pf=source^55 cat~1^3 fourth^0.5 fifth~7.8^5.2&q.alt=*:*&qf=price location^4&ps=2&qs=3&tie=0.5&mm=2
q=lucene&defType=%s&qf=location^4 price sku title^3.4&pf=cat~1^3 third~1^4 source^55

Notice: SolrDisMaxQuery::setPhraseFields(): Parameter pf value(s) was overwritten by this call in %s on line %d
q=lucene&defType=%s&qf=location^4 price sku title^3.4&pf=source^55 cat~1^3
q=lucene&defType=%s&pf=first~1^3 second~1^4 cat^55
q=lucene&defType=%s&pf=first~1^3 cat^55
q=lucene&defType=%s&qf=first^3 second^0.2 cat
q=lucene&defType=%s&qf=first^3 cat
q=lucene&defType=%s&ps=4
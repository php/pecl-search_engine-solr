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
echo $dismaxQuery;
?>
--EXPECTF--
q=lucene&defType=dismax&pf=source^55 cat~1^3 fourth^0.5 fifth~7.8^5.2&q.alt=*:*&qf=price location^4&ps=2&qs=3&tie=0.5&mm=2
q=lucene&defType=dismax&qf=location^4 price sku title^3.4&pf=cat~1^3 third~1^4 source^55
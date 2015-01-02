--TEST--
SolrDisMaxQuery - Boost Query
--FILE--
<?php

$dismaxQuery = new SolrDisMaxQuery("lucene");
$dismaxQuery
	->addBoostQuery('cat', 'electronics', 5.1)
	->addBoostQuery('cat', 'hard drive')
;
// reverse
echo $dismaxQuery.PHP_EOL;
$dismaxQuery
->removeBoostQuery('cat');
echo $dismaxQuery.PHP_EOL;

$dismaxQuery->setBoostQuery('cat:electronics manu:local^2');
echo $dismaxQuery.PHP_EOL;
?>
--EXPECTF--
q=lucene&defType=edismax&bq=cat:electronics^5.1 cat:hard drive
q=lucene&defType=edismax&bq=cat:hard drive

Notice: SolrDisMaxQuery::setBoostQuery(): Parameter bq value(s) was overwritten by this call in %s on line %d
q=lucene&defType=edismax&bq=cat:electronics manu:local^2

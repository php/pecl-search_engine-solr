--TEST--
Solr Bug #68181 - Conflict occurs when using SolrDisMax::addBoostQuery and setBoostQuery
--FILE--
<?php
$dismaxQuery = new SolrDisMaxQuery("lucene");
$dismaxQuery->setBoostQuery("failing:val^3")
->addBoostQuery('category','software',2)
->setBoostQuery("end:result^4");

echo $dismaxQuery.PHP_EOL;
?>
--EXPECTF--
Notice: SolrDisMaxQuery::addBoostQuery(): Parameter bq value(s) was overwritten by this call in %s on line %d

Notice: SolrDisMaxQuery::setBoostQuery(): Parameter bq value(s) was overwritten by this call in %s on line %d
q=lucene&defType=%s&bq=end:result^4
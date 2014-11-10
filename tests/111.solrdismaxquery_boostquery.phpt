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
?>
--EXPECTF--
q=lucene&defType=%s&bq=cat:electronics^5.1 cat:hard drive
q=lucene&defType=%s&bq=cat:hard drive
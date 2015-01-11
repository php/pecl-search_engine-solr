--TEST--
SolrDisMaxQuery - setBoostFunction
--FILE--
<?php

$dismaxQuery = new SolrDisMaxQuery('lucene');

$boostRecentDocsFunction = "recip(ms(NOW,mydatefield),3.16e-11,1,1)";
$dismaxQuery->setBoostFunction($boostRecentDocsFunction);

echo $dismaxQuery.PHP_EOL;

?>
--EXPECTF--
q=lucene&defType=%s&bf=recip(ms(NOW,mydatefield),3.16e-11,1,1)
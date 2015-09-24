--TEST--
Solr Bug #68179 - Solr Params (Argument list) separator disappears
--FILE--
<?php
$dismaxQuery = new SolrDisMaxQuery('score');
$dismaxQuery->addSortField('price', SolrQuery::ORDER_ASC);
$dismaxQuery->addSortField('score', SolrQuery::ORDER_DESC);
echo $dismaxQuery.PHP_EOL;
?>
--EXPECTF--
q=score&defType=%s&sort=price asc,score desc
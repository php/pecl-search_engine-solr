--TEST--
SolrQuery::collapse - Collapse Using a SolrCollapseFunction
--FILE--
<?php

$query = new SolrQuery('lucene');
$collapseFunction = new SolrCollapseFunction('ISBN');
$collapseFunction->setMax(5);

$query->collapse($collapseFunction);

echo $query;
?>
--EXPECTF--
q=lucene&fq={!collapse field=ISBN max=5}

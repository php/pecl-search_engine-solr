--TEST--
SolrQuery::collapse - Collapse Using a SolrCollapseFunction
--FILE--
<?php

$query = new SolrQuery('lucene');
$collapseFunction = new SolrCollapseFunction('ISBN');

$query->collapse($collapseFunction);

echo $query;
?>
--EXPECTF--
q=lucene&fq={!collapse field=ISBN}

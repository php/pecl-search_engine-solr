--TEST--
SolrQuery::collapse - Collapse Using a SolrCollapseFunction
--FILE--
<?php

$query = new SolrQuery('lucene');
$collapseFunction = new SolrCollapseFunction('ISBN');

$query->collapse($collapseFunction);

echo $query;

$collapseFunction = new SolrCollapseFunction();
try {
	$query->collapse($collapseFunction);
} catch (SolrMissingMandatoryParameterException $e) {
	echo PHP_EOL.sprintf('Exception %d: %s', $e->getCode(), $e->getMessage());
}
?>
--EXPECTF--
q=lucene&fq={!collapse field=ISBN}
Exception 4100: Mandatory parameter Missing: field

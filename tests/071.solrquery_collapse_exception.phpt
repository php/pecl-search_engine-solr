--TEST--
SolrQuery::collapse - throws SolrMissingMandatoryParameterException
--FILE--
<?php

$query = new SolrQuery('*:*');
$collapseFunction = new SolrCollapseFunction();
try {
    $query->collapse($collapseFunction);
} catch (SolrMissingMandatoryParameterException $e) {
    echo PHP_EOL.sprintf('Exception %d: %s', $e->getCode(), $e->getMessage());
}
?>
--EXPECTF--
Exception 4100: Mandatory parameter Missing: field

--TEST--
SolrQuery - Strict type parameters
--FILE--
<?php declare(strict_types=1);

$query = new SolrQuery('lucene');

$query->setStart(1);
$query->setRows(2);
$query->setTimeAllowed(300);
$query->setGroupOffset(1);
$query->setExpandRows(1);
--EXPECTF--

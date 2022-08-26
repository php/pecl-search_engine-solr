--TEST--
SolrQuery - Strict type parameters without BC break
--FILE--
<?php declare(strict_types=1);

$query = new SolrQuery('lucene');

$query->setStart(1);
$query->setRows(2);
$query->setTimeAllowed(300);
$query->setGroupOffset(1);
$query->setExpandRows(1);

echo $query . "\n";

// Now with strings
$query = new SolrQuery('lucene');
$query->setStart('1anystring'); // we don't do any checking
$query->setRows('2');
$query->setTimeAllowed('300');
$query->setGroupOffset('1');
$query->setExpandRows('1');

echo $query;
--EXPECT--
q=lucene&start=1&rows=2&timeAllowed=300&group.offset=1&expand.rows=1
q=lucene&start=1anystring&rows=2&timeAllowed=300&group.offset=1&expand.rows=1

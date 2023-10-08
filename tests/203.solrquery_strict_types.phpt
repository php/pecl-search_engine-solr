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

echo $query . "\n";

try { $query->setStart(true); } catch (SolrIllegalArgumentException $e) { echo $e->getMessage() . "\n"; }

$collapse = new SolrCollapseFunction();
$collapse->setSize(1);

echo $collapse . "\n";

$d = new SolrDisMaxQuery('lucene');
$d->setPhraseSlop(2);
$d->setQueryPhraseSlop(3);
$d->setBigramPhraseSlop(4);
$d->setTrigramPhraseSlop(5);

echo $d . "\n";

--EXPECT--
q=lucene&start=1&rows=2&timeAllowed=300&group.offset=1&expand.rows=1
q=lucene&start=1anystring&rows=2&timeAllowed=300&group.offset=1&expand.rows=1
Argument 1 must be an int
{!collapse size=1}
q=lucene&defType=edismax&ps=2&qs=3&ps2=4&ps3=5


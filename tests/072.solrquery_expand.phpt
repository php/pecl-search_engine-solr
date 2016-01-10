--TEST--
SolrQuery - Expand Component
--FILE--
<?php

$query = new SolrQuery('lucene');

$query->setExpand(true);
$query->setExpandRows(50);
$query->setExpandQuery('text:product');
$query->addExpandFilterQuery('manu:apple')->addExpandFilterQuery('inStock:true');
$query->addExpandSortField('score', SolrQuery::ORDER_DESC)->addExpandSortField('title', SolrQuery::ORDER_ASC);

// removal test
$query->addExpandFilterQuery('extra')->removeExpandFilterQuery('extra');
$query->addExpandSortField('extra', SolrQuery::ORDER_ASC)->removeExpandSortField('extra');

echo $query.PHP_EOL;
var_dump($query->getExpand()).PHP_EOL;
var_dump($query->getExpandRows()).PHP_EOL;
var_dump($query->getExpandQuery()).PHP_EOL;
var_dump($query->getExpandFilterQueries()).PHP_EOL;
var_dump($query->getExpandSortFields()).PHP_EOL;
?>
--EXPECTF--
q=lucene&expand=true&expand.rows=50&expand.q=text:product&expand.fq=manu:apple&expand.fq=inStock:true&expand.sort=score desc,title asc
bool(true)
int(50)
string(12) "text:product"
array(2) {
  [0]=>
  string(10) "manu:apple"
  [1]=>
  string(12) "inStock:true"
}
array(2) {
  [0]=>
  string(5) "score"
  [1]=>
  string(5) "title"
}

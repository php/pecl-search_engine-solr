--TEST--
SolrQuery::_construct - Throws exception on illegal Argument
--FILE--
<?php

try {
	$query = new SolrQuery(new StdClass());
} catch (SolrIllegalArgumentException $e) {
	echo $e->getMessage();
}
?>
--EXPECT--
SolrQuery::__construct() expects parameter 1 to be string, object given
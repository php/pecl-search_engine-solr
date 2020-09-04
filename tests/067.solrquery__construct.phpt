--TEST--
SolrQuery::_construct - Throws exception on illegal Argument
--FILE--
<?php

try {
	$query = new SolrQuery(new StdClass());
} catch (SolrIllegalArgumentException $e) {
	echo $e->getMessage();
} catch (TypeError $e) {
	echo $e->getMessage();
}
?>
--EXPECTF--
SolrQuery::__construct()%s string, %s given

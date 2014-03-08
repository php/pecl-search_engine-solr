--TEST--
SolrQuery::_construct - Throws exception on illegal Argument
--FILE--
<?php

$query = new SolrQuery(new StdClass());

?>
--EXPECTF--
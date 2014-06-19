--TEST--
SolrQuery::_construct - Throws exception on illegal Argument
--FILE--
<?php

$query = new SolrQuery(new StdClass());

?>
--EXPECTF--
Fatal error: Uncaught exception 'SolrIllegalArgumentException' with message 'SolrQuery::__construct() expects parameter 1 to be string, object given' in %s:%d
Stack trace:
#0 %s(%d): SolrQuery->__construct(Object(stdClass))
#1 {main}
  thrown in %s on line %d
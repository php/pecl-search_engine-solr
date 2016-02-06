--TEST--
SolrInputDocument::getBoost - Test document fieldnames
--FILE--
<?php

require_once "bootstrap.inc";
$doc = new SolrInputDocument();
$doc->setBoost(4);
var_dump($doc->getBoost());
?>
--EXPECT--
float(4)
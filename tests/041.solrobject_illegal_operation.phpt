--TEST--
SolrObject - checking illegal operation of modifying object
--FILE--
<?php

$solrObject = new SolrObject();

try
{
   @$solrObject->email = "iekpo@php.net";

} catch (Exception $e) {

    var_dump($e->getCode());

    var_dump($e->getMessage());
}

?>
--EXPECT--
int(1006)
string(76) "SolrObject instances are read-only. Properties cannot be updated or removed."

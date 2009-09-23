<?php

$solrObject = new SolrObject();

try
{
   @$solrObject->email = "iekpo@php.net";

} catch (Exception $e) {

    var_dump($e->getCode());

    var_dump($e->getMessage());
}

var_dump($solrObject->getPropertyNames());
?>
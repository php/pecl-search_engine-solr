--TEST--
SolrClient::rollback() - Testing rollback
--SKIPIF--
<?php
include 'skip.if.server_not_configured.inc';
?>
--FILE--
<?php

require_once "bootstrap.inc";

$options = array
(
    'hostname' => SOLR_SERVER_HOSTNAME,
    'login'    => SOLR_SERVER_USERNAME,
    'password' => SOLR_SERVER_PASSWORD,
    'port'     => SOLR_SERVER_PORT,
	'path'	   => SOLR_SERVER_PATH
);

$client = new SolrClient($options);
$updateResponse = $client->rollback();
print $updateResponse->getRawRequest();
?>
--EXPECTF--
<?xml version="1.0" encoding="UTF-8"?>
<rollback/>
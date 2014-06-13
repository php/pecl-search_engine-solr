--TEST--
SolrClient::commit() - Test commit with arguments
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
);

$client = new SolrClient($options);

$updateResponse = $client->commit(true,true,true);
print_r($updateResponse->getRawRequest());
?>
--EXPECTF--
<?xml version="1.0" encoding="UTF-8"?>
<commit waitFlush="true" waitSearcher="true" expungeDeletes="true"/>
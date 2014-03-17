--TEST--
SolrClient::commit() - Test commit with arguments (User of deprecated maxSegments)
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

$updateResponse = $client->commit(2,true,true,true);
print_r($updateResponse->getRawRequest());
?>
--EXPECTF--
Deprecated: SolrClient::commit(): Use of $maxSegments is deprecated, and will be removed in the next release in %s on line %d
<?xml version="1.0" encoding="UTF-8"?>
<commit waitFlush="true" waitSearcher="true" expungeDeletes="true"/>
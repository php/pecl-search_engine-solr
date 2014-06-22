--TEST--
SolrClient::commit() - Testing commit
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
$updateResponse = $client->commit();
print $updateResponse->getRawRequest();
$updateResponse = $client->commit(true,false,true);
print $updateResponse->getRawRequest();

$updateResponse = $client->commit(true,false,true);
?>
--EXPECTF--
<?xml version="1.0" encoding="UTF-8"?>
<commit softCommit="false" waitSearcher="true" expungeDeletes="false"/>
<?xml version="1.0" encoding="UTF-8"?>
<commit softCommit="true" waitSearcher="false" expungeDeletes="true"/>
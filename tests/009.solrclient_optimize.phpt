--TEST--
SolrClient::optimize() - Testing optimize
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
$updateResponse = $client->optimize();
print $updateResponse->getRawRequest();
$updateResponse = $client->optimize(4,true,false);
print $updateResponse->getRawRequest();
?>
--EXPECTF--
<?xml version="1.0" encoding="UTF-8"?>
<optimize maxSegments="1" softCommit="false" waitSearcher="true"/>
<?xml version="1.0" encoding="UTF-8"?>
<optimize maxSegments="4" softCommit="true" waitSearcher="false"/>

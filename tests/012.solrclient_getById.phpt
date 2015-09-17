--TEST--
SolrClient::getById() - Testing Real Time Get by id
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
$response = $client->getById('GB18030TEST');
var_dump(isset($response->getArrayResponse()['doc'])).PHP_EOL;
var_dump($response->getResponse()->doc->id) . PHP_EOL;
?>
--EXPECTF--
bool(true)
string(11) "GB18030TEST"
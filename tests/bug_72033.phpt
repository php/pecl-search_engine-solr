--TEST--
Solr Bug #72033 - Real Time Get requests fails if it wasn't the first request
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
    'path'     => SOLR_SERVER_PATH
);

$client = new SolrClient($options);

$doc = new SolrInputDocument();

$doc->addField('id', 'some_id');
$doc->addField('field1', 'val1');

$client->addDocument($doc);

$client->commit();

$response = $client->getById('some_id');

var_dump(isset($response->getArrayResponse()['doc'])).PHP_EOL;
var_dump($response->getResponse()->doc->id) . PHP_EOL;
// pointless request just to fill the request buffer
$client->commit();


$response = $client->getByIds(['GB18030TEST', '6H500F0']);

var_dump($response->getResponse()->response->docs[0]->id, $response->getResponse()->response->docs[1]->id);
?>
--EXPECTF--
bool(true)
string(7) "some_id"
string(11) "GB18030TEST"
string(7) "6H500F0"

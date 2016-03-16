--TEST--
SolrClient::threads() - Solr Threads Info
--SKIPIF--
<?php require_once 'skip.if.server_not_configured.inc'; ?>
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

$response = $client->threads()->getResponse();

print_r($response->system->threadCount);
?>
--EXPECTF--
SolrObject Object
(
    [current] => %d
    [peak] => %d
    [daemon] => %d
)

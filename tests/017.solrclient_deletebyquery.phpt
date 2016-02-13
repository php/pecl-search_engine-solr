--TEST--
SolrClient::deleteByQuery() - delete by query
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

$serverOutput = $client->deleteByQuery('id:3675');

$response = $serverOutput->getResponse();

print_r($serverOutput->getRawRequest());
print_r($response);
?>
--EXPECTF--
<?xml version="1.0" encoding="UTF-8"?>
<delete>
  <query>id:3675</query>
</delete>
SolrObject Object
(
    [responseHeader] => SolrObject Object
        (
            [status] => %d
            [QTime] => %d
        )

)

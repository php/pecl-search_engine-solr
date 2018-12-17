--TEST--
SolrClient::deleteByQueries() - delete by multiple queries
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

$serverOutput = $client->deleteByQueries([
	'id:3675',
	'id:2548'
]);

$response = $serverOutput->getResponse();

print_r($serverOutput->getRawRequest());
print_r($response);

try {
	$client->deleteByQueries(array(0,''));
} catch (SolrIllegalArgumentException $e) {
	echo sprintf("Exception %d: %s", $e->getCode(), $e->getMessage());
}
?>
--EXPECTF--
<?xml version="1.0" encoding="UTF-8"?>
<delete>
  <query>id:3675</query>
  <query>id:2548</query>
</delete>
SolrObject Object
(
    [responseHeader] => SolrObject Object
        (
            [status] => %d
            [QTime] => %d
        )

)
Exception 4000: Query number 1 is not a valid query string


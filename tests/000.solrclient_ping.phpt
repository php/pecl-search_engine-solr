--TEST--
SolrClient::ping() - Ping Solr Server
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

$pingResponse = $client->ping();

echo $pingResponse->getRawResponse();
?>
--EXPECT--
HTTP/1.1 200 OK
Content-Type: application/xml; charset=UTF-8
Content-Length: 0
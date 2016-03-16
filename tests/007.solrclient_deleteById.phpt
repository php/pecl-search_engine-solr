--TEST--
SolrClient::deleteById() - Testing deleting a document by ID
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
$response = $client->deleteById('334457');
$client->commit();
print_r($response->getResponse());
?>
--EXPECTF--
SolrObject Object
(
    [responseHeader] => SolrObject Object
        (
            [status] => %d
            [QTime] => %d
        )

)

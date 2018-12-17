--TEST--
SolrClient::__clone() - expect exception on clone
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

try {
	$failing = clone $client;
} catch (SolrIllegalOperationException $e) {
	echo sprintf("Exception %d: %s", $e->getCode(), $e->getMessage()) . PHP_EOL;
}

?>
--EXPECTF--
Exception 4001: Cloning of SolrClient objects is currently not supported
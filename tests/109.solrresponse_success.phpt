--TEST--
SolrResponse::success() - Was the request successful
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
	'path'	   => SOLR_SERVER_PATH,
);


$client = new SolrClient($options);

$query = new SolrQuery();

$query->setQuery('lucene');

$query_response = $client->query($query);

var_dump($query_response->success());
?>
--EXPECTF--
bool(true)
--TEST--
Solr Server 4+ Compatibility Test
--SKIPIF--
<?php require_once 'skip.if.server_not_configured.inc'; ?>
--FILE--
<?php

require_once "bootstrap.inc";
// force to timeout trying to resolve
$options = array
(
		'hostname' => SOLR_SERVER_HOSTNAME,
		'login'    => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'port'     => SOLR_SERVER_PORT,
		'path'	   => SOLR_SERVER_PATH
);

$client = new SolrClient($options);

$query_response = $client->system();
$solrVersion = $query_response->getResponse()->lucene['solr-spec-version'];

$match = preg_match('#([0-9]+)\.[0-9]+\.[0-9]+#', $solrVersion, $matches);

var_dump($matches[1] >=4 );
?>
--EXPECTF--
bool(true)
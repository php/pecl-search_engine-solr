--TEST--
Solr Bug #69156 - segfault on 500 response from Solr
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
		'path'	   => 'solr/collection44444',
		'wt'       => 'phps'
);

$client = new SolrClient($options);
$query = new SolrQuery("lucene");
try {
	$query_response = $client->query($query);
} catch (Exception $e) {
}
?>
--EXPECTF--
Notice: SolrClient::query(): Unable to parse serialized php response in %s on line %d

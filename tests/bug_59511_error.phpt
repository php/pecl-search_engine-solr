--TEST--
Solr bug #59511 - SolrClient::query() Timeout shall throw a SolrClientException
--SKIPIF--
<?php require_once 'skip.if.server_not_configured.inc'; ?>
--FILE--
<?php

require_once "bootstrap.inc";
// force to timeout trying to resolve
$options = array
(
		'hostname' => 'anyhost',
		'login'    => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'port'     => SOLR_SERVER_PORT,
		'path'	   => SOLR_SERVER_PATH,
		'timeout'  => 2
);

$client = new SolrClient($options);
$query = new SolrQuery("lucene");
try {
	$query_response = $client->query($query);	
} catch (SolrClientException $e) {
	echo $e->getMessage().PHP_EOL;
	echo $e->getCode().PHP_EOL;
}
?>
--EXPECTF--
Solr HTTP Error %d: '%s' 
1004
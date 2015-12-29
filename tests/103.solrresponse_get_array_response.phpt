--TEST--
SolrResponse::getArrayResponse - For All response writers
--SKIPIF--
<?php
include 'skip.if.server_not_configured.inc';
?>
--FILE--
<?php
require_once "bootstrap.inc";

$options = array (
		'hostname' => SOLR_SERVER_HOSTNAME,
		'login' => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'port' => SOLR_SERVER_PORT,
		'path' => SOLR_SERVER_PATH,
);

$client = new SolrClient ( $options );


$testArrayResponse = function ($writer) use ($client){
	$client->setResponseWriter($writer);
	$q = new SolrQuery("lucene");
	$response = $client->query ( $q );
	$arrayResponse = $response->getArrayResponse();
	return is_array($arrayResponse);
};

var_dump($testArrayResponse('phps'));
var_dump($testArrayResponse('xml'));
var_dump($testArrayResponse('json'));
?>
--EXPECTF--
bool(true)
bool(true)
bool(true)
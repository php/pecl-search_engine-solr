--TEST--
SolrServerException (json) - Throw Exception on solr server call
--SKIPIF--
<?php require_once 'skip.if.server_not_configured.inc'; ?>
--FILE--
<?php
require_once "bootstrap.inc";

$options = array (
		'hostname' => SOLR_SERVER_HOSTNAME,
		'login' => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'port' => SOLR_SERVER_PORT,
		'path' => SOLR_SERVER_PATH,
		'wt' => 'json' 
);

$client = new SolrClient ( $options );
$query = new SolrQuery ( "lucene:*:*" );
try {
	$response = $client->query ( $query );
} catch ( SolrServerException $e ) {
	echo sprintf("code: %d", $e->getCode()).PHP_EOL;
	echo sprintf("message: %s", $e->getMessage()).PHP_EOL;
}

?>
--EXPECTF--
code: %d
message: %s
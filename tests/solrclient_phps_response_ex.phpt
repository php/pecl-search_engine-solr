--TEST--
SolrServerException (xml) - Throw Exception on solr server exception using xml response writer
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
		'wt' => 'phps' 
);

$client = new SolrClient ( $options );
$query = new SolrQuery ( "iTunes" );
$response = $client->query($query);
$responseSolrObj = $response->getResponse();
var_dump(is_array($responseSolrObj));
?>
--EXPECTF--
bool(true)
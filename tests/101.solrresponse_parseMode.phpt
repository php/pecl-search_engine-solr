--TEST--
SolrResponse - ParseMode
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
		'wt' => 'xml' 
);

$client = new SolrClient ( $options );
$query = new SolrQuery ( "lucene" );

$response = $client->query ( $query );

$response->setParseMode(SolrResponse::PARSE_SOLR_DOC);
$x = $response->getResponse();
var_dump($x->response->docs[0] instanceof SolrDocument);
?>
--EXPECTF--
bool(true)
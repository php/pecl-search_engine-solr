--TEST--
SolrClient::system() - Retrieve Solr Server/System Info
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

$genericResponse = $client->system();
var_dump(get_class($genericResponse->getResponse())) . PHP_EOL;
var_dump(get_class($genericResponse->getResponse()->system));
?>
--EXPECTF--
string(10) "SolrObject"
string(10) "SolrObject"

--TEST--
SolrClient - PHPS response writer support
--FILE--
<?php
require_once "bootstrap.inc";
ERROR_REPORTING(E_ALL);
$options = array (
		'hostname' => SOLR_SERVER_HOSTNAME,
		'login' => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'port' => SOLR_SERVER_PORT,
		'path' => SOLR_SERVER_PATH,
);

$client = new SolrClient ( $options );
$client->setResponseWriter('phps');
$options = $client->getOptions();
var_dump($options['wt'] == 'phps');
?>
--EXPECTF--
bool(true)
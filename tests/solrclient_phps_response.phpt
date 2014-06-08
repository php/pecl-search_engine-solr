--TEST--
SolrClient - Support phps Response Writer
--FILE--
<?php
require_once "bootstrap.inc";
error_reporting(E_ALL);
$options = array (
		'hostname' => SOLR_SERVER_HOSTNAME,
		'login' => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'port' => SOLR_SERVER_PORT,
		'path' => SOLR_SERVER_PATH,
		'wt' => 'phps' 
);

$client = new SolrClient ( $options );
?>
--EXPECTF--
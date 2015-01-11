<?php
chdir('examples/');
require_once "bootstrap.php";

// force to timeout trying to resolve
$options = array
(
		'hostname' => SOLR_SERVER_HOSTNAME,
		'login'    => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'port'     => SOLR_SERVER_PORT,
		'path'	   => SOLR_SERVER_PATH,
		'wt'		=> 'json'
);

$client = new SolrClient($options);
$query = new SolrQuery("lucene/");
try
{
$response = $client->query($query);
print_r($response);
}catch(Exception $e)
{
print_r($e);
}


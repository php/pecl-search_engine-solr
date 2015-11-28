--TEST--
SolrClient::query() - Query child documents SolrObject (Integ)
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
		'path' => SOLR_SERVER_STORE_PATH,
		'wt' => 'xml' 
);

$client = new SolrClient ( $options );

$query = new SolrQuery ();

$query->setQuery ( 'id:1 AND {!parent which=$parentFilter}' );
$query->setParam ( 'parentFilter', 'content_type_s:product' );
$query->addFilterQuery('{!parent which=$parentFilter}');

$query->addField ( '*' );
$query->addField ( '[child parentFilter=$parentFilter]' );

$query->setStart ( 0 );

$query->setRows ( 50 );
$queryResponse = $client->query ( $query );

$response = $queryResponse->getResponse ();
echo "----XML----" . PHP_EOL;
var_dump($response->response->docs[0]->_childDocuments_[0]->id);

echo "----JSON----" . PHP_EOL;
$options['wt'] = 'json';
$client = new SolrClient ( $options );
$queryResponse = $client->query($query);
$response = $queryResponse->getResponse ();
var_dump($response->response->docs[0]->_childDocuments_[0]->id);
?>
--EXPECT--
----XML----
string(9) "IMM-HOW-S"
----JSON----
string(9) "IMM-HOW-S"
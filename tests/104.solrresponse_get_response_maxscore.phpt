--TEST--
SolrResponse::getResponse() - maxScore
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
		'wt'=> 'xml'
);

$client = new SolrClient ( $options );

$q = new SolrQuery("lucene");
$q->addField('score');
$response = $client->query ( $q );
$arrayResponse = $response->getArrayResponse();
var_dump($arrayResponse['response']['maxScore']);
var_dump($response->getResponse()->response->maxScore);
var_dump($response->getResponse()->response->start);
var_dump($response->getResponse()->response->numFound);
var_dump(is_array($response->getResponse()->response->docs));
echo "------ W/O maxScore ------".PHP_EOL;
$q->removeField('score');
$response = $client->query ( $q );
var_dump($response->getResponse()->response->start);
var_dump($response->getResponse()->response->numFound);
var_dump(is_array($response->getResponse()->response->docs));
var_dump(property_exists($response->getResponse()->response, 'maxScore'));
?>
--EXPECTF--
float(%f)
float(%f)
int(%d)
int(%d)
bool(true)
------ W/O maxScore ------
int(0)
int(1)
bool(true)
bool(false)
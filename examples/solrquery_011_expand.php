<?php 

include "bootstrap.php";

$options = array
(
		'hostname' => SOLR_SERVER_HOSTNAME,
		'login'    => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'port'     => SOLR_SERVER_PORT,
		'path'	   => SOLR_SERVER_PATH
);

$client = new SolrClient($options);

$query = new SolrQuery('*:*');

$func = new SolrCollapseFunction('manu_id_s');

$query->collapse($func);

$query->setExpand(true);
$query->setExpandRows(10);
$query->setExpandQuery('manu_id_s:corsair');
$query->addExpandFilterQuery('inStock:true');
$query->addExpandSortField('score', SolrQuery::ORDER_DESC);

$queryResponse = $client->query($query);

$response = $queryResponse->getResponse();

print_r($response);

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

$collapseFunction = new SolrCollapseFunction('manu_id_s');

$collapseFunction
->setSize(2)
->setNullPolicy(SolrCollapseFunction::NULLPOLICY_IGNORE);

// $collapseFunction->setMax('sum(cscore(),field(A))');

$query
->collapse($collapseFunction)
->setRows(4);

$queryResponse = $client->query($query);

$response = $queryResponse->getResponse();

print_r($response);

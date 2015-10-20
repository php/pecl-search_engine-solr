<?php 

include "bootstrap.php";

$options = array
(
		'hostname' => SOLR_SERVER_HOSTNAME,
		'login'    => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'port'     => SOLR_SERVER_PORT,
		'path'     => SOLR_SERVER_PATH
);

$client = new SolrClient($options);

$query = new SolrDismaxQuery('*:*');

$query->setRows(4);

$query->setGroup(true);

$query->addGroupField('manu_s_id');

$query->setGroupLimit(2);

$query->addGroupSortField('price', SolrQuery::ORDER_ASC);

$query->setGroupNGroups(true);

$query_response = $client->query($query);

$response = $query_response->getResponse();

print_r($response);


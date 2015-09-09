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

$query = new SolrQuery('*:*');

$query->setGroup(true);

$query->addGroupField('manu');

$query->addGroupFunction('ceil(internalScore)');

$query->addGroupQuery('silk')->addGroupQuery('name:june');

$query->setGroupLimit(98);

$query->setGroupOffset(110);

$query->addGroupSortField('count', SolrQuery::ORDER_ASC);
$query->addGroupSortField('name', SolrQuery::ORDER_DESC);

$query->setGroupFormat('simple');

$query->setGroupMain(false);

$query->setGroupNGroups(false);

$query->setGroupTruncate(true);

$query->setGroupFacet(true);


$query->setGroupCachePercent(100);

$query_response = $client->query($query);

$response = $query_response->getResponse();

print_r($response);


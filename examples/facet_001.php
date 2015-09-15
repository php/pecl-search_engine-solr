<?php

include "bootstrap.php";

$options = array
(
    'hostname' => SOLR_SERVER_HOSTNAME,
    'login'    => SOLR_SERVER_USERNAME,
    'password' => SOLR_SERVER_PASSWORD,
    'port'     => SOLR_SERVER_PORT,
    'path'     => SOLR_SERVER_PATH,
);

$client = new SolrClient($options);

$query = new SolrQuery('*:*');

$query->setFacet(true);

$query->addFacetField('cat')->addFacetField('name')->setFacetMinCount(2);

$updateResponse = $client->query($query);

$response_array = $updateResponse->getResponse();

$facet_data = $response_array->facet_counts->facet_fields;

print_r($facet_data);

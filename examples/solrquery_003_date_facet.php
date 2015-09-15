<?php

include "bootstrap.php";

$options = array(
    'hostname' => SOLR_SERVER_HOSTNAME,
    'login'    => SOLR_SERVER_USERNAME,
    'password' => SOLR_SERVER_PASSWORD,
    'port'     => SOLR_SERVER_PORT,
    'path'     => SOLR_SERVER_PATH,
);

$client = new SolrClient($options);

$query = new SolrQuery('*:*');

$query->setFacet(true);

$query->addFacetDateField('manufacturedate_dt');

$query->setFacetDateStart('2006-02-13T00:00:00Z');

$query->setFacetDateEnd('2012-02-13T00:00:00Z');

$query->setFacetDateGap('+1YEAR');

$query->setFacetDateHardEnd(1);

$query->addFacetDateOther('before');

$updateResponse = $client->query($query);

$response_array = $updateResponse->getResponse();

$facet_data = $response_array->facet_counts->facet_dates;

print_r($facet_data);

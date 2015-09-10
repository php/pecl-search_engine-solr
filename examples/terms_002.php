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

$query = new SolrQuery();

$query->setTerms(true);

/* Return only terms starting with $prefix */
$prefix = 'c';

$query->setTermsField('cat')->setTermsPrefix($prefix);

$updateResponse = $client->query($query);

print_r($updateResponse->getResponse());

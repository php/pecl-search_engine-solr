<?php

include "bootstrap.php";

$options = array
(
    'hostname' => SOLR_SERVER_HOSTNAME,
    'login'    => SOLR_SERVER_USERNAME,
    'password' => SOLR_SERVER_PASSWORD,
    'port'     => SOLR_SERVER_PORT,
);

$client = new SolrClient($options);

$query = new SolrQuery();

$userInput = 'USB/2';

$escapedUserInput = SolrUtils::escapeQueryChars($userInput);

$query->setQuery('text:'.$escapedUserInput);

echo $query.PHP_EOL;

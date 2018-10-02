--TEST--
SolrClient::query() - Terms component
--SKIPIF--
<?php
include 'skip.if.server_not_configured.inc';
?>
--FILE--
<?php

require_once "bootstrap.inc";

$options = array
(
    'hostname' => SOLR_SERVER_HOSTNAME,
    'login'    => SOLR_SERVER_USERNAME,
    'password' => SOLR_SERVER_PASSWORD,
    'port'     => SOLR_SERVER_PORT,
    'path'	   => SOLR_SERVER_PATH,
);


$client = new SolrClient($options);

$query = new SolrQuery('*:*');

$query->setTerms(true);

$query->setTermsField('name');

$query->setTermsLowerBound('a');

$query->setTermsSort(SolrQuery::TERMS_SORT_INDEX);

$query_response = $client->query($query);

echo $query_response->getRequestUrl() .PHP_EOL;

print_r($query_response->getResponse());

?>
--EXPECTF--
http://%s/solr/collection1/terms/?version=2.2&indent=on&wt=xml
SolrObject Object
(
    [responseHeader] => SolrObject Object
        (
            [status] => %d
            [QTime] => %d
        )

    [terms] => SolrObject Object
        (
            [name] => SolrObject Object
                (
                    [iPod & iPod Mini USB 2.0 Cable] => %d
                )

        )

)

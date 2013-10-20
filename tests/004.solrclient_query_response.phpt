--TEST--
SolrClient::query() - Sending a chained query request
--EXTENSIONS--
libxml
curl
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
);

$client = new SolrClient($options);

$query = new SolrQuery();

$query->setQuery('lucene');

$query->setStart(0);

$query->setRows(50);

$query->addField('cat')->addField('features')->addField('id')->addField('timestamp');

$query_response = $client->query($query);

$response = $query_response->getResponse();

print_r($response);

?>
--EXPECTF--
SolrObject Object
(
    [responseHeader] => SolrObject Object
        (
            [status] => 0
            [QTime] => %d
            [params] => SolrObject Object
                (
                    [fl] => cat,features,id,timestamp
                    [indent] => on
                    [start] => 0
                    [q] => lucene
                    [wt] => xml
                    [version] => 2.2
                    [rows] => 50
                )

        )

    [response] => SolrObject Object
        (
            [numFound] => 2
            [start] => 0
            [docs] => Array
                (
                    [0] => SolrObject Object
                        (
                            [id] => 334455
                            [cat] => Array
                                (
                                    [0] => Software
                                    [1] => Lucene
                                )

                        )

                    [1] => SolrObject Object
                        (
                            [cat] => Array
                                (
                                    [0] => Software
                                    [1] => Lucene
                                )

                            [id] => 334456
                        )

                )

        )

)

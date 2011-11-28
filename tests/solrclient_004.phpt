--TEST--
SolrClient::query() - Sending a chained query request
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
            [status] => %d
            [QTime] => %d
            [params] => SolrObject Object
                (
                    [wt] => xml
                    [rows] => 50
                    [start] => 0
                    [indent] => on
                    [q] => lucene
                    [fl] => cat,features,id,timestamp
                    [version] => 2.2
                )

        )

    [response] => SolrObject Object
        (
            [numFound] => 5
            [start] => 0
            [docs] => Array
                (
                    [0] => SolrObject Object
                        (
                            [cat] => Array
                                (
                                    [0] => Software
                                    [1] => Lucene
                                )

                            [id] => 334455
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

                    [2] => SolrObject Object
                        (
                            [cat] => Array
                                (
                                    [0] => Software
                                    [1] => Lucene
                                )

                            [id] => 334455
                        )

                    [3] => SolrObject Object
                        (
                            [cat] => Array
                                (
                                    [0] => Software
                                    [1] => Lucene
                                )

                            [id] => 334456
                        )

                    [4] => SolrObject Object
                        (
                            [cat] => Array
                                (
                                    [0] => software
                                    [1] => search
                                )

                            [features] => Array
                                (
                                    [0] => Advanced Full-Text Search Capabilities using Lucene
                                    [1] => Optimized for High Volume Web Traffic
                                    [2] => Standards Based Open Interfaces - XML and HTTP
                                    [3] => Comprehensive HTML Administration Interfaces
                                    [4] => Scalability - Efficient Replication to other Solr Search Servers
                                    [5] => Flexible and Adaptable with XML configuration and Schema
                                    [6] => Good unicode support: héllo (hello with an accent over the e)
                                )

                            [id] => SOLR1000
                            [timestamp] => 2009-09-04T20:38:55.906
                        )

                )

        )

)

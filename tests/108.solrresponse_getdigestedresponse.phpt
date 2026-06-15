--TEST--
SolrResponse::getDigestedResponse() - Get Raw Response Headers
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
	'path'	   => 'solr/metal_store',
);


$client = new SolrClient($options);

$query = new SolrQuery();

$query->setQuery('artist_s:Satyricon');

$query->setStart(0);

$query->setRows(50);

$query->addField('name_s')->addField('artist_s')->addField('cat')->addField('id');

$query_response = $client->query($query);

// failing without getResponse first (bug)
$response = $query_response->getResponse();

var_dump($query_response->getDigestedResponse());
$digestedResponse = $query_response->getDigestedResponse();
print_r(unserialize($digestedResponse));
?>
--EXPECTF--
string(571) "O:10:"SolrObject":2:{s:14:"responseHeader";O:10:"SolrObject":3:{s:6:"status";i:0;s:5:"QTime";i:%d;s:6:"params";O:10:"SolrObject":7:{s:1:"q";s:18:"artist_s:Satyricon";s:6:"indent";s:2:"on";s:2:"fl";s:22:"name_s,artist_s,cat,id";s:5:"start";s:1:"0";s:4:"rows";s:2:"50";s:7:"version";s:3:"2.2";s:2:"wt";s:3:"xml";}}s:8:"response";O:10:"SolrObject":3:{s:8:"numFound";i:1;s:5:"start";i:0;s:4:"docs";a:1:{i:0;O:10:"SolrObject":4:{s:2:"id";s:1:"3";s:6:"name_s";s:26:"Satyricon - Nemesis Divina";s:8:"artist_s";s:9:"Satyricon";s:3:"cat";a:2:{i:0;s:4:"tops";i:1;s:7:"tshirts";}}}}}"
SolrObject Object
(
    [responseHeader] => SolrObject Object
        (
            [status] => 0
            [QTime] => %d
            [params] => SolrObject Object
                (
                    [q] => artist_s:Satyricon
                    [indent] => on
                    [fl] => name_s,artist_s,cat,id
                    [start] => 0
                    [rows] => 50
                    [version] => 2.2
                    [wt] => xml
                )

        )

    [response] => SolrObject Object
        (
            [numFound] => 1
            [start] => 0
            [docs] => Array
                (
                    [0] => SolrObject Object
                        (
                            [id] => 3
                            [name_s] => Satyricon - Nemesis Divina
                            [artist_s] => Satyricon
                            [cat] => Array
                                (
                                    [0] => tops
                                    [1] => tshirts
                                )

                        )

                )

        )

)
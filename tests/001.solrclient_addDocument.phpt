--TEST--
SolrClient::addDocument() - sending document to the Solr server
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

$doc = new SolrInputDocument();

$doc->addField('id', 334455);
$doc->addField('cat', 'Software');
$doc->addField('cat', 'Lucene');

$doc2 = new SolrInputDocument();

$doc2->addField('id', 12345);
$doc->addField('cat', 'Category1');
$doc->addField('cat', 'Category2');

$updateResponse = $client->addDocument($doc, true, 500);
$updateResponse = $client->addDocument($doc2, true, 500);

print_r($updateResponse->getResponse());

?>
--EXPECTF--
SolrObject Object
(
    [responseHeader] => SolrObject Object
        (
            [status] => 0
            [QTime] => %d
        )

)

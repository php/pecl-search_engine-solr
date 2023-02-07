--TEST--
SolrResponse::getRawResponseHeaders() - Get Raw Response Headers
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

$query = new SolrQuery();

$query->setQuery('lucene');

$query->setStart(0);

$query->setRows(50);

$query->addField('cat')->addField('features')->addField('id')->addField('timestamp');

$query_response = $client->query($query);

$headers = $query_response->getRawResponseHeaders();

$filteredHeaders = implode(
	"\n",
    array_filter(
        explode("\r\n", $headers),
        function($header) {
            return strpos($header, 'HTTP') === 0 || strpos($header, 'Content-Type') === 0;
        }
    )
);

print_r($filteredHeaders);

?>
--EXPECTF--
HTTP/%s 200 OK
Content-Type: %s

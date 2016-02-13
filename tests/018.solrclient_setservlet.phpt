--TEST--
SolrClient::setServlet() - set different servlet for a certain request type
--SKIPIF--
<?php require_once 'skip.if.server_not_configured.inc'; ?>
--FILE--
<?php

require_once "bootstrap.inc";

$options = array
(
    'hostname' => SOLR_SERVER_HOSTNAME,
    'login'    => SOLR_SERVER_USERNAME,
    'password' => SOLR_SERVER_PASSWORD,
    'port'     => SOLR_SERVER_PORT,
    'path'	   => SOLR_SERVER_PATH
);

$client = new SolrClient($options);

$response = $client->ping();
echo $response->getRequestUrl().PHP_EOL;

$client->setServlet(SolrClient::PING_SERVLET_TYPE, 'select');
$response = $client->ping();
echo $response->getRequestUrl().PHP_EOL;

?>
--EXPECTF--
http://%s/solr/collection1/admin/ping/?version=2.2&indent=on&wt=xml
http://%s/solr/collection1/select/?version=2.2&indent=on&wt=xml

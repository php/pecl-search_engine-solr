--TEST--
Solr Bug #71568 - locale float formatting is inconsistent
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
var_dump(setlocale ( LC_NUMERIC, NULL));
$document = new \SolrInputDocument();
$document->setBoost(10000000.110);
$document->addField('x', 1);
$documentArr = array($document);
$response = $client->addDocuments($documentArr);

?>
--EXPECT--
string(11) "da_DK.UTF-8"


--TEST--
Solr Bug #70496 - VERIFYING
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
    'path'     => SOLR_SERVER_PATH,
);

$client = new SolrClient($options);

$query = new SolrQuery('*:*');
$query->setGroup(true);
$query->addGroupField('manu_id_s');
$query->setGroupLimit(10);
$resp1 = $client->query($query); // works
$query = new SolrQuery('*:*');
$query->setGroup(true);
$query->addGroupField('manu_id_s');
$query->setGroupLimit(0);
echo $query;
$resp2 = $client->query($query); // throws Exception
print_r($resp2);
?>
--EXPECTF--

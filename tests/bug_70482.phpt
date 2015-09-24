--TEST--
Solr Bug #70482 - Segmentation fault on server 500 response with no msg field XML RW
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
		'path'	   => SOLR_SERVER_PATH,
		'wt'	   => 'xml'
);

$client = new SolrClient($options);

$query = new SolrQuery('*:*');

$func = new SolrCollapseFunction('manu_id_s');

$func->setMax('sum(cscore(),field(manu_id_s))');
$func->setSize(100);
$func->setNullPolicy(SolrCollapseFunction::NULLPOLICY_EXPAND);

$query->collapse($func);
try {
	$queryResponse = $client->query($query);
} catch (SolrServerException $e) {
	printf("Exception code %d", $e->getCode());
	assert(strlen($e->getMessage()) > 0, 'Exception message is empty');
	echo PHP_EOL;
}

?>
OK
--EXPECTF--
Exception code %d
OK
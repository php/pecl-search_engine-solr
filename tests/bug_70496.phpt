--TEST--
Solr Bug #70496 - Failed to parse 500 error response when Solr it lacks msg PHPS RW
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
		'wt'	   => 'phps'
);

$client = new SolrClient($options);

$query = new SolrQuery('*:*');

$func = new SolrCollapseFunction('manu_id_s');

$func->setMax('sum(cscore(),field(manu_id_s))');  
$func->setNullPolicy(SolrCollapseFunction::NULLPOLICY_EXPAND);

$query->collapse($func);
try {
	$queryResponse = $client->query($query);
} catch (SolrServerException $e) {
	printf("Exception code %d", $e->getCode());
	assert(strlen($e->getMessage()) > 0, 'Exception message is empty');
}

?>

OK
--EXPECTF--
Exception code 500
OK
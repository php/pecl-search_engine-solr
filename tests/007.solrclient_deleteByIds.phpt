--TEST--
SolrClient::deleteByIds() - Test deleting documents by an array of IDS
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
	'path'	   => SOLR_SERVER_PATH
);

$client = new SolrClient($options);
$response = $client->deleteByIds(array('334455','334456'));
$client->commit();
print_r($response->getResponse());

try {
	$client->deleteByIds(array(0));	
} catch (SolrIllegalArgumentException $e) {
	echo sprintf("Exception %d: %s", $e->getCode(), $e->getMessage()). PHP_EOL;
}

try {
	$client->deleteByIds(array('334455', ''));
} catch (SolrIllegalArgumentException $e) {
	echo sprintf("Exception %d: %s", $e->getCode(), $e->getMessage()). PHP_EOL;
}

?>
--EXPECTF--
SolrObject Object
(
    [responseHeader] => SolrObject Object
        (
            [status] => %d
            [QTime] => %d
        )

)
Exception 4000: Id number 1 is not a valid string
Exception 4000: Id number 2 is not a valid string
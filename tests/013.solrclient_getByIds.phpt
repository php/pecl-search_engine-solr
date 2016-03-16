--TEST--
SolrClient::getByIds() - Testing Real Time Get by ids
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
$response = $client->getByIds(['GB18030TEST', '6H500F0']);
var_dump(isset($response->getArrayResponse()['response']['docs'])) . PHP_EOL;
var_dump($response->getResponse()->response->start) . PHP_EOL;
try {
	$response = $client->getByIds(['GB18030TEST', '']);
} catch (Exception $e) {
	printf("Exception %d: %s", $e->getCode(), $e->getMessage());
}
echo PHP_EOL.PHP_EOL;
// make sure request was reset
echo "- Headers start".PHP_EOL;
$response = $client->getByIds(['GB18030TEST']);
$headers = explode(PHP_EOL, trim($response->getRawRequestHeaders()));
sort($headers);
print_r(implode(PHP_EOL, $headers).PHP_EOL);
echo "- Headers End".PHP_EOL;;

echo PHP_EOL;
try {
	$response = $client->getByIds([]);
} catch (Exception $e) {
	printf("Exception %d: %s", $e->getCode(), $e->getMessage());
}
?>
--EXPECTF--
bool(true)
int(0)
Exception 4000: Invalid id at position 1

- Headers start
Accept-Charset: utf-8
Accept: */*
Authorization: Basic YWRtaW46Y2hhbmdlaXQ=
Connection: keep-alive
GET /solr/collection1/get/?version=2.2&indent=on&wt=xml&ids=GB18030TEST HTTP/1.1
Host: %s:8983
Keep-Alive: 300
User-Agent: %s
- Headers End

Exception 4000: Invalid parameter: at least 1 ID is required. Passed an empty array.

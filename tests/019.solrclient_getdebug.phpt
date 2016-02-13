--TEST--
SolrClient::getDebug() - Get request debug logs for the last request
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

$debug = $client->getDebug();

$lines = explode("\n",$debug);
$print = false;
foreach ( $lines as $line) {
	if (FALSE !== strpos($line, 'Connected')) {
		$print = true;
	} elseif ($line == '<?xml version="1.0" encoding="UTF-8"?>') {
		$print = false;
	}
	
	if ($print) {
		echo $line . PHP_EOL;
	}
}
?>
--EXPECTF--
Connected to %s port %d (#0)
Server auth using Basic with user 'admin'
HEAD /solr/collection1/admin/ping/?version=2.2&indent=on&wt=xml HTTP/1.1
Authorization: Basic YWRtaW46Y2hhbmdlaXQ=
User-Agent: PHP Solr Client %s
Host: %s
Accept: */*
Accept-Charset: utf-8
Keep-Alive: 300
Connection: keep-alive

HTTP/1.1 200 OK
Content-Type: application/xml; charset=UTF-8
Content-Length: 0

Connection #0 to host %s left intact

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
sort($lines);
foreach ( $lines as $line) {
	if ($line == '<?xml version="1.0" encoding="UTF-8"?>' ||
		FALSE !== strpos($line, 'Trying') ||
		0 === strpos($line, 'Mark bundle') ||
		0 === strpos($line, 'Server') ||
		0 === strpos($line, 'Hostname') ||
		0 === strpos($line, 'TCP_NODELAY') || 
		0 === strpos($line, 'Accept-Encoding') ||
		0 === strpos($line, 'Curl_http_done')
		) {
		$print = false;
	} else {
		$print = true;
	}

	if ($print) {
		echo $line . "\n";
	}
}
?>
--EXPECTF--
Accept-Charset: utf-8
Accept: */*
Authorization: Basic YWRtaW46Y2hhbmdlaXQ=
Connected to %s (%s) port 8983 (#0)
Connection #0 to host %s left intact
Connection: keep-alive
Content-Length: 0
Content-Type: application/xml; charset=UTF-8
HEAD /solr/collection1/admin/ping/?version=2.2&indent=on&wt=xml HTTP/1.1
HTTP/1.1 200 OK
Host: %s:8983
Keep-Alive: 300
User-Agent: %s

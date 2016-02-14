--TEST--
SolrClient::__construct() - Test options
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
    'path'     => SOLR_SERVER_PATH,
	'timeout'  => 400
);

$client = new SolrClient($options);
$pingResponse = $client->ping();
print_r($pingResponse->getRawResponse());

$options = array
(
    'hostname' => SOLR_SERVER_HOSTNAME,
    'login'    => SOLR_SERVER_USERNAME,
	'port'     => strval(SOLR_SERVER_PORT),
    'password' => SOLR_SERVER_PASSWORD,
    'path'     => '/'.SOLR_SERVER_PATH,
	'timeout'  => '400'
);

$client = new SolrClient($options);
$pingResponse = $client->ping();
print_r($pingResponse->getRawResponse());

$options = array (
		'hostname' => SOLR_SERVER_HOSTNAME,
		'login' => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'path' => SOLR_SERVER_PATH,
		'proxy_host' => 'localhost',
		'proxy_login' => 'test',
		'proxy_password' => 'password',
		'proxy_port' => 8181,
		'query_string_delimiter' => '&'
);

$client = new SolrClient($options);
try {
	$pingResponse = $client->ping();
} catch (SolrClientException $e) {
	print_exception($e);
}

$options = array (
		'hostname' => SOLR_SERVER_HOSTNAME,
		'login' => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'path' => SOLR_SERVER_PATH,
		'proxy_host' => 'localhost',
		'proxy_login' => 'test',
		'proxy_password' => 'password',
		'proxy_port' => '8181',
		'query_string_delimiter' => '&'
);

$client = new SolrClient($options);
try {
	$pingResponse = $client->ping();
} catch (SolrClientException $e) {
	print_exception($e);
}

try {
	$client = new SolrClient(array());
} catch (SolrIllegalArgumentException $e) {
	print_exception($e);
}

$options = array
(
		'hostname' => SOLR_SERVER_HOSTNAME,
		'login'    => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'path'     => SOLR_SERVER_PATH,
		'ssl_cert' => '/tmp/unavailable.crt',
		'ssl_key'  => 'test',
		'ssl_keypassword' => 'test',
		'ssl_cainfo' => 'test',
		'ssl_capath' => '/tmp/'
);

$client = new SolrClient($options);
try {
	$pingResponse = $client->ping();
} catch (SolrClientException $e) {
	print_exception($e);
}

?>
--EXPECTF--
HTTP/1.1 200 OK
Content-Type: application/xml; charset=UTF-8
Content-Length: 0

HTTP/1.1 200 OK
Content-Type: application/xml; charset=UTF-8
Content-Length: 0

SolrClientException 1004: Solr HTTP Error 7: 'Couldn't connect to server' 
SolrClientException 1004: Solr HTTP Error 7: 'Couldn't connect to server' 
SolrIllegalArgumentException 4000: The SolrClient options cannot be an empty array



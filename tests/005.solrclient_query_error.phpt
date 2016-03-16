--TEST--
SolrClient::query() - throw SolrClientException on Solr Server exception
--SKIPIF--
<?php require_once 'skip.if.server_not_configured.inc'; ?>
--FILE--
<?php

require_once "bootstrap.inc";
// force to timeout trying to resolve
$options = array
(
		'hostname' => SOLR_SERVER_HOSTNAME,
		'login'    => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'port'     => SOLR_SERVER_PORT,
		'path'	   => SOLR_SERVER_PATH
);

$client = new SolrClient($options);
$query = new SolrQuery("lucene\\");

try {
	$query_response = $client->query($query);	
} catch (SolrServerException $e) {
	echo $e->getMessage();
}

?>
--EXPECTF--
%s: Cannot parse 'lucene\': Lexical error at line 1, column 8.  Encountered: <EOF> after : ""
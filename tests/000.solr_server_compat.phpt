--TEST--
Solr Server 4 Compatibility Test
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
$query = new SolrQuery("lucene/");

$query_response = $client->query($query);
?>
--EXPECTF--
Fatal error: Uncaught exception 'SolrServerException' with message 'org.apache.lucene.queryparser.classic.ParseException: Cannot parse 'lucene/': Lexical error at line 1, column 8.  Encountered: <EOF> after : ""' in %s:%d
Stack trace:
#0 %s(%d): SolrClient->query(Object(SolrQuery))
#1 {main}
  thrown in %s on line %d
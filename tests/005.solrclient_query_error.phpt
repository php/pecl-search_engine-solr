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
$query = new SolrQuery("lucene/");

$query_response = $client->query($query);
?>
--EXPECTF--
Fatal error: Uncaught exception 'SolrClientException' with message 'Unsuccessful query request : Response Code 400. <?xml version="1.0" encoding="UTF-8"?>
<response>

<lst name="responseHeader">
  <int name="status">400</int>
  <int name="QTime">%d</int>
  <lst name="params">
    <str name="indent">on</str>
    <str name="wt">xml</str>
    <str name="q">lucene/</str>
    <str name="version">2.2</str>
  </lst>
</lst>
<lst name="error">
  <str name="msg">%s</str>
  <int name="code">400</int>
</lst>
</response>
' in %s:%d
Stack trace:
#0 %s(%d): SolrClient->query(Object(SolrQuery))
#1 {main}
  thrown in %s on line %d
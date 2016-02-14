--TEST--
SolrUtils::getSolrStats() - Get Statistics about number of documents/clients..etc
--FILE--
<?php
require_once "bootstrap.inc";

var_dump(SolrUtils::getSolrStats());

$options = array (
		'hostname' => SOLR_SERVER_HOSTNAME,
		'login' => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'port' => SOLR_SERVER_PORT,
		'path' => SOLR_SERVER_PATH
);

$client = new SolrClient ( $options );

$solrDoc = new SolrInputDocument();

$params = new SolrModifiableParams();

var_dump(SolrUtils::getSolrStats());

?>
--EXPECT--
array(3) {
  ["document_count"]=>
  int(0)
  ["client_count"]=>
  int(0)
  ["params_count"]=>
  int(0)
}
array(3) {
  ["document_count"]=>
  int(1)
  ["client_count"]=>
  int(1)
  ["params_count"]=>
  int(1)
}

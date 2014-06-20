--TEST--
SolrClient::getOptions - Returning all the default options
--FILE--
<?php

$options = array('secure' => false);

$client = new SolrClient($options);

var_dump($client->getOptions());

?>
--EXPECTF--
array(17) {
  ["timeout"]=>
  int(30)
  ["secure"]=>
  bool(false)
  ["hostname"]=>
  string(9) "localhost"
  ["wt"]=>
  string(3) "xml"
  ["port"]=>
  int(8983)
  ["proxy_host"]=>
  string(0) ""
  ["proxy_port"]=>
  int(0)
  ["path"]=>
  string(4) "solr"
  ["http_auth"]=>
  string(0) ""
  ["proxy_auth"]=>
  string(0) ""
  ["ssl_verify_peer"]=>
  bool(false)
  ["ssl_verify_host"]=>
  int(2)
  ["ssl_cert"]=>
  string(0) ""
  ["ssl_key"]=>
  string(0) ""
  ["ssl_keypassword"]=>
  string(0) ""
  ["ssl_cainfo"]=>
  string(0) ""
  ["ssl_capath"]=>
  string(0) ""
}

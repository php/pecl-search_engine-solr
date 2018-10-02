--TEST--
SolrResponse::getDigestedResponse() - Get Raw Response Headers
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
	'path'	   => SOLR_SERVER_PATH,
);


$client = new SolrClient($options);

$query = new SolrQuery();

$query->setQuery('lucene');

$query->setStart(0);

$query->setRows(50);

$query->addField('cat')->addField('features')->addField('id')->addField('timestamp');

$query_response = $client->query($query);

var_dump($query_response->getDigestedResponse());
$tmp = $query_response->getResponse();
$digestedResponse = $query_response->getDigestedResponse();
print_r($digestedResponse);
?>
--EXPECTF--
string(1) " "
O:10:"SolrObject":2:{s:14:"responseHeader";O:10:"SolrObject":3:{s:6:"status";i:0;s:5:"QTime";i:%d;s:%d:"params";O:10:"SolrObject":7:{s:1:"q";s:6:"lucene";s:6:"indent";s:2:"on";s:2:"fl";s:25:"cat,features,id,timestamp";s:5:"start";s:1:"0";s:4:"rows";s:2:"50";s:7:"version";s:3:"2.2";s:2:"wt";s:3:"xml";}}s:8:"response";O:10:"SolrObject":3:{s:8:"numFound";i:1;s:5:"start";i:0;s:4:"docs";a:1:{i:0;O:10:"SolrObject":3:{s:2:"id";s:8:"SOLR1000";s:3:"cat";a:2:{i:0;s:8:"software";i:1;s:6:"search";}s:8:"features";a:7:{i:0;s:51:"Advanced Full-Text Search Capabilities using Lucene";i:1;s:37:"Optimized for High Volume Web Traffic";i:2;s:46:"Standards Based Open Interfaces - XML and HTTP";i:3;s:44:"Comprehensive HTML Administration Interfaces";i:4;s:64:"Scalability - Efficient Replication to other Solr Search Servers";i:5;s:56:"Flexible and Adaptable with XML configuration and Schema";i:6;s:62:"Good unicode support: héllo (hello with an accent over the e)";}}}}}
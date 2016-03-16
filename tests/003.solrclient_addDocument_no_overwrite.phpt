--TEST--
SolrClient::addDocument() - Overwrite an existing document
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

$doc = new SolrInputDocument();

$doc->addField('id', 334455);
$doc->addField('cat', 'Software');
$doc->addField('cat', 'Solr');

$updateResponse = $client->addDocument($doc, false);
$client->commit();
print $updateResponse->getRawRequest();
?>
--EXPECT--
<?xml version="1.0" encoding="UTF-8"?>
<add overwrite="false">
  <doc>
    <field name="id">334455</field>
    <field name="cat">Software</field>
    <field name="cat">Solr</field>
  </doc>
</add>

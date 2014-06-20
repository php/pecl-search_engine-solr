--TEST--
SolrClient::addDocuments() - sending a cloned document
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
);

$client = new SolrClient($options);

$doc = new SolrInputDocument();

$doc->addField('id', 334455);
$doc->addField('cat', 'Software');
$doc->addField('cat', 'Lucene');

$doc2 = clone $doc;

$doc2->deleteField('id');
$doc2->addField('id', 334456);

$docs = array($doc, $doc2);

$updateResponse = $client->addDocuments($docs, true, 1024);

print $updateResponse->getRawRequest();

?>
--EXPECT--
<?xml version="1.0" encoding="UTF-8"?>
<add allowDups="true" commitWithin="1024">
  <doc>
    <field name="id">334455</field>
    <field name="cat">Software</field>
    <field name="cat">Lucene</field>
  </doc>
  <doc>
    <field name="cat">Software</field>
    <field name="cat">Lucene</field>
    <field name="id">334456</field>
  </doc>
</add>

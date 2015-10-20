--TEST--
SolrClient::addDocuments() - Sending multiple documents with child documents
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

$doc = new SolrInputDocument();

$doc->addField('id', 'CTEST_1');
$doc->addField('title', 'Solr adds block join support');
$doc->addField('content_type', 'parentDocument');

$doc2 = new SolrInputDocument();
$doc2->addField('id', 'CTEST_2');
$doc2->addField('comment_t', 'SolrCloud supports it too!');

$doc3 = new SolrInputDocument();
$doc3->addField('id', 'CTEST_3');
$doc3->addField('content_type', 'parentDocument');
$doc3->addField('comment_t', 'Lots of features');

$doc4 = new SolrInputDocument();
$doc4->addField('id', 'CTEST_4');
$doc4->addField('comment_t', 'Cool features');

$doc->addChildDocument($doc2);
$doc3->addChildDocument($doc4);

$documents = [$doc, $doc3];

$updateResponse = $client->addDocuments($documents);
print_r($updateResponse->getRawRequest());
print_r($updateResponse->getResponse());
$client->commit();
?>
--EXPECTF--
<?xml version="1.0" encoding="UTF-8"?>
<add overwrite="true">
  <doc>
    <field name="id">CTEST_1</field>
    <field name="title">Solr adds block join support</field>
    <field name="content_type">parentDocument</field>
    <doc>
      <field name="id">CTEST_2</field>
      <field name="comment_t">SolrCloud supports it too!</field>
    </doc>
  </doc>
  <doc>
    <field name="id">CTEST_3</field>
    <field name="content_type">parentDocument</field>
    <field name="comment_t">Lots of features</field>
    <doc>
      <field name="id">CTEST_4</field>
      <field name="comment_t">Cool features</field>
    </doc>
  </doc>
</add>
SolrObject Object
(
    [responseHeader] => SolrObject Object
        (
            [status] => %d
            [QTime] => %d
        )

)
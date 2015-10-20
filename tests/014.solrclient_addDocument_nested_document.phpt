--TEST--
SolrClient::addDocument() - Sending a document with child documents
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
$doc3->addField('comment_t', 'Lots of features');

$doc->addChildDocument($doc2);
$doc->addChildDocument($doc3);

$doc4 = new SolrInputDocument();
$doc4->addField('id', 'CTEST_4');
$doc4->addField('comment_t', 'Child Child');

$doc3->addChildDocument($doc4);

$docs = $doc->getChildDocuments();
$docs[0]->addField('one_more_field_t', 'testing');

$updateResponse = $client->addDocument($doc);
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
      <field name="one_more_field_t">testing</field>
    </doc>
    <doc>
      <field name="id">CTEST_3</field>
      <field name="comment_t">Lots of features</field>
      <doc>
        <field name="id">CTEST_4</field>
        <field name="comment_t">Child Child</field>
      </doc>
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
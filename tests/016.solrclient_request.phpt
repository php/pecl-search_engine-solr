--TEST--
SolrClient::Request() - Sending custom update request
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

$rawAtomicUpdateRequest = <<<REQ
<?xml version="1.0" encoding="UTF-8"?>
<add>
  <doc>
    <field name="id">IW-02</field>
    <field name="weight" update="inc">1</field>
    <field name="features" update="add">New Atomic Update Feature</field>
    <field name="inStock" update="set">true</field>
  </doc>
</add>
REQ;

$response = $client->request($rawAtomicUpdateRequest)->getResponse();
$client->commit();

print_r($response);
?>
--EXPECTF--

SolrObject Object
(
    [responseHeader] => SolrObject Object
        (
            [status] => %d
            [QTime] => %d
        )

)
--TEST--
SolrClient::addDocumnt() - Partial Update (integration)
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

$printDocument = function() use ($client) {
	$response = $client->getById('testing_partials');
	print_r($response->getResponse());
};
// clean up, before running the test
$client->deleteById('testing_partials');
$client->commit();

$initialDoc = new SolrInputDocument();

$initialDoc->addField('id', 'testing_partials');
$initialDoc->addField('field1', 'existing value');
$initialDoc->addField('field1', 'remove me please');
$initialDoc->addField('field1', '15/01/2007');
$initialDoc->addField('field2_s', 'initialField');
$initialDoc->addField('field3_i', 0);
$initialDoc->addField('field4', 'val1');
$initialDoc->addField('field5_s', 'unmodified field');

$client->addDocument($initialDoc);
$client->commit();
separator('INITIAL');
$printDocument();

$doc = new SolrInputDocument();
$doc->addField('id', 'testing_partials');
$doc->updateField('field1', SolrInputDocument::UPDATE_MODIFIER_ADD, 'newly added value');
$doc->updateField('field1', SolrInputDocument::UPDATE_MODIFIER_REMOVE, 'remove me please');
$doc->updateField('field3_i', SolrInputDocument::UPDATE_MODIFIER_INC, 5);
$doc->updateField('field2_s', SolrInputDocument::UPDATE_MODIFIER_SET, 'updated string');
$doc->updateField('field1', SolrInputDocument::UPDATE_MODIFIER_REMOVEREGEX, '[\d]{2}/[\d]{2}/[\d]{4}');

$response = $client->addDocument($doc);
$client->commit();
separator('RAW REQUEST');
print_r($response->getRawRequest());
$client->commit();

separator('RESULT AFTER UPDATE');
$printDocument();
?>
--EXPECTF--
=================================== INITIAL ====================================
SolrObject Object
(
    [doc] => SolrObject Object
        (
            [id] => testing_partials
            [field1] => Array
                (
                    [0] => existing value
                    [1] => remove me please
                    [2] => 15/01/2007
                )

            [field2_s] => initialField
            [field3_i] => 0
            [field4] => Array
                (
                    [0] => val1
                )

            [field5_s] => unmodified field
            [_version_] => %d
        )

)
================================= RAW REQUEST ==================================
<?xml version="1.0" encoding="UTF-8"?>
<add overwrite="true">
  <doc>
    <field name="id">testing_partials</field>
    <field name="field1" update="add">newly added value</field>
    <field name="field1" update="remove">remove me please</field>
    <field name="field1" update="removeregex">[\d]{2}/[\d]{2}/[\d]{4}</field>
    <field name="field3_i" update="inc">5</field>
    <field name="field2_s" update="set">updated string</field>
  </doc>
</add>
============================= RESULT AFTER UPDATE ==============================
SolrObject Object
(
    [doc] => SolrObject Object
        (
            [id] => testing_partials
            [field1] => Array
                (
                    [0] => existing value
                    [1] => newly added value
                )

            [field2_s] => updated string
            [field3_i] => 5
            [field4] => Array
                (
                    [0] => val1
                )

            [field5_s] => unmodified field
            [_version_] => %d
        )

)


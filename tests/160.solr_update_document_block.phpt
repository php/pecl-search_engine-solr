--TEST--
Solr - Fetch and Update nested documents
--SKIPIF--
<?php
include 'skip.if.server_not_configured.inc';
?>
--FILE--
<?php

require_once "bootstrap.inc";

$updateInventory = function ($document, $inventory) {
	$children = $document->getChildDocuments();
	$child = $children[0];
	$child->deleteField('inventory_i');
	$child->addField('inventory_i', $inventory);

	$document->deleteField('_version_');
};

$getInventory = function ($response) {
	return (int) current($response->response->docs[0]->getChildDocuments()[0]['inventory_i']->values);
};

$options = array (
		'hostname' => SOLR_SERVER_HOSTNAME,
		'login' => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'port' => SOLR_SERVER_PORT,
		'path' => SOLR_SERVER_STORE_PATH,
		'wt' => 'xml' 
);

$client = new SolrClient ( $options );

$query = new SolrQuery ('id:1 AND {!parent which=$parentFilter}');

$query->setParam ( 'parentFilter', 'content_type_s:product' );
$query->addFilterQuery('{!parent which=$parentFilter}');

$query->addField ( '*' );
$query->addField ( '[child parentFilter=$parentFilter]' );

$query->setStart ( 0 );
$query->setRows ( 1 );

// query existing inventory
$queryResponse = $client->query ( $query );
$queryResponse->setParseMode(SolrResponse::PARSE_SOLR_DOC);
$response = $queryResponse->getResponse();
$existingInventory = $getInventory($response);

// update inventory to 300
$document = $response->response->docs[0]->getInputDocument();
$updateInventory($document, 300);
$client->addDocument($document);
$client->commit();

// fetch the document again after the update
$queryResponse = $client->query ( $query );
$queryResponse->setParseMode(SolrResponse::PARSE_SOLR_DOC);
$response = $queryResponse->getResponse();
$newInventory = $getInventory($response);
assert($newInventory == 300);


echo "------EXISTING------" . PHP_EOL;
var_dump($existingInventory);
echo "----AFTER UPDATE----" . PHP_EOL;
var_dump($newInventory);

// cleanup: restore document's original state
$document = $response->response->docs[0]->getInputDocument();
$updateInventory($document, $existingInventory);
$client->addDocument($document);
$client->commit();
?>
--EXPECT--
------EXISTING------
int(200)
----AFTER UPDATE----
int(300)
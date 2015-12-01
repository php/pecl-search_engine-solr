<?php

include "bootstrap.php";

$options = array
(
    'hostname' => SOLR_SERVER_HOSTNAME,
    'login'    => SOLR_SERVER_USERNAME,
    'password' => SOLR_SERVER_PASSWORD,
    'port'     => SOLR_SERVER_PORT,
    'path'     => SOLR_SERVER_STORE_PATH,
);

$client = new SolrClient($options);

$product = new SolrInputDocument();

$product->addField('id', 'black');
$product->addField('cat', 'tshirt');
$product->addField('cat', 'polo');
$product->addField('content_type', 'product');

$small = new SolrInputDocument();
$small->addField('id', 'TS-BLK-S');
$small->addField('content_type', 'sku');
$small->addField('size', 'S');
$small->addField('inventory', 100);

$medium = new SolrInputDocument();
$medium->addField('id', 'TS-BLK-M');
$medium->addField('content_type', 'sku');
$medium->addField('size', 'M');
$medium->addField('inventory', 200);

$large = new SolrInputDocument();
$large->addField('id', 'TS-BLK-L');
$large->addField('content_type', 'sku');
$large->addField('size', 'L');
$large->addField('inventory', 300);

// add child documents 
$product->addChildDocument($small);
$product->addChildDocument($medium);
$product->addChildDocument($large);
// or 
// $skus = [$small, $medium, $large];
// $product->addChildDocuments($skus);

// add product document to the index
$updateResponse = $client->addDocument(
		$product,
		true, // overwrite if the document exists
		10000 // commit within 10 seconds
);

print_r($updateResponse->getResponse());

/* OUTPUT SIMILAR TO:
SolrObject Object
(
    [responseHeader] => SolrObject Object
        (
            [status] => 0
            [QTime] => 5
        )
)
*/

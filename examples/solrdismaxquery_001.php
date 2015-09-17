<?php
include "bootstrap.php";

$options = array
(
	'hostname' => SOLR_SERVER_HOSTNAME,
	'login'    => SOLR_SERVER_USERNAME,
	'password' => SOLR_SERVER_PASSWORD,
	'port'     => SOLR_SERVER_PORT,
	'path'     => SOLR_SERVER_PATH,
);

$client = new SolrClient($options);

$disMaxQuery = new SolrDisMaxQuery();

$disMaxQuery->setStart(0)->setQuery('solr')->setTimeAllowed(500)->setRows(17);

$disMaxQuery->addSortField('price', 0);

$disMaxQuery
	->setQueryAlt('*:*')->addQueryField('text', 1.5)
	->addQueryField('title', 5)
	->addBoostQuery('cat', 'electronics', 2)
	->setQueryPhraseSlop(1)
	->setBigramPhraseSlop(3)
	->addBigramPhraseField('text', 2.5)
	->addBigramPhraseField('type', 3, 4)
	->setTrigramPhraseFields('content^0.5 anchor~4^1.5 title^1.2 site^1.5')
;

$queryResponse = $client->query($disMaxQuery);

$response = $queryResponse->getResponse();

if($response->response->numFound > 0) {
	$docs = $response->response->docs;
	print_r($docs);
} else {
	echo "No Documents Found".PHP_EOL;
}

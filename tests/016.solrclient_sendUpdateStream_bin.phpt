--TEST--
SolrClient::sendUpdateStream - send SolrExtractRequest (bin)
--SKIPIF--
<?php require_once 'skip.if.server_not_configured.inc'; ?>
--FILE--
<?php

require_once "bootstrap.inc";

$options = array (
	'hostname' => SOLR_SERVER_HOSTNAME,
	'login' => SOLR_SERVER_USERNAME,
	'password' => SOLR_SERVER_PASSWORD,
	'port' => SOLR_SERVER_PORT,
	'path' => SOLR_SERVER_FILES_PATH,
);

$client = new SolrClient($options);

$extractParams = new SolrModifiableParams();

$extractParams
	->set(SolrExtractRequest::LITERALS_PREFIX . 'id', 'doc1')
	->set(SolrExtractRequest::CAPTURE_ELEMENTS, 'p')
	->set(SolrExtractRequest::FIELD_MAPPING_PREFIX . 'p', 'text')
;

$binContent = file_get_contents(EXTRACT_FILE_1);

$extractRequest = SolrExtractRequest::createFromStream($binContent, 'application/pdf', $extractParams);

$response = $client->sendUpdateStream($extractRequest);

$client->rollback();

echo $response->getHttpStatus() . PHP_EOL;
echo $response->getRequestUrl() . PHP_EOL;
?>
--EXPECTF--
200
http://%s/update/extract/?version=2.2&indent=on&wt=xml&literal.id=doc1&capture=p&fmap.p=text

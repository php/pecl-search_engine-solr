--TEST--
Solr - Accept int (strict mode)
--FILE--
<?php
declare(strict_types=1);
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

case_title(1, 'No arguments passed');
$updateResponse = $client->optimize();
print $updateResponse->getRawRequest();

case_title(2, 'int argument passed');
$updateResponse = $client->optimize(4, true, false);
print $updateResponse->getRawRequest();

case_title(3, 'string argument passed');
try {
	$updateResponse = $client->optimize('5', true, false);
} catch (SolrIllegalArgumentException $e) {
	echo $e->getMessage() . PHP_EOL;
}

case_title(4, 'object argument passed');
try {
	$updateResponse = $client->optimize(new StdClass());
} catch (SolrIllegalArgumentException $e) {
	echo $e->getMessage() . PHP_EOL;
}
?>
--EXPECTF--

case #1: No arguments passed
<?xml version="1.0" encoding="UTF-8"?>
<optimize maxSegments="1" softCommit="false" waitSearcher="true"/>

case #2: int argument passed
<?xml version="1.0" encoding="UTF-8"?>
<optimize maxSegments="4" softCommit="true" waitSearcher="false"/>

case #3: string argument passed

case #4: object argument passed
maxSegments must be of type int.
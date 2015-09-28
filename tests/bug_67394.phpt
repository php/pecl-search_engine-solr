--TEST--
Solr Bug #67394 - Unable to parse response with NaN
--FILE--
<?php
require_once 'tests/test.config.inc';

$fixture = file_get_contents(ROOT_DIRECTORY . '/files/bug67394.json');

$response = SolrUtils::digestJsonResponse($fixture);

// json spec: does not conform to NaN
var_dump($response->stats->stats_fields->date->stddev);

$xmlFixture = file_get_contents(ROOT_DIRECTORY . '/files/bug67394.xml');
if (!json_decode($fixture)) {
	echo "PHP JSON DECODE failed with: ". json_last_error_msg().PHP_EOL;
}
$response = SolrUtils::digestXmlResponse($xmlFixture);

var_dump($response->response->stats->stats_fields->currentPrice->mean);
?>
--EXPECTF--
string(3) "NaN"
float(NAN)
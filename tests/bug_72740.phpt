--TEST--
Solr Bug #72740 - addQueryField return wrong query
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
		'path' => SOLR_SERVER_PATH
);

$client = new SolrClient( $options );

$dismaxQuery = new SolrDisMaxQuery( '*:*' );
$dismaxQuery->addPhraseField( "phraseField1", 10, 5 );
$dismaxQuery->addPhraseField( "phraseField2", 5, 1 );
$dismaxQuery->addSortField('score', SolrQuery::ORDER_DESC);
$dismaxQuery->addSortField('manufacturedate_dt', SolrQuery::ORDER_DESC);


$queryResponse = $client->query( $dismaxQuery );

print_r($queryResponse->getResponse()->responseHeader->params);

?>
--EXPECTF--
SolrObject Object
(
    [q] => *:*
    [defType] => edismax
    [indent] => on
    [pf] => phraseField1~5^10 phraseField2~1^5
    [sort] => score desc,manufacturedate_dt desc
    [version] => 2.2
    [wt] => xml
)
--TEST--
Solr Bug #72740 - addPhraseField return wrong query
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

// Scenario 1: DisMax Query Parser - Adds Phrase Fields with both boost and slop.
// Expect:
// - pf parameter should list each phrase field with ~ and ^ prefix for slop and boost value respectively.
$queryResponse = $client->query( $dismaxQuery );

print_r($queryResponse->getResponse()->responseHeader->params);

// Scenario 2: Same as Scenario 1, now including explicit query fields too.
// Expect:
// - pf parameter should list each phrase field with ~ and ^ prefix for slop and boost value respectively.
// - qf parameter should list each query field with a trailing ^ (no boost here).
$dismaxQuery->addQueryField('score');
$dismaxQuery->addQueryField('manufacturedate_dt');

$queryResponse = $client->query( $dismaxQuery );

print_r($queryResponse->getResponse()->responseHeader->params);

// Scenario 3: Same as Scenario 2, now including explicit boost value for the query fields.
// Expect:
// - pf parameter should list each phrase field with ~ and ^ prefix for slop and boost value respectively.
// - qf parameter should list each query field with a ^ prefix for boost value.
$dismaxQuery->removeQueryField('score');
$dismaxQuery->removeQueryField('manufacturedate_dt');
$dismaxQuery->addQueryField('score', 3);
$dismaxQuery->addQueryField('manufacturedate_dt', 7);

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
SolrObject Object
(
    [q] => *:*
    [defType] => edismax
    [indent] => on
    [qf] => score^ manufacturedate_dt^
    [pf] => phraseField1~5^10 phraseField2~1^5
    [sort] => score desc,manufacturedate_dt desc
    [version] => 2.2
    [wt] => xml
)
SolrObject Object
(
    [q] => *:*
    [defType] => edismax
    [indent] => on
    [qf] => score^3 manufacturedate_dt^7
    [pf] => phraseField1~5^10 phraseField2~1^5
    [sort] => score desc,manufacturedate_dt desc
    [version] => 2.2
    [wt] => xml
)
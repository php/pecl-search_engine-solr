--TEST--
Solr bug #66774 - SolrQuery::setFacetDateGap() Does not urlencode the date math string
--EXTENSIONS--
libxml
curl
--SKIPIF--
<?php require_once 'skip.if.server_not_configured.inc'; ?>
--FILE--
<?php

$query = new SolrQuery();
$query->setFacetDateGap('+1YEAR');
echo $query;
?>
--EXPECTF--
facet.date.gap=%2B1YEAR
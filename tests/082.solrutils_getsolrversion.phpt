--TEST--
SolrUtils::getSolrVersion() - Returns solr dotted version
--FILE--
<?php

$version = SolrUtils::getSolrVersion();
echo $version . PHP_EOL;

echo solr_get_version() . PHP_EOL;
?>
--EXPECTF--
%d.%d.%d
%d.%d.%d
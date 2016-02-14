--TEST--
SolrUtils::getSolrVersion() - Returns solr dotted version
--FILE--
<?php

$version = SolrUtils::getSolrVersion();
echo $version;
?>
--EXPECTF--
%d.%d.%d
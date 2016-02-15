--TEST--
SolrUtils::queryPhrase() - Escapes a query phrase
--FILE--
<?php

echo SolrUtils::queryPhrase('Book Title: Apache Solr Server') . PHP_EOL;

?>
--EXPECT--
"Book Title\: Apache Solr Server"

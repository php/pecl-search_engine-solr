--TEST--
SolrInputDocument - serialize/unserialize Exception
--FILE--
<?php

require_once "bootstrap.inc";

$doc = new SolrInputDocument();

try {
serialize($doc);
} catch (Exception $e) {
echo $e->getMessage().PHP_EOL;
}
?>
--EXPECT--
SolrInputDocument objects cannot be serialized or unserialized
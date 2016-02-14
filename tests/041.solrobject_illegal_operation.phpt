--TEST--
SolrObject - checking illegal operation of modifying object
--FILE--
<?php

$solrObject = new SolrObject();

try
{
   @$solrObject->email = "iekpo@php.net";
} catch (Exception $e) {
    var_dump($e->getCode());
    var_dump($e->getMessage());
}

try {
	$solrObject['usingOffset'] = 'test';
} catch (SolrIllegalOperationException $e) {
	echo sprintf("Exception %d: %s", $e->getCode(), $e->getMessage()) . PHP_EOL;
}

try {
	$solrObject['newprop2_dimension_access'] = 'test';
} catch (SolrIllegalOperationException $e) {
	echo sprintf("Exception %d: %s", $e->getCode(), $e->getMessage()) . PHP_EOL;
}

// unset
try {
	unset($solrObject->responseHeader);
} catch (SolrIllegalOperationException $e) {
	echo sprintf("Exception %d: %s", $e->getCode(), $e->getMessage()) . PHP_EOL;
}

try {
	unset($solrObject['responseHeader']);
} catch (SolrIllegalOperationException $e) {
	echo sprintf("Exception %d: %s", $e->getCode(), $e->getMessage()) . PHP_EOL;
}

?>
--EXPECTF--
int(1006)
string(83) "SolrObject instances are read-only. Properties cannot be added, updated or removed."

Warning: main(): Attempting to set value for [usingOffset] property in a SolrObject instance in %s on line %d
Exception 1006: SolrObject instances are read-only. Properties cannot be added, updated or removed.

Warning: main(): Attempting to set value for [newprop2_dimension_access] property in a SolrObject instance in %s on line %d
Exception 1006: SolrObject instances are read-only. Properties cannot be added, updated or removed.

Warning: main(): Attempting to remove [responseHeader] property in a SolrObject instance in %s on line %d
Exception 1006: SolrObject instances are read-only. Properties cannot be added, updated or removed.

Warning: main(): Attempting to remove [responseHeader] property in a SolrObject instance in %s on line %d
Exception 1006: SolrObject instances are read-only. Properties cannot be added, updated or removed.
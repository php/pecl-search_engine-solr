--TEST--
SolrQuery - Invalid Parameters thorws exception Throws exception on illegal Argument
--FILE--
<?php

$query = new SolrQuery();
$params = new SolrModifiableParams();

try {
	// normal parameter
	$query->setQuery('');
}catch (SolrIllegalArgumentException $e)
{
	echo $e.PHP_EOL;
	try {
		// simple list
		$query->addField('');
	} catch (SolrIllegalArgumentException $e) {
		echo $e.PHP_EOL;
		try {
			// argument list
			$query->addSortField('');
		} catch (SolrIllegalArgumentException $e) {
			echo $e.PHP_EOL;
			try {
				$params->addParam('',1);
			} catch (Exception $e) {
				echo $e.PHP_EOL;
			}
// 			try {
// 				$query->addSortField('price',55);
// 			} catch (SolrIllegalArgumentException $e) {
// 				echo $e.PHP_EOL;
// 			}
		}
	}
}
?>
--EXPECTF--
exception 'SolrIllegalArgumentException' with message 'Invalid parameter value' in %s:%d
Stack trace:
#0 %s(%d): SolrQuery->setQuery('')
#1 {main}
exception 'SolrIllegalArgumentException' with message 'Invalid parameter value' in %s:%d
Stack trace:
#0 %s(%d): SolrQuery->addField('')
#1 {main}
exception 'SolrIllegalArgumentException' with message 'Invalid parameter value' in %s:%d
Stack trace:
#0 %s(%d): SolrQuery->addSortField('')
#1 {main}
exception 'SolrIllegalArgumentException' with message 'Invalid parameter name' in %s:%d
Stack trace:
#0 %s(%d): SolrParams->addParam('', '1')
#1 {main}

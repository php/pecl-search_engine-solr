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
	echo $e->getMessage().PHP_EOL;
	try {
		// simple list
		$query->addField('');
	} catch (SolrIllegalArgumentException $e) {
		echo $e->getMessage().PHP_EOL;
		try {
			// argument list
			$query->addSortField('');
		} catch (SolrIllegalArgumentException $e) {
			echo $e->getMessage().PHP_EOL;
			try {
				$params->addParam('',1);
			} catch (Exception $e) {
				echo $e->getMessage().PHP_EOL;
			}
		}
	}
}
?>
--EXPECT--
Invalid parameter value
Invalid parameter value
Invalid parameter value
Invalid parameter name

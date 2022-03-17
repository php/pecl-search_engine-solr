--TEST--
Solr bug #61836 - Extending SolrDocument
--SKIPIF--
<?php require_once 'skip.if.server_not_configured.inc'; ?>
--FILE--
<?php
class Model_SolrDocument extends SolrDocument
{
	public function addField($fieldName, $fieldValue,$boost=0)
	{
		if (is_bool($fieldValue))
			$fieldValue = ($fieldValue ? '1' : '0');
		return parent::addField($fieldName, $fieldValue);
	}
}

$doc = new Model_SolrDocument();
//$doc->addField('testname', true);
?>
--EXPECTF--
Fatal error: Class Model_SolrDocument %s final class %s

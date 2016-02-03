--TEST--
SolrDocument::getInputDocument() - Where document has child docs
--FILE--
<?php

require_once "bootstrap.inc";

$fixtureXml = file_get_contents(EXAMPLE_RESPONSE_XML_2);

$response = SolrUtils::digestXmlResponse($fixtureXml, SolrResponse::PARSE_SOLR_DOC);

foreach($response->response->docs as $doc)
{
	$childrenOfTheInput = $doc->getInputDocument()->getChildDocuments();
	
	if ($childrenOfTheInput)
	{
		$firstChild = $childrenOfTheInput[0];
		var_dump(get_class($firstChild));
		var_dump(current($childrenOfTheInput)->toArray());
	}
}

?>
--EXPECT--
string(17) "SolrInputDocument"
array(3) {
  ["document_boost"]=>
  float(0)
  ["field_count"]=>
  int(1)
  ["fields"]=>
  array(1) {
    [0]=>
    object(SolrDocumentField)#9 (3) {
      ["name"]=>
      string(2) "id"
      ["boost"]=>
      float(0)
      ["values"]=>
      array(1) {
        [0]=>
        string(9) "CHILD_1_1"
      }
    }
  }
}
string(17) "SolrInputDocument"
array(3) {
  ["document_boost"]=>
  float(0)
  ["field_count"]=>
  int(1)
  ["fields"]=>
  array(1) {
    [0]=>
    object(SolrDocumentField)#10 (3) {
      ["name"]=>
      string(2) "id"
      ["boost"]=>
      float(0)
      ["values"]=>
      array(1) {
        [0]=>
        string(9) "CHILD_2_1"
      }
    }
  }
}

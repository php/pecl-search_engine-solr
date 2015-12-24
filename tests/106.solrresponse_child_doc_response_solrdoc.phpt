--TEST--
SolrDocument - Response parsed as SolrDocument with child documents
--FILE--
<?php

require_once "bootstrap.inc";

$fixtureXml = file_get_contents(EXAMPLE_RESPONSE_XML_2);

$response = SolrUtils::digestXmlResponse($fixtureXml, SolrResponse::PARSE_SOLR_DOC);

foreach($response->response->docs as $doc)
{
	echo '--- doc start ---'.PHP_EOL;
	print_r($doc->toArray());
	if ($doc->hasChildDocuments())
	{
		foreach ($doc->getChildDocuments() as $child)
		{
			print_r($child->toArray());
		}	
	}
	echo '--- doc end ---'.PHP_EOL;
}
?>
--EXPECT--
--- doc start ---
Array
(
    [document_boost] => 0
    [field_count] => 1
    [fields] => Array
        (
            [0] => SolrDocumentField Object
                (
                    [name] => id
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => parent_1
                        )

                )

        )

)
Array
(
    [document_boost] => 0
    [field_count] => 1
    [fields] => Array
        (
            [0] => SolrDocumentField Object
                (
                    [name] => id
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => CHILD_1_1
                        )

                )

        )

)
--- doc end ---
--- doc start ---
Array
(
    [document_boost] => 0
    [field_count] => 1
    [fields] => Array
        (
            [0] => SolrDocumentField Object
                (
                    [name] => id
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => parent_2
                        )

                )

        )

)
Array
(
    [document_boost] => 0
    [field_count] => 1
    [fields] => Array
        (
            [0] => SolrDocumentField Object
                (
                    [name] => id
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => CHILD_2_1
                        )

                )

        )

)
Array
(
    [document_boost] => 0
    [field_count] => 1
    [fields] => Array
        (
            [0] => SolrDocumentField Object
                (
                    [name] => id
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => CHILD_2_2
                        )

                )

        )

)
--- doc end ---
--- doc start ---
Array
(
    [document_boost] => 0
    [field_count] => 1
    [fields] => Array
        (
            [0] => SolrDocumentField Object
                (
                    [name] => id
                    [boost] => 0
                    [values] => Array
                        (
                            [0] => not_a_parent_1
                        )

                )

        )

)
--- doc end ---

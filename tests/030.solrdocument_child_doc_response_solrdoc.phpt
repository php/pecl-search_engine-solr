--TEST--
SolrUtils::digestXmlResponse() - Response with child documents
--FILE--
<?php

require_once "bootstrap.inc";

$fixtureXml = file_get_contents(EXAMPLE_RESPONSE_XML_2);

$response = SolrUtils::digestXmlResponse($fixtureXml, SolrResponse::PARSE_SOLR_DOC);
print_r($response);
foreach($response->response->docs as $doc)
{
	print_r($doc->toArray());
	echo "children".PHP_EOL;
	print_r($doc->getChildDocuments());
}
?>
--EXPECT--
SolrDocument Object
(
    [response] => SolrDocument Object
        (
            [numFound] => 3
            [start] => 0
            [docs] => Array
                (
                    [0] => SolrDocument Object
                        (
                            [id] => parent_1
                            [_childDocuments_] => Array
                                (
                                    [0] => SolrDocument Object
                                        (
                                            [id] => CHILD_1_1
                                        )

                                )

                        )

                    [1] => SolrDocument Object
                        (
                            [id] => parent_2
                            [_childDocuments_] => Array
                                (
                                    [0] => SolrDocument Object
                                        (
                                            [id] => CHILD_2_1
                                        )

                                    [1] => SolrDocument Object
                                        (
                                            [id] => CHILD_2_2
                                        )

                                )

                        )

                    [2] => SolrDocument Object
                        (
                            [id] => not_a_parent_1
                        )

                )

        )

)

--TEST--
Response - Response with child documents
--FILE--
<?php

require_once "bootstrap.inc";

$fixtureXml = file_get_contents(EXAMPLE_RESPONSE_XML_2);

$response = SolrUtils::digestXmlResponse($fixtureXml);
print_r($response);
?>
--EXPECT--
SolrObject Object
(
    [response] => SolrObject Object
        (
            [numFound] => 3
            [start] => 0
            [docs] => Array
                (
                    [0] => SolrObject Object
                        (
                            [id] => parent_1
                            [_childDocuments_] => Array
                                (
                                    [0] => SolrObject Object
                                        (
                                            [id] => CHILD_1_1
                                        )

                                )

                        )

                    [1] => SolrObject Object
                        (
                            [id] => parent_2
                            [_childDocuments_] => Array
                                (
                                    [0] => SolrObject Object
                                        (
                                            [id] => CHILD_2_1
                                        )

                                    [1] => SolrObject Object
                                        (
                                            [id] => CHILD_2_2
                                        )

                                )

                        )

                    [2] => SolrObject Object
                        (
                            [id] => not_a_parent_1
                        )

                )

        )

)

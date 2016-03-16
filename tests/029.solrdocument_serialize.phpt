--TEST--
SolrDocument - clone
--FILE--
<?php

require_once "bootstrap.inc";

$fixtureXml = file_get_contents(EXAMPLE_RESPONSE_XML_2);

$response = SolrUtils::digestXmlResponse($fixtureXml, SolrResponse::PARSE_SOLR_DOC);

$doc =$response->response->docs[1];

$serializedString = serialize($doc);
print_r($serializedString);
echo PHP_EOL;
print_r(unserialize($serializedString)->toArray());
?>
--EXPECT--
C:12:"SolrDocument":172:{<?xml version="1.0" encoding="UTF-8"?>
<solr_document>
  <fields>
    <field name="id">
      <field_value>parent_2</field_value>
    </field>
  </fields>
</solr_document>
}
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
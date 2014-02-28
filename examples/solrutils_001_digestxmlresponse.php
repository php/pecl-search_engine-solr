<?php

include "bootstrap.php";

$response = file_get_contents(DOCUMENT_RESPONSE_XML_2);

$object = SolrUtils::digestXmlResponse($response);

$dotted_property = $object["dotted.property"];

print_r($dotted_property);





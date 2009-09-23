<?php

include "bootstrap.php";

$xml_reponse = file_get_contents(EXAMPLE_RESPONSE_XML_1);

$solrObject = SolrUtils::digestXMLResponse($xml_reponse);

$header = ($solrObject->responseHeader);

$system = $solrObject->system;

print_r($header);

print_r($system);

?>
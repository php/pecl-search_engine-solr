<?php

$extractParams = new SolrModifiableParams();
$extractParams
//  index the document, using the unique ID: doc1
    ->set(SolrExtractRequest::LITERALS_PREFIX . 'id', 'doc1')

// capture what is inside paragraph tags
    ->set(SolrExtractRequest::CAPTURE_ELEMENTS, 'p')

// Indexes attributes of the Tika XHTML elements into separate fields
    ->set(SolrExtractRequest::CAPTURE_ATTRIBUTES, 'true')

// map p content to solr field
    ->set(
        SolrExtractRequest::FIELD_MAPPING_PREFIX . 'p',
        'an_indexed_field_name_that_holds_paragraphs'
        )

// capture unmapped content here
    ->set(SolrExtractRequest::DEFAULT_FIELD, '__text__')

// restrict capturing to matching xpath expression
->set(
    SolrExtractRequest::XPATH_EXPRESSION, 
    '/xhtml:html/xhtml:body/xhtml:div//node()'
    )
;

$binContent = file_get_contents('somefile.pdf');
// please reference docs/documentation.php for the rest of the parameters

$extractRequest = SolrExtractRequest::createFromStream($binContent, 'application/pdf', $extractParams);
$response = $client->sendUpdateStream($extractRequest);


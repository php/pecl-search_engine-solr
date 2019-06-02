<?php 

$doc = new SolrInputDocument();
$doc->addField('id', 'my_long_doc_id');
$doc->updateField('field1', SolrInputDocument::UPDATE_MODIFIER_ADD, 'newly added value');
$doc->updateField('field1', SolrInputDocument::UPDATE_MODIFIER_REMOVE, 'remove me please');
$doc->updateField('field3_i', SolrInputDocument::UPDATE_MODIFIER_INC, 5);
$doc->updateField('field2_s', SolrInputDocument::UPDATE_MODIFIER_SET, 'updated string');
$doc->updateField('field1', SolrInputDocument::UPDATE_MODIFIER_REMOVEREGEX, '[\d]{2}/[\d]{2}/[\d]{4}');



$response = $client->addDocument($doc);
$client->commit();
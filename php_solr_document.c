/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2009 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Israel Ekpo <iekpo@php.net>                                  |
   +----------------------------------------------------------------------+
*/

/* $Id: php_solr_document.c 320130 2011-11-28 20:44:55Z pierrick $ */

#include "php_solr.h"

/** ************************************************************************ **/
/** DEFINITIONS FOR SOLR DOCUMENT METHODS                                    **/
/** ************************************************************************ **/

/* {{{ static int solr_document_set_field(zval *objptr, solr_char_t *field_name, int field_name_length, solr_char_t *field_value, int field_value_length TSRMLS_DC) */
static int solr_document_set_field(zval *objptr, solr_char_t *field_name, int field_name_length, solr_char_t *field_value, int field_value_length TSRMLS_DC)
{
	double field_boost = 0.0f;

	solr_document_t *doc_entry = NULL;

	if (!field_name_length) {

		return FAILURE;
	}

	if (!field_value_length)
	{
		return FAILURE;
	}

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(objptr, &doc_entry TSRMLS_CC) == SUCCESS)
	{
		solr_field_list_t **field_values_ptr = NULL;
		solr_field_list_t *field_values      = NULL;

		/* If the field already exists in the SolrDocument instance append the value to the field list queue */
		if (zend_hash_find(doc_entry->fields, field_name, field_name_length, (void **) &field_values_ptr) == SUCCESS) {

			if (solr_document_insert_field_value(*field_values_ptr, field_value, field_boost) == FAILURE) {

				return FAILURE;
			}

		} else {

			/* Otherwise, create a new one and add it to the hash table */
			field_values = (solr_field_list_t *)  pemalloc(sizeof(solr_field_list_t), SOLR_DOCUMENT_FIELD_PERSISTENT);

			memset(field_values, 0, sizeof(solr_field_list_t));

			field_values_ptr = &field_values;

			field_values->count       = 0L;
			field_values->field_boost = 0.0;
			field_values->field_name  = (solr_char_t *) pestrdup(field_name,SOLR_DOCUMENT_FIELD_PERSISTENT);
			field_values->head        = NULL;
			field_values->last        = NULL;

			if (solr_document_insert_field_value(field_values, field_value, field_boost) == FAILURE) {

				solr_destroy_field_list(&field_values);

				return FAILURE;
			}

			if (zend_hash_add(doc_entry->fields, field_name, field_name_length, (void *) field_values_ptr, sizeof(solr_field_list_t *), (void **) NULL) == FAILURE) {

				solr_destroy_field_list(&field_values);

				return FAILURE;
			}

			/* Increment field count only when HEAD is added */
			doc_entry->field_count++;
		}

		return SUCCESS;
	}

	return FAILURE;
}
/* }}} */

/* {{{ static int solr_document_get_field(zval *objptr, zval *return_value, solr_char_t *field_name, int field_name_length TSRMLS_DC) */
static int solr_document_get_field(zval *objptr, zval *return_value, solr_char_t *field_name, int field_name_length TSRMLS_DC)
{
	solr_document_t *doc_entry = NULL;

	if (!field_name_length) {

		return FAILURE;
	}

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(objptr, &doc_entry TSRMLS_CC) == SUCCESS)
	{
		solr_field_list_t **field_values = NULL;

		if (zend_hash_find(doc_entry->fields, (char *)field_name, field_name_length, (void **) &field_values) == SUCCESS)
		{
			solr_create_document_field_object(*field_values, &return_value TSRMLS_CC);

			/* The field was retrieved, so we're done here */
			return SUCCESS;
		}

		return FAILURE;
	}

	return FAILURE;
}
/* }}} */

/* {{{ static int solr_document_remove_field(zval *objptr, solr_char_t *field_name, int field_name_length TSRMLS_DC) */
static int solr_document_remove_field(zval *objptr, solr_char_t *field_name, int field_name_length TSRMLS_DC)
{
	solr_document_t *doc_entry = NULL;

	if (!field_name_length) {

		return FAILURE;
	}

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(objptr, &doc_entry TSRMLS_CC) == SUCCESS) {

		if (zend_hash_del(doc_entry->fields, field_name, field_name_length) == SUCCESS) {

			doc_entry->field_count--;

			return SUCCESS;
		}

		return FAILURE;
	}

	return FAILURE;
}
/* }}} */

/* {{{ static int solr_document_field_exists(zval *objptr, solr_char_t *field_name, int field_name_length TSRMLS_DC) */
static int solr_document_field_exists(zval *objptr, solr_char_t *field_name, int field_name_length TSRMLS_DC)
{
	solr_document_t *doc_entry = NULL;

	if (!field_name_length) {

		return FAILURE;
	}

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(objptr, &doc_entry TSRMLS_CC) == SUCCESS) {

		if (zend_hash_exists(doc_entry->fields, field_name, field_name_length)) {

			return SUCCESS;

		} else {

			return FAILURE;
		}
	}

	return FAILURE;
}
/* }}} */

/* {{{ static void solr_serialize_document_object(HashTable *document_fields, xmlChar **buffer, int *size TSRMLS_DC) */
static void solr_serialize_document_object(HashTable *document_fields, xmlChar **buffer, int *size TSRMLS_DC)
{
	xmlNode *root_node = NULL, *fields_node = NULL;
	xmlDoc *doc_ptr = NULL;
	int format = 1;

	if(!buffer)
	{
		return;
	}

	doc_ptr = solr_xml_create_xml_doc((xmlChar *) "solr_document", &root_node);
	fields_node = xmlNewChild(root_node, NULL, (xmlChar *) "fields", NULL);

	SOLR_HASHTABLE_FOR_LOOP(document_fields)
	{
		solr_field_list_t **field = NULL;
		solr_char_t *doc_field_name = NULL;
		solr_field_value_t *doc_field_value = NULL;
		xmlNode *field_node = NULL;

		zend_hash_get_current_data_ex(document_fields, (void **) &field, ((HashPosition *)0));

		doc_field_name = (*field)->field_name;
		doc_field_value = (*field)->head;

		field_node = xmlNewChild(fields_node, NULL, (xmlChar *) "field", NULL);

		xmlNewProp(field_node, (xmlChar *) "name", (xmlChar *) doc_field_name);

		/* Loop through all the values for this field */
		while(doc_field_value != NULL)
		{
			xmlChar *escaped_field_value = xmlEncodeEntitiesReentrant(doc_ptr, (xmlChar *) doc_field_value->field_value);

			xmlNewChild(field_node, NULL, (xmlChar *) "field_value", escaped_field_value);

			/* Release the memory allocated by xmlEncodeEntitiesReentrant */
			xmlFree(escaped_field_value);

			/* Grab the next value for this field if any */
			doc_field_value = doc_field_value->next;

		} /* while(doc_field_value != NULL) */

	} /* SOLR_HASHTABLE_FOR_LOOP(document_fields) */

	xmlIndentTreeOutput = 1;

	xmlDocDumpFormatMemoryEnc(doc_ptr, buffer, size, "UTF-8", format);

	xmlFreeDoc(doc_ptr);
}
/* }}} */

/* {{{ static void solr_unserialize_document_field(HashTable *document_fields, xmlNode *field_node TSRMLS_DC) */
static void solr_unserialize_document_field(HashTable *document_fields, xmlNode *field_node TSRMLS_DC)
{
	solr_char_t *field_name = NULL;
	xmlNode *xml_curr_value = NULL;
	solr_field_list_t *field_values = (solr_field_list_t *) pemalloc(sizeof(solr_field_list_t), SOLR_DOCUMENT_FIELD_PERSISTENT);

	memset(field_values, 0, sizeof(solr_field_list_t));

	field_name = (solr_char_t *) solr_xml_get_node_contents(field_node->properties);

	field_values->count       = 0L;
	field_values->field_boost = 0.0f;
	field_values->field_name  = (solr_char_t *) pestrdup(field_name, SOLR_DOCUMENT_FIELD_PERSISTENT);
	field_values->head        = NULL;
	field_values->last        = NULL;

	/* Grab the first field node */
	xml_curr_value = field_node->children;

	/* Looping through all the field_value nodes */
	while(xml_curr_value != NULL)
	{
		/* No assumptions. It must be the field value nodes */
		if (xml_curr_value->type == XML_ELEMENT_NODE && solr_xml_match_node(xml_curr_value, "field_value"))
		{
			solr_char_t *field_value = (solr_char_t *) solr_xml_get_node_contents(xml_curr_value);

			/* Add this value to the list of values */
			if (solr_document_insert_field_value(field_values, field_value, 0.0f) == FAILURE) {

				php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error adding field value during SolrDocument unserialization");
			}
		}

		/* Move to the next field_value */
		xml_curr_value = xml_curr_value->next;
	}

	/* All the values have been retrieved for this field. Now let's drop the field in the HashTable */
	if (zend_hash_add(document_fields, field_name, strlen(field_name), (void *) &field_values, sizeof(solr_field_list_t *), (void **) NULL) == FAILURE) {

		solr_destroy_field_list(&field_values);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error adding field values to HashTable during SolrDocument unserialization");

		return;
	}
}
/* }}} */

/* {{{ static int solr_unserialize_document_object(HashTable *document_fields, char *serialized, int size TSRMLS_DC) */
static int solr_unserialize_document_object(HashTable *document_fields, char *serialized, int size TSRMLS_DC)
{
	xmlXPathContext *xpathctxt = NULL;

	xmlDoc *doc = NULL;

	xmlChar *xpath_expression = NULL;

	xmlXPathObject *xpathObj = NULL;

	xmlNodeSet *result = NULL;

	register size_t num_nodes = 0U;

	register size_t i = 0U;

	doc = xmlReadMemory(serialized, size, NULL, "UTF-8", 0);

	if (!doc)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "The serialized document string is invalid");

		return FAILURE;
	}

	xpathctxt = xmlXPathNewContext(doc);

	if (!xpathctxt)
	{
		xmlFreeDoc(doc);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "A valid XML xpath context could not be created");

		return FAILURE;
	}

	xpath_expression = (xmlChar *) "/solr_document/fields/field/@name";

	xpathObj = xmlXPathEval(xpath_expression, xpathctxt);

	if (!xpathObj)
	{
		xmlXPathFreeContext(xpathctxt);

		xmlFreeDoc(doc);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "A valid XML xpath object could not be created from the expression");

		return FAILURE;
	}

	result = xpathObj->nodesetval;

	if (!result)
	{
		xmlXPathFreeContext(xpathctxt);

		xmlXPathFreeObject(xpathObj);

		xmlFreeDoc(doc);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Document has no fields");

		return FAILURE;
	}

	num_nodes = result->nodeNr;

	i = 0U;

	if (!num_nodes)
	{
		xmlXPathFreeContext(xpathctxt);

		xmlXPathFreeObject(xpathObj);

		xmlFreeDoc(doc);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Document has no fields");

		return FAILURE;
	}

	for (i = 0U; i < num_nodes; i++)
	{
		xmlNode *currNode = result->nodeTab[i];

		/* Absolutely No assumptions. I have to make sure that this is the name attribute */
		if (currNode->type == XML_ATTRIBUTE_NODE && solr_xml_match_node(currNode, "name"))
		{
			/* Get the field node */
			xmlNode *field_xml_node = currNode->parent;

			/* Retrieve all the values for this field and put them in the HashTable */
			solr_unserialize_document_field(document_fields, field_xml_node TSRMLS_CC);
		}
	}

	xmlXPathFreeContext(xpathctxt);

	xmlXPathFreeObject(xpathObj);

	xmlFreeDoc(doc);

	return SUCCESS;
}
/* }}} */

/* {{{ proto void SolrDocument::__construct(void)
	SolrDocument constructor */
PHP_METHOD(SolrDocument, __construct)
{
	zval *objptr = getThis();
	solr_document_t *doc_entry = NULL, *doc_ptr = NULL;
	solr_document_t solr_doc;
	ulong document_index = SOLR_UNIQUE_DOCUMENT_INDEX();
	uint nSize = SOLR_INITIAL_HASH_TABLE_SIZE;

	memset(&solr_doc, 0, sizeof(solr_document_t));

	doc_entry = &solr_doc;

	doc_entry->document_index  = document_index;
	doc_entry->field_count     = 0L;
	doc_entry->document_boost  = 0.0f;

	/* Allocated memory for the fields HashTable using fast cache for HashTables */
	ALLOC_HASHTABLE(doc_entry->fields);

	/* Initializing the hash table used for storing fields in this SolrDocument */
	zend_hash_init(doc_entry->fields, nSize, NULL, (dtor_func_t) solr_destroy_field_list, SOLR_DOCUMENT_FIELD_PERSISTENT);

	/* Let's check one more time before insert into the HashTable */
	if (zend_hash_index_exists(SOLR_GLOBAL(documents), document_index)) {

		pefree(doc_entry->fields, SOLR_DOCUMENT_FIELD_PERSISTENT);

		return;
	}

	/* Add the document entry to the directory of documents */
	zend_hash_index_update(SOLR_GLOBAL(documents), document_index, (void *) doc_entry, sizeof(solr_document_t), (void **) &doc_ptr);

	/* Set the value of the internal id property */
	zend_update_property_long(solr_ce_SolrDocument, objptr, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, document_index TSRMLS_CC);

	/* Keep track of how many SolrDocument instances we currently have */
	SOLR_GLOBAL(document_count)++;

	/* Overriding the default object handlers */
	Z_OBJ_HT_P(objptr) = &solr_input_document_object_handlers;
}

/* }}} */

/* {{{ proto void SolrDocument::__destruct(void)
	Destructor for SolrDocument */
PHP_METHOD(SolrDocument, __destruct)
{
	solr_document_t *doc_entry = NULL;

	/* Retrieve the document entry for this SolrDocument */
	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS) 	{

		zend_hash_index_del(SOLR_GLOBAL(documents), doc_entry->document_index);

		/* Keep track of how many SolrDocument instances we currently have */
		SOLR_GLOBAL(document_count)--;

		return ;
	}
}
/* }}} */

/* {{{ proto SolrDocument::__clone(void)
   Clone method for SolrDocument */
PHP_METHOD(SolrDocument, __clone)
{
	zval *objptr = getThis();
	solr_document_t new_solr_doc;
	solr_document_t *new_doc_entry = NULL, *old_doc_entry = NULL;
	ulong document_index = SOLR_UNIQUE_DOCUMENT_INDEX();

	memset(&new_solr_doc, 0, sizeof(solr_document_t));

	new_doc_entry = &new_solr_doc;

	/* Retrieve the document entry for the original SolrDocument */
	if (solr_fetch_document_entry(objptr, &old_doc_entry TSRMLS_CC) == FAILURE) {

		return ;
	}

	/* Duplicate the doc_entry contents */
	memcpy(new_doc_entry, old_doc_entry, sizeof(solr_document_t));

	/* Override the document index with a new one and create a new HashTable */
	new_doc_entry->document_index = document_index;

	/* Allocate new memory for the fields HashTable, using fast cache for HashTables */
	ALLOC_HASHTABLE(new_doc_entry->fields);

	/* Initializing the hash table used for storing fields in this SolrDocument */
	zend_hash_init(new_doc_entry->fields, old_doc_entry->fields->nTableSize, NULL, (dtor_func_t) solr_destroy_field_list, SOLR_DOCUMENT_FIELD_PERSISTENT);

	/* Copy the contents of the old fields HashTable to the new SolrDocument */
	zend_hash_copy(new_doc_entry->fields, old_doc_entry->fields, (copy_ctor_func_t) field_copy_constructor, NULL, sizeof(solr_field_list_t *));

	/* Add the document entry to the directory of documents */
	zend_hash_index_update(SOLR_GLOBAL(documents), document_index, (void *) new_doc_entry, sizeof(solr_document_t), NULL);

	/* Set the value of the internal id property */
	zend_update_property_long(solr_ce_SolrDocument, objptr, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, document_index TSRMLS_CC);

	/* Keep track of how many SolrDocument instances we currently have */
	SOLR_GLOBAL(document_count)++;
}
/* }}} */

/* {{{ proto SolrDocument::__set(string fieldname, string field_value)
   Magic method for setting field names. */
PHP_METHOD(SolrDocument, __set)
{
	solr_char_t *field_name = NULL;
	int field_name_length  = 0;

	solr_char_t *field_value = NULL;
	int field_value_length = 0;

	/* Process the parameters passed to the method */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &field_name,
			&field_name_length, &field_value,
			&field_value_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (solr_document_set_field(getThis(), field_name, field_name_length, field_value, field_value_length TSRMLS_CC) == SUCCESS)
	{
		RETURN_TRUE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto SolrDocumentField SolrDocument::__get(string fieldname)
   Magic method for getting a field. */
PHP_METHOD(SolrDocument, __get)
{
	solr_char_t *field_name = NULL;
	int field_name_length   = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &field_name, &field_name_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (solr_document_get_field(getThis(), return_value, field_name, field_name_length TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}
}
/* }}} */

/* {{{ proto bool SolrDocument::__isset(string field_name)
   Checks if a field exists */
PHP_METHOD(SolrDocument, __isset)
{
	solr_char_t *field_name = NULL;
	int field_name_length  = 0;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &field_name, &field_name_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (solr_document_field_exists(getThis(), field_name, field_name_length TSRMLS_CC) == SUCCESS)
	{
		RETURN_TRUE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool SolrDocument::__unset(string fieldname)
   Removes a field from the document. */
PHP_METHOD(SolrDocument, __unset)
{
	solr_char_t *field_name = NULL;
	int field_name_length  = 0;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &field_name, &field_name_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (solr_document_remove_field(getThis(), field_name, field_name_length TSRMLS_CC) == SUCCESS)
	{
		RETURN_TRUE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto void SolrDocument::offsetSet(string field_name, string field_value)
    Sets the specified field in the document */
PHP_METHOD(SolrDocument, offsetSet)
{
	solr_char_t *field_name = NULL;
	int field_name_length  = 0;

	solr_char_t *field_value = NULL;
	int field_value_length = 0;

	/* Process the parameters passed to the method */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &field_name,
			&field_name_length, &field_value,
			&field_value_length) == FAILURE) {

		return;
	}

	if (solr_document_set_field(getThis(), field_name, field_name_length, field_value, field_value_length TSRMLS_CC) == SUCCESS)
	{
		return;
	}
}
/* }}} */

/* {{{ proto SolrDocumentField SolrDocument::offsetGet(string field_name)
   Returns the request field. */
PHP_METHOD(SolrDocument, offsetGet)
{
	solr_char_t *field_name = NULL;
	int field_name_length   = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &field_name, &field_name_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (solr_document_get_field(getThis(), return_value, field_name, field_name_length TSRMLS_CC) == FAILURE) {

		RETURN_NULL();
	}
}
/* }}} */

/* {{{ proto bool SolrDocument::offsetExists(string fieldname)
   Checks if the request field exists in the document */
PHP_METHOD(SolrDocument, offsetExists)
{
	solr_char_t *field_name = NULL;
	int field_name_length  = 0;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &field_name, &field_name_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (solr_document_field_exists(getThis(), field_name, field_name_length TSRMLS_CC) == SUCCESS)
	{
		RETURN_TRUE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto void SolrDocument::offsetUnset(string fieldname)
   Removes the specified field from the document */
PHP_METHOD(SolrDocument, offsetUnset)
{
	solr_char_t *field_name = NULL;
	int field_name_length  = 0;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &field_name, &field_name_length) == FAILURE) {

		return;
	}

	if (solr_document_remove_field(getThis(), field_name, field_name_length TSRMLS_CC) == SUCCESS)
	{
		return;
	}
}
/* }}} */

/* {{{ proto void SolrDocument::rewind(void)
   Resets the internal pointer. */
PHP_METHOD(SolrDocument, rewind)
{
	solr_document_t *doc_entry = NULL;
	HashTable *doc_fields = NULL;

	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == FAILURE) 	{

		return;
	}

	doc_fields = doc_entry->fields;

	zend_hash_internal_pointer_reset(doc_fields);
}
/* }}} */

/* {{{ proto SolrDocumentField SolrDocument::current(void)
   Retrieves the current field. */
PHP_METHOD(SolrDocument, current)
{
	solr_document_t *doc_entry = NULL;
	HashTable *doc_fields = NULL;
	solr_field_list_t **field_values = NULL;

	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == FAILURE) 	{

		return;
	}

	doc_fields = doc_entry->fields;

	zend_hash_get_current_data_ex(doc_fields, (void **) &field_values, NULL);

	if(field_values && *field_values ) {

		solr_create_document_field_object(*field_values, &return_value TSRMLS_CC);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto string SolrDocument::key(void)
   Retrieves the current key. */
PHP_METHOD(SolrDocument, key)
{
	solr_document_t *doc_entry = NULL;
	char *fieldname = NULL;
	uint fieldname_length = 0U;
	ulong num_index = 0L;
	HashTable *doc_fields = NULL;
	register zend_bool duplicate = 0;

	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == FAILURE) 	{

		return;
	}

	doc_fields = doc_entry->fields;

	zend_hash_get_current_key_ex(doc_fields, &fieldname, &fieldname_length, &num_index, duplicate, NULL);

	RETURN_STRINGL(fieldname, fieldname_length, 1);
}
/* }}} */

/* {{{ proto void SolrDocument::next(void)
  Moves the internal pointer to the next field. */
PHP_METHOD(SolrDocument, next)
{
	solr_document_t *doc_entry = NULL;
	HashTable *doc_fields = NULL;

	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == FAILURE) 	{

		return;
	}

	doc_fields = doc_entry->fields;

	zend_hash_move_forward(doc_fields);
}
/* }}} */

/* {{{ proto bool SolrDocument::valid(void)
  Checks if the current internal pointer position is still valid. */
PHP_METHOD(SolrDocument, valid)
{
	solr_document_t *doc_entry = NULL;
	HashTable *doc_fields = NULL;
	zend_bool is_valid = 0;

	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == FAILURE) 	{

		return;
	}

	doc_fields = doc_entry->fields;
	is_valid = (zend_bool) ( SUCCESS == zend_hash_has_more_elements(doc_fields) );

	RETURN_BOOL(is_valid);
}
/* }}} */

/* {{{ proto string SolrDocument::serialize(void)
   Custom SolrDocument serializer. Returns an XML document string representing the object. */
PHP_METHOD(SolrDocument, serialize)
{
	solr_document_t *doc_entry = NULL;
	HashTable *doc_fields = NULL;
	char *serialized = NULL;
	int size = 0;

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == FAILURE)
	{
		RETURN_NULL();
	}

	doc_fields = doc_entry->fields;

	solr_serialize_document_object(doc_fields, (xmlChar **) &serialized, &size TSRMLS_CC);

	if (size)
	{
		RETVAL_STRINGL(serialized, size, 1);

		xmlFree(serialized);

		return;
	}

	RETURN_NULL();
}
/* }}} */

/* {{{ proto void SolrDocument::unserialize(string serialized_xml)
   Custom SolrDocument unserializer. Brings the object back to life. */
PHP_METHOD(SolrDocument, unserialize)
{
	solr_char_t *serialized = NULL;
	int serialized_length  = 0;
	zval *objptr = getThis();
	ulong document_index = SOLR_UNIQUE_DOCUMENT_INDEX();
	uint nSize = SOLR_INITIAL_HASH_TABLE_SIZE;
	solr_document_t solr_doc;
	solr_document_t *doc_entry = NULL, *doc_ptr = NULL;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &serialized, &serialized_length) == FAILURE) {

		RETURN_FALSE;
	}

	memset(&solr_doc, 0, sizeof(solr_document_t));

	doc_entry = &solr_doc;

	doc_entry->document_index  = document_index;
	doc_entry->field_count     = 0L;
	doc_entry->document_boost  = 0;

	/* Allocated memory for the fields HashTable using fast cache for HashTables */
	ALLOC_HASHTABLE(doc_entry->fields);

	/* Initializing the hash table used for storing fields in this SolrDocument */
	zend_hash_init(doc_entry->fields, nSize, NULL, (dtor_func_t) solr_destroy_field_list, SOLR_DOCUMENT_FIELD_PERSISTENT);

	/* Let's check one more time before insert into the HashTable */
	if (zend_hash_index_exists(SOLR_GLOBAL(documents), document_index)) {

		pefree(doc_entry->fields, SOLR_DOCUMENT_FIELD_PERSISTENT);

		return;
	}

	/* Add the document entry to the directory of documents */
	zend_hash_index_update(SOLR_GLOBAL(documents), document_index, (void *) doc_entry, sizeof(solr_document_t), (void **) &doc_ptr);

	/* Set the value of the internal id property */
	zend_update_property_long(solr_ce_SolrDocument, objptr, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, document_index TSRMLS_CC);

	/* Keep track of how many SolrDocument instances we currently have */
	SOLR_GLOBAL(document_count)++;

	/* Overriding the default object handlers */
	Z_OBJ_HT_P(objptr) = &solr_input_document_object_handlers;

	if (solr_unserialize_document_object(doc_ptr->fields, serialized, serialized_length TSRMLS_CC) == FAILURE)
	{
		return;
	}

	doc_ptr->field_count = zend_hash_num_elements(doc_ptr->fields);
}
/* }}} */

/* {{{ proto bool SolrDocument::clear(void)
   Resets the current object. Discards all the fields and resets the document boost to zero. */
PHP_METHOD(SolrDocument, clear)
{
	solr_document_t *doc_entry = NULL;

	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS) 	{

		doc_entry->document_boost = 0.0;
		doc_entry->field_count = 0L;

		zend_hash_clean(doc_entry->fields);

		RETURN_TRUE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool SolrDocument::addField(string fieldname, string value)
   Adds a field to the document */
PHP_METHOD(SolrDocument, addField)
{
	solr_char_t *field_name = NULL;
	int field_name_length  = 0;
	solr_char_t *field_value = NULL;
	int field_value_length = 0;

	/* Process the parameters passed to the method */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &field_name,
			&field_name_length, &field_value,
			&field_value_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (solr_document_set_field(getThis(), field_name, field_name_length, field_value, field_value_length TSRMLS_CC) == SUCCESS)
	{
		RETURN_TRUE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto array SolrDocument::getFieldNames(void)
   Returns an array of fields names in the document. */
PHP_METHOD(SolrDocument, getFieldNames)
{
	solr_document_t *doc_entry = NULL;

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS)
	{
		HashTable *fields_ht = NULL;
		register zend_bool duplicate = 0;

		array_init(return_value);

		fields_ht = doc_entry->fields;

		SOLR_HASHTABLE_FOR_LOOP(fields_ht)
		{
			char *fieldname = NULL;
			uint fieldname_length = 0U;
			ulong num_index = 0L;
			solr_field_list_t **field = NULL;
			zend_bool duplicate_field_name = 1;

			zend_hash_get_current_key_ex(fields_ht, &fieldname, &fieldname_length, &num_index, duplicate, NULL);
			zend_hash_get_current_data_ex(fields_ht, (void **) &field, NULL);

			add_next_index_stringl(return_value, (*field)->field_name, fieldname_length, duplicate_field_name);
		}

		/* We are done */
		return;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto int SolrDocument::getFieldCount(void)
   Returns the number of fields in this document. Multi-value fields are only counted once. */
PHP_METHOD(SolrDocument, getFieldCount)
{
	solr_document_t *doc_entry = NULL;

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS)
	{
		RETURN_LONG(zend_hash_num_elements(doc_entry->fields));
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto SolrDocumentField SolrDocument::getField(string fieldname)
   Retrieves the requested field */
PHP_METHOD(SolrDocument, getField)
{
	solr_char_t *field_name = NULL;
	int field_name_length  = 0;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &field_name, &field_name_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (solr_document_get_field(getThis(), return_value, field_name, field_name_length TSRMLS_CC) == FAILURE) {

		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ proto array SolrDocument::toArray(void)
   Returns an array representation of the SolrDocument object. */
PHP_METHOD(SolrDocument, toArray)
{
	solr_document_t *doc_entry = NULL;

	zval *fields_array = NULL;

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS)
	{
		HashTable *fields_ht;
		register zend_bool duplicate = 0;

		MAKE_STD_ZVAL(fields_array);

		array_init(return_value);
		array_init(fields_array);

		add_assoc_double(return_value, "document_boost", doc_entry->document_boost);
		add_assoc_long(return_value,   "field_count", doc_entry->field_count);
		add_assoc_zval(return_value,   "fields", fields_array);

		fields_ht = doc_entry->fields;

		SOLR_HASHTABLE_FOR_LOOP(fields_ht)
		{
			solr_char_t *fieldname = NULL;
			uint fieldname_length = 0U;
			ulong num_index = 0L;

			solr_field_list_t **field = NULL;
			zval *current_field = NULL;

			MAKE_STD_ZVAL(current_field);

			zend_hash_get_current_key_ex(fields_ht, (char **) &fieldname, &fieldname_length, &num_index, duplicate, NULL);
			zend_hash_get_current_data_ex(fields_ht, (void **) &field, NULL);

			solr_create_document_field_object(*field, &current_field TSRMLS_CC);

			add_next_index_zval(fields_array, current_field);
		}

		/* We are done */
		return;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool SolrDocument::fieldExists(string fieldname)
   Checks if the field exists. */
PHP_METHOD(SolrDocument, fieldExists)
{
	solr_char_t *field_name = NULL;
	int field_name_length = 0;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &field_name, &field_name_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (solr_document_field_exists(getThis(), field_name, field_name_length TSRMLS_CC) == SUCCESS)
	{
		RETURN_TRUE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool SolrDocument::deleteField(string field_name)
   Removes the requested field. */
PHP_METHOD(SolrDocument, deleteField)
{
	solr_char_t *field_name = NULL;
	int field_name_length  = 0;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &field_name, &field_name_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (solr_document_remove_field(getThis(), field_name, field_name_length TSRMLS_CC) == SUCCESS)
	{
		RETURN_TRUE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool SolrDocument::sort(int sort_criterion [, int sort_direction])
   Sorts the fields in the document */
PHP_METHOD(SolrDocument, sort)
{
	long int order_by = 0L;
	long int sort_direction = SOLR_SORT_ASC;
	solr_document_t *doc_entry = NULL;
	int renumber = 0;

	/* The pointer to the comparison function used by zend_qsort */
	compare_func_t comparison_function = (compare_func_t) NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|l", &order_by, &sort_direction) == FAILURE) {

		RETURN_FALSE;
	}

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == FAILURE) {

		RETURN_FALSE;
	}

	/*  {{{ Select the appropriate comparison function */
	switch(order_by)
	{
		case  SOLR_SORT_FIELD_NAME : /* Sorting by field name */
		{
			switch(sort_direction)
			{
				case SOLR_SORT_ASC :
					comparison_function = solr_compare_field_name;
				break;

				case SOLR_SORT_DESC :
					comparison_function = solr_rcompare_field_name;
				break;
			}
		}
		break; /* case  SOLR_SORT_FIELD_NAME */

		case  SOLR_SORT_FIELD_VALUE_COUNT : /* Sorting by number of values per field */
		{
			switch(sort_direction)
			{
				case SOLR_SORT_ASC :
					comparison_function = solr_compare_field_value_count;
				break;

				case SOLR_SORT_DESC :
					comparison_function = solr_rcompare_field_value_count;
				break;
			}
		}
		break; /* case  SOLR_SORT_FIELD_VALUE_COUNT */

		case  SOLR_SORT_FIELD_BOOST_VALUE : /* Sorting by field boost values */
		{
			switch(sort_direction)
			{
				case SOLR_SORT_ASC :
					comparison_function = solr_compare_field_boost_value;
				break;

				case SOLR_SORT_DESC :
					comparison_function = solr_rcompare_field_boost_value;
				break;
			}
		}
		break; /* case  SOLR_SORT_FIELD_BOOST_VALUE */

		default : /* Undefined sort criteria */

			RETURN_FALSE;

		break;

	} /* }}} switch(order_by) */

	/* Undefined sort direction. It was not ASC or DESC */
	if (!comparison_function) {

		RETURN_FALSE;
	}

	if (zend_hash_sort(doc_entry->fields, zend_qsort, comparison_function, renumber TSRMLS_CC) == FAILURE) {

		RETURN_FALSE;
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool SolrDocument::merge(SolrDocument source [, bool override])
   Merges source to the current SolrDocument. */
PHP_METHOD(SolrDocument, merge)
{
	solr_document_t *destination_document = NULL;
	solr_document_t *source_document = NULL;

	copy_ctor_func_t p_copy_ctor = (copy_ctor_func_t) field_copy_constructor;

	/* The destination SolrDocument instance */
	zval *destination_document_zval = getThis();

	/* The source SolrDocument instance */
	zval *source_document_zval = NULL;

	/* Should we skip fields that already exist in destination */
	zend_bool overwrite = (zend_bool) 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O|b", &source_document_zval, solr_ce_SolrDocument, &overwrite) == FAILURE) {

		RETURN_FALSE;
	}

	if (solr_fetch_document_entry(source_document_zval, &source_document TSRMLS_CC) == FAILURE) {

		RETURN_FALSE;
	}

	if (solr_fetch_document_entry(destination_document_zval, &destination_document TSRMLS_CC) == FAILURE) {

		RETURN_FALSE;
	}

	if (zend_hash_num_elements(source_document->fields) == 0)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Source SolrDocument has no fields. Source");

		RETURN_FALSE;
	}

	/* Copy the fields in the source HashTable to the destination HashTable */
	zend_hash_merge(destination_document->fields, source_document->fields, p_copy_ctor, NULL, sizeof(solr_field_list_t *), (int) overwrite);

	/* Update the field count */
	destination_document->field_count = (uint) zend_hash_num_elements(destination_document->fields);

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto SolrInputDocument SolrDocument::getInputDocument(void)
   Returns a SolrInputDocument equivalent of the object. */
PHP_METHOD(SolrDocument, getInputDocument)
{
	zval *objptr = getThis();
	zval *input_objptr = (*return_value_ptr);
	solr_document_t new_solr_doc;
	solr_document_t *new_doc_entry = NULL, *old_doc_entry = NULL;
	ulong document_index = SOLR_UNIQUE_DOCUMENT_INDEX();

	if (!return_value_used)
	{
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "SolrInputDocument object requested without processing output.");

		return;
	}

	memset(&new_solr_doc, 0, sizeof(solr_document_t));

	new_doc_entry = &new_solr_doc;

	/* Retrieve the document entry for the original SolrDocument */
	if (solr_fetch_document_entry(objptr, &old_doc_entry TSRMLS_CC) == FAILURE) {

		php_error_docref(NULL TSRMLS_CC, E_ERROR, "SolrDocument could not be fetched.");

		return;
	}

	object_init_ex(input_objptr, solr_ce_SolrInputDocument);

	/* Duplicate the doc_entry contents */
	memcpy(new_doc_entry, old_doc_entry, sizeof(solr_document_t));

	/* Override the document index with a new one and create a new HashTable */
	new_doc_entry->document_index = document_index;

	/* Allocate new memory for the fields HashTable, using fast cache for HashTables */
	ALLOC_HASHTABLE(new_doc_entry->fields);

	/* Initializing the hash table used for storing fields in this SolrDocument */
	zend_hash_init(new_doc_entry->fields, old_doc_entry->fields->nTableSize, NULL, (dtor_func_t) solr_destroy_field_list, SOLR_DOCUMENT_FIELD_PERSISTENT);

	/* Copy the contents of the old fields HashTable to the new SolrDocument */
	zend_hash_copy(new_doc_entry->fields, old_doc_entry->fields, (copy_ctor_func_t) field_copy_constructor, NULL, sizeof(solr_field_list_t *));

	/* Add the document entry to the directory of documents */
	zend_hash_index_update(SOLR_GLOBAL(documents), document_index, (void *) new_doc_entry, sizeof(solr_document_t), NULL);

	/* Set the value of the internal id property */
	zend_update_property_long(solr_ce_SolrInputDocument, input_objptr, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, document_index TSRMLS_CC);

	/* Keep track of how many SolrDocument instances we currently have */
	SOLR_GLOBAL(document_count)++;
}
/* }}} */

/* {{{ proto SolrDocumentField::__construct(void)
   Constructor */
PHP_METHOD(SolrDocumentField, __construct)
{
	Z_OBJ_HT_P(getThis()) = &solr_document_field_handlers;
}
/* }}} */

/* {{{ proto SolrDocumentField::__destruct(void)
   Destructor */
PHP_METHOD(SolrDocumentField, __destruct)
{

}
/* }}} */

/* {{{ PHP_SOLR_API void solr_document_field_write_property(zval *object, zval *member, zval *value TSRMLS_DC) */
#if PHP_VERSION_ID < 50399
PHP_SOLR_API void solr_document_field_write_property(zval *object, zval *member, zval *value TSRMLS_DC)
#else
PHP_SOLR_API void solr_document_field_write_property(zval *object, zval *member, zval *value, const zend_literal *key TSRMLS_DC)
#endif

{
	solr_throw_exception(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1007_MSG, SOLR_ERROR_1007 TSRMLS_CC, SOLR_FILE_LINE_FUNC);
/*
	if (Z_TYPE_P(member) == IS_STRING)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Attempting to set value for [%s] property in a SolrDocumentField instance", Z_STRVAL_P(member));
	}
*/
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_document_field_unset_property(zval *object, zval *member TSRMLS_DC) */
#if PHP_VERSION_ID < 50399
PHP_SOLR_API void solr_document_field_unset_property(zval *object, zval *member TSRMLS_DC)
#else
PHP_SOLR_API void solr_document_field_unset_property(zval *object, zval *member, const zend_literal *key TSRMLS_DC)
#endif
{
	solr_throw_exception(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1007_MSG, SOLR_ERROR_1007 TSRMLS_CC, SOLR_FILE_LINE_FUNC);

/*
	if (Z_TYPE_P(member) == IS_STRING)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Attempting to remove [%s] property in a SolrDocumentField instance", Z_STRVAL_P(member));
	}
*/
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

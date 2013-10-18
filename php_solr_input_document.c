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

/* $Id: php_solr_input_document.c 289006 2009-09-30 15:19:31Z iekpo $ */

#include "php_solr.h"

/** ************************************************************************ **/
/** DEFINITIONS FOR SOLR INPUT DOCUMENT METHODS                              **/
/** ************************************************************************ **/

/* {{{ proto void SolrInputDocument::__construct()
	SolrInputDocument constructor */
PHP_METHOD(SolrInputDocument, __construct)
{
	zval *objptr = getThis();
	uint nSize = SOLR_INITIAL_HASH_TABLE_SIZE;
	ulong document_index = SOLR_UNIQUE_DOCUMENT_INDEX();
	auto solr_document_t solr_doc;
	solr_document_t *doc_entry = NULL, *doc_ptr = NULL;

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
	zend_update_property_long(solr_ce_SolrInputDocument, objptr, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, document_index TSRMLS_CC);

	/* Keep track of how many SolrDocument instances we currently have */
	SOLR_GLOBAL(document_count)++;

	/* Overriding the default object handlers */
	Z_OBJ_HT_P(objptr) = &solr_input_document_object_handlers;
}

/* }}} */

/* {{{ proto void SolrInputDocument::__destruct(void)
	Destructor for SolrInputDocument */
PHP_METHOD(SolrInputDocument, __destruct)
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

/* {{{ proto void SolrInputDocument::__clone(void)
  Clones the current object. Not to be called directly. */
PHP_METHOD(SolrInputDocument, __clone)
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
	zend_update_property_long(solr_ce_SolrInputDocument, objptr, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, document_index TSRMLS_CC);

	/* Keep track of how many SolrDocument instances we currently have */
	SOLR_GLOBAL(document_count)++;
}
/* }}} */

/* {{{ proto void SolrInputDocument::__sleep(void)
 Should not be called directly. Serialization is not supported. */
PHP_METHOD(SolrInputDocument, __sleep)
{
	solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1005 TSRMLS_CC, SOLR_FILE_LINE_FUNC, SOLR_ERROR_1005_MSG);
}
/* }}} */

/* {{{ proto void SolrInputDocument::__wakeup(void)
 Should not be called directly. Serialization is not supported. */
PHP_METHOD(SolrInputDocument, __wakeup)
{
	solr_throw_exception_ex(solr_ce_SolrIllegalOperationException, SOLR_ERROR_1005 TSRMLS_CC, SOLR_FILE_LINE_FUNC, SOLR_ERROR_1005_MSG);
}
/* }}} */

/* {{{ proto bool SolrInputDocument::setBoost(float document_boost)
   Sets the boost for the document. */
PHP_METHOD(SolrInputDocument, setBoost)
{
	double boost_value = 0.0f;
	solr_document_t *doc_entry = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &boost_value) == FAILURE) {

		RETURN_FALSE;
	}

	/* If the submitted boost_value is negative. */
	if (boost_value < 0.0) {

		RETURN_FALSE;
	}

	/* Retrieve the document entry for this SolrDocument */
	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS) {

		doc_entry->document_boost = boost_value;

		RETURN_TRUE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto float SolrInputDocument::getBoost(void)
   Retrieves the boost for the document. */
PHP_METHOD(SolrInputDocument, getBoost)
{
	solr_document_t *doc_entry = NULL;

	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS) {

		RETURN_DOUBLE(doc_entry->document_boost);
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool SolrInputDocument::clear(void)
   Discards all the fields and resets the document boost to zero. */
PHP_METHOD(SolrInputDocument, clear)
{
	solr_document_t *doc_entry = NULL;

	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS) 	{

		doc_entry->document_boost = 0.0;
		doc_entry->field_count    = 0L;

		zend_hash_clean(doc_entry->fields);

		RETURN_TRUE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool SolrInputDocument::addField(string field_name, field_value [, float field_boost])
   Adds a field to the document. Can be called multiple times. */
PHP_METHOD(SolrInputDocument, addField)
{
	solr_char_t *field_name = NULL;
	int field_name_length  = 0;
	solr_char_t *field_value = NULL;
	int field_value_length = 0;
	double field_boost     = 0.0f;
	solr_document_t *doc_entry = NULL;

	/* Process the parameters passed to the method */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|d", &field_name,
			&field_name_length, &field_value,
			&field_value_length, &field_boost) == FAILURE) {

		RETURN_FALSE;
	}

	if (!field_name_length) {

		RETURN_FALSE;
	}

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS)
	{
		solr_field_list_t **field_values_ptr = NULL;
		solr_field_list_t *field_values      = NULL;

		/* If the field already exists in the SolrDocument instance append the value to the field list queue */
		if (zend_hash_find(doc_entry->fields, field_name, field_name_length, (void **) &field_values_ptr) == SUCCESS) {

			if (solr_document_insert_field_value(*field_values_ptr, field_value, field_boost) == FAILURE) {

				RETURN_FALSE;
			}

		} else {

			/* Otherwise, create a new one and add it to the hash table */
			field_values     = (solr_field_list_t *)  pemalloc(sizeof(solr_field_list_t), SOLR_DOCUMENT_FIELD_PERSISTENT);

			memset(field_values, 0, sizeof(solr_field_list_t));

			field_values_ptr = &field_values;

			field_values->count       = 0L;
			field_values->field_boost = 0.0;
			field_values->field_name  = (solr_char_t *) pestrdup(field_name,SOLR_DOCUMENT_FIELD_PERSISTENT);
			field_values->head        = NULL;
			field_values->last        = NULL;

			if (solr_document_insert_field_value(field_values, field_value, field_boost) == FAILURE) {

				solr_destroy_field_list(&field_values);

				RETURN_FALSE;
			}

			if (zend_hash_add(doc_entry->fields, field_name, field_name_length, (void *) field_values_ptr, sizeof(solr_field_list_t *), (void **) NULL) == FAILURE) {

				solr_destroy_field_list(&field_values);

				RETURN_FALSE;
			}

			/* Increment field count only when HEAD is added */
			doc_entry->field_count++;
		}

		RETURN_TRUE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool SolrInputDocument::setFieldBoost(string fieldname, float boost_value)
   Sets the boost for the specified field. */
PHP_METHOD(SolrInputDocument, setFieldBoost)
{
	solr_char_t *field_name = NULL;
	int field_name_length  = 0;
	double field_boost     = 0.0;
	solr_document_t *doc_entry = NULL;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sd", &field_name, &field_name_length, &field_boost) == FAILURE) {

		RETURN_FALSE;
	}

	if (!field_name_length) {

		RETURN_FALSE;
	}

	if (field_boost < 0.0) {

		RETURN_FALSE;
	}

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS) 	{

		solr_field_list_t **field_values = NULL;

		/* If the field already exists in the SolrDocument instance append the value to the field list queue */
		if (zend_hash_find(doc_entry->fields, (char *) field_name, field_name_length, (void **) &field_values) == SUCCESS) {

			(*field_values)->field_boost = field_boost;

			RETURN_TRUE;
		}


		RETURN_FALSE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto float SolrInputDocument::getFieldBoost(string fieldname)
   Returns the boost value for the specified field. */
PHP_METHOD(SolrInputDocument, getFieldBoost)
{
	solr_char_t *field_name = NULL;
	int field_name_length  = 0;
	solr_document_t *doc_entry = NULL;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &field_name, &field_name_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (!field_name_length) {

		RETURN_FALSE;
	}

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS) 	{

		solr_field_list_t **field_values = NULL;

		if (zend_hash_find(doc_entry->fields, (char *) field_name, field_name_length, (void **) &field_values) == SUCCESS) {

			RETURN_DOUBLE((*field_values)->field_boost);
		}

		RETURN_FALSE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto array SolrInputDocument::getFieldNames(void)
   Returns an array of all the field names in the document. */
PHP_METHOD(SolrInputDocument, getFieldNames)
{
	solr_document_t *doc_entry = NULL;

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS)
	{
		HashTable *fields_ht = doc_entry->fields;
		register zend_bool duplicate = 0;

		array_init(return_value);

		SOLR_HASHTABLE_FOR_LOOP(fields_ht)
		{
			char *fieldname       = NULL;
			uint fieldname_length = 0U;
			ulong num_index       = 0L;

			solr_field_list_t **field      = NULL;
			zend_bool duplicate_field_name = 1;

			zend_hash_get_current_key_ex(fields_ht, &fieldname, &fieldname_length, &num_index, duplicate, NULL);
			zend_hash_get_current_data_ex(fields_ht, (void **) &field, NULL);

			add_next_index_string(return_value, (char *) (*field)->field_name, duplicate_field_name);
		}

		/* We are done */
		return;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto int SolrInputDocument::getFieldCount(void)
   Returns the number of fields in document. Multivalued fields are only counted once. */
PHP_METHOD(SolrInputDocument, getFieldCount)
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

/* {{{ proto SolrDocumentField SolrInputDocument::getField(string fieldname)
   Returns the requested field. */
PHP_METHOD(SolrInputDocument, getField)
{
	solr_char_t *field_name = NULL;
	int field_name_length = 0;
	solr_document_t *doc_entry = NULL;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &field_name, &field_name_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (!field_name_length) {

		RETURN_FALSE;
	}


	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS)
	{
		solr_field_list_t **field_values = NULL;

		if (zend_hash_find(doc_entry->fields, (char *)field_name, field_name_length, (void **) &field_values) == SUCCESS)
		{
			solr_create_document_field_object(*field_values, &return_value TSRMLS_CC);

			/* The field was retrieved, so we're done here */
			return ;
		}

		RETURN_FALSE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto array SolrInputDocument::toArray(void)
   Returns an array representation of the object. */
PHP_METHOD(SolrInputDocument, toArray)
{
	solr_document_t *doc_entry = NULL;
	zval *fields_array = NULL;

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS)
	{
		register zend_bool duplicate = 0;
		HashTable *fields_ht;

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

/* {{{ proto bool SolrInputDocument::fieldExists(string field_name)
   Checks if the field name exists in the document. */
PHP_METHOD(SolrInputDocument, fieldExists)
{
	solr_char_t *field_name = NULL;
	int field_name_length = 0;
	solr_document_t *doc_entry = NULL;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &field_name, &field_name_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (!field_name_length) {

		RETURN_FALSE;
	}

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS) {

		if (zend_hash_exists(doc_entry->fields, (char *) field_name, field_name_length)) {

			RETURN_TRUE;

		} else {

			RETURN_FALSE;
		}
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool SolrInputDocument::deleteField(string field_name)
   Removes the request field from the document. */
PHP_METHOD(SolrInputDocument, deleteField)
{
	solr_char_t *field_name = NULL;
	int field_name_length = 0;
	solr_document_t *doc_entry = NULL;

	/* Process the parameters passed to the default constructor */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &field_name, &field_name_length) == FAILURE) {

		RETURN_FALSE;
	}

	if (!field_name_length) {

		RETURN_FALSE;
	}

	/* Retrieve the document entry for the SolrDocument instance */
	if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS) {
		if (zend_hash_del(doc_entry->fields, (char *) field_name, field_name_length) == SUCCESS) {
			doc_entry->field_count--;

			RETURN_TRUE;
		}

		RETURN_FALSE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool SolrInputDocument::sort(int sort_criterion [, int sort_direction])
   Sorts the document fields by the specified criterion. */
PHP_METHOD(SolrInputDocument, sort)
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

/* {{{ proto bool SolrInputDocument::merge(SolrInputDocument source [, bool override])
   Merges the source document to the current object. */
PHP_METHOD(SolrInputDocument, merge)
{
	solr_document_t *destination_document  = NULL;
	solr_document_t *source_document       = NULL;

	/* The destination SolrDocument instance */
	zval * destination_document_zval = getThis();

	/* The source SolrDocument instance */
	zval *source_document_zval = NULL;

	/* Should we skip fields that already exist in destination */
	zend_bool overwrite = (zend_bool) 0;

	copy_ctor_func_t p_copy_ctor = (copy_ctor_func_t) field_copy_constructor;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O|b", &source_document_zval, solr_ce_SolrInputDocument, &overwrite) == FAILURE) {

		RETURN_FALSE;
	}

	if (solr_fetch_document_entry(source_document_zval, &source_document TSRMLS_CC) == FAILURE) {

		RETURN_FALSE;
	}

	if (solr_fetch_document_entry(destination_document_zval, &destination_document TSRMLS_CC) == FAILURE) {

		RETURN_FALSE;
	}

	if (zend_hash_num_elements(source_document->fields) == 0) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Source SolrInputDocument has no fields. Source documentId");

		RETURN_FALSE;
	}

	/* Copy the fields in the source HashTable to the destination HashTable */
	zend_hash_merge(destination_document->fields, source_document->fields, p_copy_ctor, NULL, sizeof(solr_field_list_t *), (int) overwrite);

	/* Update the field count */
	destination_document->field_count = (uint) zend_hash_num_elements(destination_document->fields);

	RETURN_TRUE;
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

/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2015 The PHP Group                                |
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

/* $Id$ */

#include "php_solr.h"

PHP_SOLR_API zend_object *solr_document_object_handler_clone(zval *zobject TSRMLS_DC)
{
    zend_object *old_object;
    zend_object *new_object;
    solr_document_t *doc_entry, *old_doc_entry;
    long document_index = SOLR_UNIQUE_DOCUMENT_INDEX();

    old_object = Z_OBJ_P(zobject);
    new_object = zend_objects_new(old_object->ce);
    zend_objects_clone_members(new_object, old_object);

    if (solr_fetch_document_entry(zobject, &old_doc_entry TSRMLS_CC) == FAILURE) {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Clone Failed: Unable to fetch document entry of the source document");
    }

    doc_entry = solr_init_document(document_index);
    ZVAL_LONG(&(new_object->properties_table[0]), document_index)
    /* Add the document entry to the directory of documents */
    doc_entry->field_count = old_doc_entry->field_count;
    doc_entry->document_boost = old_doc_entry->document_boost;

    zend_hash_copy(doc_entry->fields, old_doc_entry->fields, (copy_ctor_func_t) field_copy_constructor);
    zend_hash_copy(doc_entry->children, old_doc_entry->children, (copy_ctor_func_t) zval_add_ref);

    return new_object;
}

PHP_SOLR_API void field_copy_constructor_ex(solr_field_list_t **original_field_queue_ptr)
{
    solr_field_list_t *original_field_queue = *original_field_queue_ptr;
    solr_field_value_t *ptr = original_field_queue->head;
    if (ptr == NULL)
    {
        return;
    }

    solr_field_list_t *new_field_queue = (solr_field_list_t *) pemalloc(sizeof(solr_field_list_t), SOLR_DOCUMENT_FIELD_PERSISTENT);

    new_field_queue->count       = 0L;
    new_field_queue->field_name  = (solr_char_t *) pestrdup((char *) (original_field_queue)->field_name, SOLR_DOCUMENT_FIELD_PERSISTENT);
    new_field_queue->head        = NULL;
    new_field_queue->last        = NULL;
    new_field_queue->field_boost = original_field_queue->field_boost;

    while(ptr != NULL)
    {
        if (solr_document_insert_field_value(new_field_queue, ptr->field_value, 0) == FAILURE) {
            php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to insert field value");
        }

        ptr = ptr->next;
    }

    *original_field_queue_ptr = new_field_queue;
}
/* {{{ void field_copy_constructor_zv(zval *field_queue_zv) */
PHP_SOLR_API void field_copy_constructor_zv(zval *field_queue_zv)
{
    solr_field_list_t *original_field_queue = NULL;
	original_field_queue = Z_PTR_P(field_queue_zv);
	field_copy_constructor_ex(&original_field_queue);
	ZVAL_PTR(field_queue_zv, original_field_queue);
}
/* }}} */


/* {{{ PHP_SOLR_API int solr_document_insert_field_value(solr_field_list_t *queue, const solr_char_t *field_value, double field_boost) */
PHP_SOLR_API int solr_document_insert_field_value(solr_field_list_t *queue, const solr_char_t *field_value, double field_boost)
{
	solr_field_value_t *new_entry = (solr_field_value_t *) pemalloc(sizeof(solr_field_value_t), SOLR_DOCUMENT_FIELD_PERSISTENT);

	if (new_entry == NULL) {

		return FAILURE;
	}

	new_entry->field_value = (solr_char_t *) pestrdup((char *) field_value, SOLR_DOCUMENT_FIELD_PERSISTENT);

	if (new_entry->field_value == NULL) {

		return FAILURE;
	}

	new_entry->next = NULL;

	if (queue->head == NULL) {

		/* This is the first and only item in the field list */
		queue->head = new_entry;
		queue->last = new_entry;

		/* Update the field boost value */
		if (field_boost > 0.0) {

			queue->field_boost = field_boost;
		}

	} else { /* There are already entries in the list. */

		/* Append to the end of the queue */
		queue->last->next = new_entry;

		/* Set the last item in the queue to the latest entry */
		queue->last       = new_entry;

		/* Update the field boost value */
		if (field_boost > 0.0) {

			if (queue->field_boost > 0.0) {

				queue->field_boost *= field_boost;

			} else {

				queue->field_boost = field_boost;
			}
		}
	}

	queue->count++;

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_SOLR_API solr_document_t *solr_init_document(long int document_index)
 * create and allocate a solr_document_t with the specified index
 */
PHP_SOLR_API solr_document_t *solr_init_document(long int document_index)
{
    uint nSize = SOLR_INITIAL_HASH_TABLE_SIZE;
    solr_document_t *doc_ptr = NULL;
    solr_document_t *doc_entry;

#ifdef PHP_7
    doc_entry = pemalloc(sizeof(solr_document_t), SOLR_DOCUMENT_PERSISTENT);
#endif

    doc_entry->document_index  = document_index;
    doc_entry->field_count     = 0L;
    doc_entry->document_boost  = 0.0f;

    /* Allocated memory for the fields HashTable using fast cache for HashTables */
    ALLOC_HASHTABLE(doc_entry->fields);
    ALLOC_HASHTABLE(doc_entry->children);

    /* Initializing the hash table used for storing fields in this SolrDocument */
    zend_hash_init(doc_entry->fields, nSize, NULL, (dtor_func_t) solr_destroy_field_list_ht_dtor, SOLR_DOCUMENT_FIELD_PERSISTENT);
    zend_hash_init(doc_entry->children, nSize, NULL, ZVAL_PTR_DTOR, SOLR_DOCUMENT_FIELD_PERSISTENT);

    /* Let's check one more time before insert into the HashTable */
    if (zend_hash_index_exists(SOLR_GLOBAL(documents), document_index)) {
        /* todo call dtor ? */
        pefree(doc_entry->fields, SOLR_DOCUMENT_FIELD_PERSISTENT);

        pefree(doc_entry->children, SOLR_DOCUMENT_FIELD_PERSISTENT);
        return NULL;
    }

    /* Add the document entry to the directory of documents */
    doc_ptr = zend_hash_index_update_ptr(SOLR_GLOBAL(documents), document_index, (void *) doc_entry);

    /* Keep track of how many SolrDocument instances we currently have */
    SOLR_GLOBAL(document_count)++;
    return doc_ptr;
}
/* }}} */

/* {{{ PHP_SOLR_API solr_document_t *solr_input_doc_ctor(zval *objptr)
 * constructor populate/allocate the new document after object instantiation
 * and allocates hashtables for fields and children
 */
PHP_SOLR_API solr_document_t *solr_input_doc_ctor(zval *objptr)
{
    ulong document_index = SOLR_UNIQUE_DOCUMENT_INDEX();
    solr_document_t *solr_doc = NULL;

    if ((solr_doc = solr_init_document(document_index)) == NULL)
    {
        return NULL;
    }

    /* Set the value of the internal id property */
    zend_update_property_long(solr_ce_SolrInputDocument, objptr, SOLR_INDEX_PROPERTY_NAME, sizeof(SOLR_INDEX_PROPERTY_NAME) - 1, document_index TSRMLS_CC);

    /* Overriding the default object handlers */
    Z_OBJ_HT_P(objptr) = &solr_input_document_object_handlers;
    return solr_doc;
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_destroy_document_zv(zval *document)
 * destory a solr_document within a zval (ZE 3)
 */
PHP_SOLR_API void solr_destroy_document_zv(zval *document)
{
    solr_document_t *doc_entry = (solr_document_t *) Z_PTR_P(document);

    solr_destroy_document_ex(doc_entry);

    pefree(doc_entry, SOLR_DOCUMENT_PERSISTENT);
}
/* }}} */

/* {{{  void solr_destroy_document(void *document)
 * destory a solr_document_t
 */
PHP_SOLR_API void solr_destroy_document_ex(solr_document_t *doc_entry)
{
    /* Release all the field_lists one at a time with solr_destroy_field_list */
    zend_hash_destroy(doc_entry->fields);

    /* Deallocate memory for the fields HashTable */
    pefree(doc_entry->fields, SOLR_DOCUMENT_FIELD_PERSISTENT);
    if (doc_entry->children) {
        zend_hash_destroy(doc_entry->children);
        pefree(doc_entry->children, SOLR_DOCUMENT_FIELD_PERSISTENT);
    }
}
/* }}} */

PHP_SOLR_API void solr_destroy_field_list_ht_dtor(zval *zv_field_entry)
{
    solr_field_list_t *field_entry = Z_PTR_P(zv_field_entry);
    solr_destroy_field_list(field_entry);
}

/* {{{ void solr_destroy_field_list(solr_field_list_t **field_entry_ptr) */
PHP_SOLR_API void solr_destroy_field_list(solr_field_list_t *field_entry)
{
	solr_field_value_t *tmp = NULL;
	solr_field_value_t *current_field_value = field_entry->head;

	/* Go through the list and free all the values */
	while(current_field_value != NULL) {

		tmp = current_field_value->next;

		pefree(current_field_value->field_value, SOLR_DOCUMENT_FIELD_PERSISTENT);

		pefree(current_field_value, SOLR_DOCUMENT_FIELD_PERSISTENT);

		current_field_value = tmp;
	}

	field_entry->head = NULL;

	field_entry->last = NULL;

	pefree(field_entry->field_name, SOLR_DOCUMENT_FIELD_PERSISTENT);

	pefree(field_entry, SOLR_DOCUMENT_FIELD_PERSISTENT);
}
/* }}} */

/* Comparison functions for field entries */

/* {{{ int solr_compare_field_name(const void *a, const void *b TSRMLS_DC) */
PHP_SOLR_API int solr_compare_field_name(const void *a, const void *b TSRMLS_DC)
{
#ifdef PHP_7
    const Bucket *x = (Bucket *) a;
    const Bucket *y = (Bucket *) b;
#else
    const Bucket *x = *((Bucket **) a);
    const Bucket *y = *((Bucket **) b);
#endif


	const solr_field_list_t *first  = (solr_field_list_t *) Z_PTR(x->val);
	const solr_field_list_t *second = (solr_field_list_t *) Z_PTR(y->val);

	const int diff = strcmp((char *) first->field_name, (char *) second->field_name);

	const int result = ((diff > 0) ? 1 : ((diff < 0) ? -1 : 0));

	return result;
}
/* }}} */

/* {{{ 	int solr_rcompare_field_name(const void *a, const void *b TSRMLS_DC) */
PHP_SOLR_API int solr_rcompare_field_name(const void *a, const void *b TSRMLS_DC)
{
	return (solr_compare_field_name(a, b TSRMLS_CC) * -1);
}
/* }}} */

/* {{{	int solr_compare_field_value_count(const void *a, const void *b TSRMLS_DC) */
PHP_SOLR_API int solr_compare_field_value_count(const void *a, const void *b TSRMLS_DC)
{
#ifdef PHP_7
    const Bucket *x = (Bucket *) a;
    const Bucket *y = (Bucket *) b;
#else
    const Bucket *x = *((Bucket **) a);
    const Bucket *y = *((Bucket **) b);
#endif
    const solr_field_list_t *first  = (solr_field_list_t *) Z_PTR(x->val);
    const solr_field_list_t *second = (solr_field_list_t *) Z_PTR(y->val);

	const int diff = first->count - second->count;

	const int result = ((diff > 0) ? 1 : ((diff < 0) ? -1 : 0));

	return result;
}
/* }}} */

/* {{{	int solr_rcompare_field_value_count(const void *a, const void *b TSRMLS_DC)	*/
PHP_SOLR_API int solr_rcompare_field_value_count(const void *a, const void *b TSRMLS_DC)
{
	return (solr_compare_field_value_count(a, b TSRMLS_CC) * -1);
}
/* }}} */

/* {{{ 	int solr_compare_field_boost_value(const void *a, const void *b TSRMLS_DC) */
PHP_SOLR_API int solr_compare_field_boost_value(const void *a, const void *b TSRMLS_DC)
{
#ifdef PHP_7
    const Bucket *x = (Bucket *) a;
    const Bucket *y = (Bucket *) b;
#else
    const Bucket *x = *((Bucket **) a);
    const Bucket *y = *((Bucket **) b);
#endif

    const solr_field_list_t *first  = (solr_field_list_t *) Z_PTR(x->val);
    const solr_field_list_t *second = (solr_field_list_t *) Z_PTR(y->val);

	const double diff = first->field_boost - second->field_boost;

	const int result = ((diff > 0.0) ? 1 : ((diff < 0.0) ? -1 : 0));

	return result;
}
/* }}} */

/* {{{ 	int solr_rcompare_field_boost_value(const void *a, const void *b TSRMLS_DC) */
PHP_SOLR_API int solr_rcompare_field_boost_value(const void *a, const void *b TSRMLS_DC)
{
	return (solr_compare_field_boost_value(a, b TSRMLS_CC) * -1);
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_create_document_field_object(solr_field_list_t *field_values, zval **field_obj TSRMLS_DC) */
PHP_SOLR_API void solr_create_document_field_object(solr_field_list_t *field_values, zval **field_obj TSRMLS_DC)
{
	zval *doc_field = *field_obj;

	solr_field_value_t *curr_ptr = NULL;
	zval field_values_array_tmp;
	zval *field_values_array = &field_values_array_tmp;

	array_init(field_values_array);

	curr_ptr = field_values->head;

	while(curr_ptr != NULL) {

		solr_char_t *current_value = curr_ptr->field_value;

		add_next_index_string(field_values_array, current_value);

		curr_ptr = curr_ptr->next;
	}

	object_init_ex(doc_field, solr_ce_SolrDocumentField);

	zend_update_property_string(solr_ce_SolrDocumentField, doc_field, SOLR_FIELD_NAME_PROPERTY_NAME, sizeof(SOLR_FIELD_NAME_PROPERTY_NAME)-1, field_values->field_name TSRMLS_CC);
	zend_update_property_double(solr_ce_SolrDocumentField, doc_field, SOLR_FIELD_BOOST_PROPERTY_NAME, sizeof(SOLR_FIELD_BOOST_PROPERTY_NAME)-1, field_values->field_boost TSRMLS_CC);
	zend_update_property(solr_ce_SolrDocumentField, doc_field, SOLR_FIELD_VALUES_PROPERTY_NAME, sizeof(SOLR_FIELD_VALUES_PROPERTY_NAME)-1, field_values_array TSRMLS_CC);

	zval_ptr_dtor(field_values_array);

	Z_OBJ_HT_P(doc_field) = &solr_document_field_handlers;
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_create_document_field_object(solr_field_list_t *field_values, zval **field_obj TSRMLS_DC)
    constructs the <doc> element when adding a document to the index */
PHP_SOLR_API void solr_add_doc_node(xmlNode *root_node, solr_document_t *doc_entry TSRMLS_DC)
{
    HashTable *document_fields = NULL;
    xmlNode *solr_doc_node = NULL;
    document_fields = doc_entry->fields;

    solr_doc_node = xmlNewChild(root_node, NULL, (xmlChar *) "doc", NULL);

   if (doc_entry->document_boost > 0.0f)
   {
       auto char tmp_buffer[256]; /* Scratch pad for converting numeric values to strings */
       memset(tmp_buffer, 0, sizeof(tmp_buffer));
       php_gcvt(doc_entry->document_boost, EG(precision), '.', 'e' , tmp_buffer);
       xmlNewProp(solr_doc_node, (xmlChar *) "boost", (xmlChar *) tmp_buffer);
   }

   solr_generate_document_xml_from_fields(solr_doc_node, document_fields TSRMLS_CC);
   if (zend_hash_num_elements(doc_entry->children) > 0) {

       SOLR_HASHTABLE_FOR_LOOP(doc_entry->children)
       {
           zval *doc_obj = NULL;
           solr_document_t *child_doc_entry = NULL;
           doc_obj = zend_hash_get_current_data(doc_entry->children);
           if (solr_fetch_document_entry(doc_obj, &child_doc_entry TSRMLS_CC) == SUCCESS)
           {
               solr_add_doc_node(solr_doc_node, child_doc_entry TSRMLS_CC);
           }
       }
   }
}
/* }}} */


/* {{{ static void solr_generate_document_xml_from_fields(xmlNode *solr_doc_node, HashTable *document_fields) */
PHP_SOLR_API void solr_generate_document_xml_from_fields(xmlNode *solr_doc_node, HashTable *document_fields TSRMLS_DC)
{
    xmlDoc *doc_ptr = solr_doc_node->doc;

    SOLR_HASHTABLE_FOR_LOOP(document_fields)
    {
        solr_char_t *doc_field_name;
        solr_field_value_t *doc_field_value;
        solr_field_list_t *field = NULL;
        zend_bool is_first_value = 1; /* Turn on first value flag */

        field = (solr_field_list_t *)zend_hash_get_current_data_ptr(document_fields);

        doc_field_name = field->field_name;
        doc_field_value = field->head;

        /* Loop through all the values for this field */
        while(doc_field_value != NULL)
        {
            xmlChar *escaped_field_value = xmlEncodeEntitiesReentrant(doc_ptr, (xmlChar *) doc_field_value->field_value);

            xmlNode *solr_field_node = xmlNewChild(solr_doc_node, NULL, (xmlChar *) "field", escaped_field_value);

            xmlNewProp(solr_field_node, (xmlChar *) "name", (xmlChar *) doc_field_name);

            /* Set the boost attribute if this is the first value */
            if (is_first_value && field->field_boost > 0.0f)
            {
                auto char tmp_boost_value_buffer[256];

                memset(tmp_boost_value_buffer, 0, sizeof(tmp_boost_value_buffer));

                php_gcvt(field->field_boost, EG(precision), '.', 'e' , tmp_boost_value_buffer);

                xmlNewProp(solr_field_node, (xmlChar *) "boost", (xmlChar *) tmp_boost_value_buffer);

                is_first_value = 0; /* Turn off the flag */
            }

            /* Release the memory allocated by xmlEncodeEntitiesReentrant */
            xmlFree(escaped_field_value);

            /* Grab the next value for this field if any */
            doc_field_value = doc_field_value->next;

        } /* while(doc_field_value != NULL) */

    } /* SOLR_HASHTABLE_FOR_LOOP(document_fields) */
}
/* }}} */


PHP_SOLR_API void solr_document_get_field_names(INTERNAL_FUNCTION_PARAMETERS)
{
    solr_document_t *doc_entry = NULL;

    /* Retrieve the document entry for the SolrDocument instance */
    if (solr_fetch_document_entry(getThis(), &doc_entry TSRMLS_CC) == SUCCESS)
    {
        HashTable *fields_ht = doc_entry->fields;

        array_init(return_value);

        SOLR_HASHTABLE_FOR_LOOP(fields_ht)
        {
            solr_field_list_t *field      = NULL;
            field = zend_hash_get_current_data_ptr(fields_ht);
            add_next_index_string(return_value, (char *) field->field_name);
        }
        return;
    }

    RETURN_FALSE;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

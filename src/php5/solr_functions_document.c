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

/* {{{ void field_copy_constructor(solr_field_list_t **original_field_queue) */
PHP_SOLR_API void field_copy_constructor(solr_field_list_t **original_field_queue)
{
	solr_field_list_t *new_field_queue = NULL;
	solr_field_value_t *ptr = (*original_field_queue)->head;

	if (ptr == NULL)
	{
		return;
	}

	new_field_queue = (solr_field_list_t *) pemalloc(sizeof(solr_field_list_t), SOLR_DOCUMENT_FIELD_PERSISTENT);

	new_field_queue->count       = 0L;
	new_field_queue->field_name  = (solr_char_t *) pestrdup((char *) (*original_field_queue)->field_name, SOLR_DOCUMENT_FIELD_PERSISTENT);
	new_field_queue->head        = NULL;
	new_field_queue->last        = NULL;
	new_field_queue->field_boost = (*original_field_queue)->field_boost;

	while(ptr != NULL)
	{
		solr_document_insert_field_value(new_field_queue, ptr->field_value, 0);

		ptr = ptr->next;
	}

	*original_field_queue = new_field_queue;
}
/* }}} */

/* {{{ PHP_SOLR_API solr_document_t *solr_init_document(long int document_index)
 * create and allocate a solr_document_t with the specified index
 */
PHP_SOLR_API solr_document_t *solr_init_document(long int document_index TSRMLS_DC)
{
  solr_document_t *doc_entry = NULL, *doc_ptr = NULL;
  solr_document_t solr_doc;

  uint nSize = SOLR_INITIAL_HASH_TABLE_SIZE;

  memset(&solr_doc, 0, sizeof(solr_document_t));

  doc_entry = &solr_doc;

  doc_entry->document_index  = document_index;
  doc_entry->field_count     = 0L;
  doc_entry->document_boost  = 0.0f;

  /* Allocated memory for the fields HashTable using fast cache for HashTables */
  ALLOC_HASHTABLE(doc_entry->fields);
  ALLOC_HASHTABLE(doc_entry->children);

  /* Initializing the hash table used for storing fields in this SolrDocument */
  zend_hash_init(doc_entry->fields, nSize, NULL, (dtor_func_t) solr_destroy_field_list, SOLR_DOCUMENT_FIELD_PERSISTENT);
  zend_hash_init(doc_entry->children, nSize, NULL, ZVAL_PTR_DTOR, SOLR_DOCUMENT_FIELD_PERSISTENT);

  /* Let's check one more time before insert into the HashTable */
  if (zend_hash_index_exists(SOLR_GLOBAL(documents), document_index)) {

      pefree(doc_entry->fields, SOLR_DOCUMENT_FIELD_PERSISTENT);
      zend_hash_destroy(doc_entry->children);
      pefree(doc_entry->fields, SOLR_DOCUMENT_FIELD_PERSISTENT);

      return NULL;
  }

  /* Add the document entry to the directory of documents */
  zend_hash_index_update(SOLR_GLOBAL(documents), document_index, (void *) doc_entry, sizeof(solr_document_t), (void **) &doc_ptr);

  /* Keep track of how many SolrDocument instances we currently have */
  SOLR_GLOBAL(document_count)++;

  return doc_ptr;
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

/* {{{ 	void solr_destroy_document(void *document) */
PHP_SOLR_API void solr_destroy_document(void *document)
{
	solr_document_t *doc_entry = (solr_document_t *) document;

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

/* {{{ void solr_destroy_field_list(solr_field_list_t **field_entry_ptr) */
PHP_SOLR_API void solr_destroy_field_list(solr_field_list_t **field_entry_ptr)
{
	solr_field_list_t *field_entry = *field_entry_ptr;

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
	const Bucket *x = *((Bucket **) a);
	const Bucket *y = *((Bucket **) b);

	const solr_field_list_t *first  = *((solr_field_list_t **) x->pData);
	const solr_field_list_t *second = *((solr_field_list_t **) y->pData);

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
	const Bucket *x = *((Bucket **) a);
	const Bucket *y = *((Bucket **) b);

	const solr_field_list_t *first  = *((solr_field_list_t **) x->pData);
	const solr_field_list_t *second = *((solr_field_list_t **) y->pData);

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
	const Bucket *x = *((Bucket **) a);
	const Bucket *y = *((Bucket **) b);

	const solr_field_list_t *first  = *((solr_field_list_t **) x->pData);
	const solr_field_list_t *second = *((solr_field_list_t **) y->pData);

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
	zval *field_values_array = NULL;
	solr_field_value_t *curr_ptr = NULL;

	MAKE_STD_ZVAL(field_values_array);

	array_init(field_values_array);

	curr_ptr = field_values->head;

	while(curr_ptr != NULL) {

		solr_char_t *current_value = curr_ptr->field_value;

		add_next_index_string(field_values_array, current_value, 1);

		curr_ptr = curr_ptr->next;
	}

	object_init_ex(doc_field, solr_ce_SolrDocumentField);

	zend_update_property_string(solr_ce_SolrDocumentField, doc_field, SOLR_FIELD_NAME_PROPERTY_NAME, sizeof(SOLR_FIELD_NAME_PROPERTY_NAME)-1, field_values->field_name TSRMLS_CC);
	zend_update_property_double(solr_ce_SolrDocumentField, doc_field, SOLR_FIELD_BOOST_PROPERTY_NAME, sizeof(SOLR_FIELD_BOOST_PROPERTY_NAME)-1, field_values->field_boost TSRMLS_CC);
	zend_update_property(solr_ce_SolrDocumentField, doc_field, SOLR_FIELD_VALUES_PROPERTY_NAME, sizeof(SOLR_FIELD_VALUES_PROPERTY_NAME)-1, field_values_array TSRMLS_CC);

	zval_ptr_dtor(&field_values_array);

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

       php_gcvt(doc_entry->document_boost, EG(precision), '.', 'e' , (char *)tmp_buffer);
       xmlNewProp(solr_doc_node, (xmlChar *) "boost", (xmlChar *) tmp_buffer);
   }

   solr_generate_document_xml_from_fields(solr_doc_node, document_fields TSRMLS_CC);
   if (zend_hash_num_elements(doc_entry->children) > 0) {

       SOLR_HASHTABLE_FOR_LOOP(doc_entry->children)
       {
           zval **doc_obj = NULL;
           solr_document_t *child_doc_entry = NULL;
           zend_hash_get_current_data_ex(doc_entry->children, (void **)&doc_obj, ((HashPosition *)0));
           if (solr_fetch_document_entry(*doc_obj, &child_doc_entry TSRMLS_CC) == SUCCESS)
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
        solr_field_list_t **field = NULL;
        zend_bool is_first_value = 1; /* Turn on first value flag */

        zend_hash_get_current_data_ex(document_fields, (void **) &field, ((HashPosition *)0));

        doc_field_name = (*field)->field_name;
        doc_field_value = (*field)->head;

        /* Loop through all the values for this field */
        while(doc_field_value != NULL)
        {
            xmlChar *escaped_field_value = xmlEncodeEntitiesReentrant(doc_ptr, (xmlChar *) doc_field_value->field_value);

            xmlNode *solr_field_node = xmlNewChild(solr_doc_node, NULL, (xmlChar *) "field", escaped_field_value);

            xmlNewProp(solr_field_node, (xmlChar *) "name", (xmlChar *) doc_field_name);

            /* Set the boost attribute if this is the first value */
            if (is_first_value && (*field)->field_boost > 0.0f)
            {
                auto char tmp_boost_value_buffer[256];

                memset(tmp_boost_value_buffer, 0, sizeof(tmp_boost_value_buffer));
                php_gcvt((*field)->field_boost, EG(precision), '.', 'e' , tmp_boost_value_buffer);

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

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

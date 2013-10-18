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

/* $Id: solr_macros.h 320130 2011-11-28 20:44:55Z pierrick $ */

#ifndef SOLR_MACROS_H
#define SOLR_MACROS_H

#include <limits.h>

/* Macros for Object constructors and destructors declaration */
#define SOLR_CTOR(class_name, func_name, arginfo) PHP_ME(class_name, func_name, arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
#define SOLR_DTOR(class_name, func_name, arginfo) PHP_ME(class_name, func_name, arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)

/* Retrieve a unique hash index for this SolrDocument. Unique for this thread */
#define SOLR_UNIQUE_DOCUMENT_INDEX() solr_hashtable_get_new_index(SOLR_GLOBAL(documents) TSRMLS_CC)

/* Retrieve a unique hash index for this SolrClient. Unique for this thread */
#define SOLR_UNIQUE_CLIENT_INDEX() solr_hashtable_get_new_index(SOLR_GLOBAL(clients) TSRMLS_CC)

/* Retrieve a unique hash index for this SolrParams instance. Unique for this thread */
#define SOLR_UNIQUE_PARAMS_INDEX() solr_hashtable_get_new_index(SOLR_GLOBAL(params) TSRMLS_CC)

/* Iterates through the HashTable pointer */
#define SOLR_HASHTABLE_FOR_LOOP(HashTablePtr) \
	if (HashTablePtr) for ( zend_hash_internal_pointer_reset((HashTablePtr)); \
	SUCCESS == zend_hash_has_more_elements((HashTablePtr)); \
	zend_hash_move_forward((HashTablePtr)) )

/* Gets a random number between 1 and SHRT_MAX */
#define SOLR_GET_RANDOM_NUMBER() abs(rand() % SHRT_MAX + 1)

/* {{{ Memory Allocation Macros */
/* Used only to release truly persistent allocations */
#define SOLR_FREE_PTR(ptr) { if (ptr != NULL) { pefree(ptr,SOLR_HASHTABLE_PERSISTENT); ptr = NULL; } else { printf("\nSOLR_FREE_PTR double free() from function %s() called in %s on line %d\n", __func__, __FILE__, __LINE__);  } }
/* }}} */

/**
 * Used to retrieve xmlAttr and xmlNode values
 *
 * At this time, I am not sure if the next and previous sibling links
 * are guaranteed to be document order 100% of the time.
 * This is why I am requiring matches for the attribute and element names before
 * copying values from the attributes or element nodes.
 * Since I am not 100%, I believe it is better to be safe than sorry.
 * There may be a slight performance hit but at least correctness is guaranteed.
 */
#define solr_xml_match_node(solrXmlNode, solrXmlNodeName) ( \
		xmlStrEqual(solrXmlNode->name, (xmlChar *) solrXmlNodeName) && \
		solrXmlNode->children && solrXmlNode->children->content )

/* Checks if children is a valid struct */
#define solr_xml_child_content_is_valid(solrXmlNode) (solrXmlNode && solrXmlNode->children)

/* Checks to prevent segmentation fault. Ensures that children is a valid struct before attempting to get content */
#define solr_xml_get_node_contents(solrXmlNode) (solr_xml_child_content_is_valid(solrXmlNode)? (solrXmlNode->children->content) : ((xmlChar *) ""))

#define solr_xml_get_node_contents_int(solrXmlNode) atoi((char *)solr_xml_get_node_contents(solrXmlNode))

#define solr_xml_get_node_contents_double(solrXmlNode) xmlXPathCastStringToNumber(solr_xml_get_node_contents(solrXmlNode))

/**
 * Used to manage SolrQuery parameters that allow overrides by field name.
 *
 * Many parameters may be overridden on a per-field basis with the following syntax
 *
 *  f.<fieldName>.<FacetParam>=<value>
 *  f.<fieldName>.<originalParam>=<value>
 *
 * @buf pointer to a solr_string_t object
 * @fname field name
 * @fname_len length of the field name
 * @pname a string constant representing the name of the parameter.
 */
#define solr_query_field_override(buf, fname, fname_len, pname) { \
	if ((fname_len)) { \
		solr_string_append_const((buf), "f.");	\
		solr_string_appends((buf), (fname), (fname_len)); \
		solr_string_appendc((buf), '.');	\
	}	\
	solr_string_append_const((buf), (pname)); \
}

/* Macro for returning SolrParams objects if requested */
#define solr_return_solr_params_object() { \
	if(return_value_used) { \
		solr_set_return_solr_params_object((return_value_ptr), getThis() TSRMLS_CC); \
	} \
}

#endif /* SOLR_MACROS_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

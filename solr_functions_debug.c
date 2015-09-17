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
   | Authors:                                                             |
   |         Omar Shaban <omars@php.net>                                  |
   |         Israel Ekpo <iekpo@php.net>                                  |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#include "php_solr.h"

/* {{{ void solr_debug_printf(const char *format, ...) */
PHP_SOLR_API void solr_debug_printf(const char *format, ...)
{
#ifdef SOLR_DEBUG
	va_list args;
	va_start(args,format);
	vprintf(format,args);
	va_end(args);
#endif
}
/* }}} */

/* {{{ void solr_debug_print_fields(const solr_field_list_t *field_list) */
PHP_SOLR_API void solr_debug_print_fields(const solr_field_list_t *field_list)
{
	/* Used to debug field inserted */
}
/* }}} */

/**
 * print_xpath_nodes:
 * @nodes:      the nodes set.
 * @output:     the output file handle.
 *
 * Prints the @nodes content to @output.
 */
/* {{{ void print_xpath_nodes(xmlNodeSetPtr nodes, FILE* output) */
PHP_SOLR_API void print_xpath_nodes(xmlNodeSetPtr nodes, FILE* output) {
    xmlNodePtr cur;
    int size;
    int i;

    assert(output);
    size = (nodes) ? nodes->nodeNr : 0;

    fprintf(output, "Result (%d nodes):\n", size);
    for(i = 0; i < size; ++i) {
        assert(nodes->nodeTab[i]);

        if(nodes->nodeTab[i]->type == XML_NAMESPACE_DECL) {
            xmlNsPtr ns;

            ns = (xmlNsPtr)nodes->nodeTab[i];
            cur = (xmlNodePtr)ns->next;
            if(cur->ns) {
                fprintf(output, "= namespace \"%s\"=\"%s\" for node %s:%s\n",
                        ns->prefix, ns->href, cur->ns->href, cur->name);
            } else {
                fprintf(output, "= namespace \"%s\"=\"%s\" for node %s\n",
                        ns->prefix, ns->href, cur->name);
            }
        } else if(nodes->nodeTab[i]->type == XML_ELEMENT_NODE) {
            cur = nodes->nodeTab[i];
            if(cur->ns) {
                fprintf(output, "= element node \"%s:%s\"\n",
                        cur->ns->href, cur->name);
            } else {
                fprintf(output, "= element node \"%s\"\n",
                        cur->name);
            }
        } else {
            cur = nodes->nodeTab[i];
            fprintf(output, "= node \"%s\": type %d\n", cur->name, cur->type);
        }
    }
}
/* }}} */

/* {{{ void print_children (xmlNode * node) */
PHP_SOLR_API void print_children (xmlNode * node)
{
    fprintf(stdout,"\n================- start print children -=================\n");
    while (node != NULL)
    {
        if(node->ns) {
            fprintf(stdout, "= element node \"%s:%s\"\n",
                    node->ns->href,node->name);
        } else {
            fprintf(stdout, "= element node \"%s\"\n",
                    node->name);
        }

        if(node->type == XML_ELEMENT_NODE){
            xmlNode * cur2 = node->children;
            while (cur2 != NULL)
            {
                if(strcmp((const char *)cur2->name,"text")==0)
                {
                    fprintf(stdout, "= element node \"%s\", text: %s\n",cur2->name,cur2->content);
                }else{
                    fprintf(stdout, "= element node \"%s\"\n",
                            cur2->name);
                }
                cur2 = cur2->next;
            }
        }

        if(node->children != NULL)
        {
            print_children(node->children);
        }

        node = node->next;
    }
    fprintf(stdout,"\n======================- end -=====================\n");
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

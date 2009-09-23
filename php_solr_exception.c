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

/* $Id$ */

#include "php_solr.h"

/* TODO : implement more methods for SolrException to grab
 *  : __LINE__, __func__, __FILE__
 *
 *  These could be useful for debugging.
 */

PHP_METHOD(SolrException, getInternalFile);
PHP_METHOD(SolrException, getInternalLine);
PHP_METHOD(SolrException, getInternalFunction);

PHP_METHOD(SolrException, getInternalFile)
{

}

PHP_METHOD(SolrException, getInternalLine)
{

}

PHP_METHOD(SolrException, getInternalFunction)
{

}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

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

/* $Id: php_solr_api.h 288601 2009-09-23 03:43:20Z iekpo $ */

/**
 * Declaring Macro for function attributes
 *
 * This is for functions on GNU systems and Win32 systems
 *
 * On Win32 systems __declspec(dllexport) adds the export directive to the
 * object file so you do not need to use a .def file
 *
 * Using __declspec(dllexport) in addition to using a .def file should
 * not cause build errors.
 */
#ifndef PHP_SOLR_API_H
#define PHP_SOLR_API_H
#ifdef PHP_WIN32
#define PHP_SOLR_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#define PHP_SOLR_API __attribute__ ((visibility("default")))
#else
#define PHP_SOLR_API
#endif
#endif /* PHP_SOLR_API_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

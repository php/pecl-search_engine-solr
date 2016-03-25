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
   |          Israel Ekpo <iekpo@php.net>                                 |
   |          Omar Shaban <omars@php.net>                                 |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#include "php_version.h"

#ifndef PHP_SOLR_VERSION_H
#define PHP_SOLR_VERSION_H

#define PHP_SOLR_MAJOR_VERSION 2
#define PHP_SOLR_MINOR_VERSION 4
#define PHP_SOLR_PATCH_VERSION 0

#define PHP_SOLR_RELEASE_VERSION PHP_SOLR_PATCH_VERSION

#define PHP_SOLR_VERSION "2.4.0"
#define PHP_SOLR_DOTTED_VERSION PHP_SOLR_VERSION


/**
 * Extension version numbers using hexadecimal numbers
 *
 * This is the numeric version of the extension, meant for easier
 * parsing and comparisons by programs. The PHP_SOLR_VERSION_ID define will
 * always follow this syntax:
 *
 * 0xXXYYZZ
 *
 * Where XX, YY and ZZ are the main version, minor version and patch numbers in
 * hexadecimal (using 8 bits each). All three numbers are always represented
 * using two digits.  1.2 would appear as "0x010200" while version 9.11.7
 * appears as "0x090b07".
 *
 * This 6-digit (24 bits) hexadecimal number does not show pre-release number,
 * and it is always a greater number in a more recent release. It makes
 * comparisons with greater than and less than work.
 */

#define PHP_SOLR_VERSION_ID 0x020400

#define SOLR_CLIENT_USER_AGENT "PHP Solr Client 2.4.0"

#endif /* PHP_SOLR_VERSION_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

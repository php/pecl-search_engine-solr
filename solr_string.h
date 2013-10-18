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

/* $Id: solr_string.h 291683 2009-12-04 04:57:03Z iekpo $ */

#ifndef SOLR_STRING_H
#define SOLR_STRING_H

#include <main/php.h>
#include <Zend/zend_alloc.h>

#define SOLR_STRING_PERSISTENT 0
#define SOLR_STRING_START_SIZE 64
#define SOLR_STRING_INCREMENT_SIZE 128

#define SOLR_STRING_LONG_BUFFER_SIZE 16
#define SOLR_STRING_UNSIGNED_LONG_BUFFER_SIZE 32

#include "php_solr_api.h"

#ifdef SOLR_DEBUG
/* #define SOLR_MEM_DEBUG 1 Uncomment if you need memdebug enabled */
#endif

#ifdef SOLR_MEM_DEBUG

#define SOLR_MEM_DEBUG_DC , const char * mm_function, char * mm_filename, int mm_line
#define SOLR_MEM_DEBUG_CC , mm_function, mm_filename, mm_line
#define SOLR_MEM_DEBUG_RC , __func__, __FILE__, __LINE__

#else

#define SOLR_MEM_DEBUG_DC
#define SOLR_MEM_DEBUG_CC
#define SOLR_MEM_DEBUG_RC

#endif

/**
 * solr_char_t
 *
 * iekpo 2009/08/28
 *
 * Decided to create this type just in case there is a special need in the
 * future to use unsigned char instead of plain char to transport character
 * arrays within the library.
 *
 * Having this typedef will allow us to toggle easily between plain char and
 * unsigned char, without having to do a massive search and replace.
 *
 * There may be a few cases where casting may be needed to handle cases where
 * the sign of the variable is now the opposite.
 */
typedef char solr_char_t;

/* Structure to store solr strings */
typedef struct _solr_string {

	solr_char_t  *str; 	/* The buffer to store the character array. */

	size_t len; 		/* The current length of the solr_string_t object  */

	size_t cap; 		/* The current capacity of the solr_string_t object */

} solr_string_t;

#define SOLR_STRING_INITIALIZER {.str = ((solr_char_t *)0), .len = 0U, .cap = 0U}

/* Appends a string constant to a solr_string_t */
#define solr_string_append_const(dest, str) solr_string_appends((dest), (solr_char_t *) str, sizeof(str)-1)

/* Appends one solr_string_t to another */
#define solr_string_append_solr_string(dest, src) solr_string_appends((dest), (src)->str, (src)->len)

/* Initializes the solr_string_t structure to empty values */
#define solr_string_init(dest) 		\
{ 									\
	(dest)->str = (solr_char_t *) 0x00; 	\
	(dest)->len = 0U; 				\
	(dest)->cap = 0U; 				\
}

#define solr_strndup estrndup

#define solr_strdup estrdup

#define solr_strlen strlen

#define solr_string_appends(dest, src, len) solr_string_appends_ex((dest), (src), (len) SOLR_MEM_DEBUG_RC)

#define solr_string_appendc(dest, ch) solr_string_appendc_ex((dest), (ch) SOLR_MEM_DEBUG_RC)

#define solr_string_append_long(dest, long_val) solr_string_append_long_ex((dest), (long_val) SOLR_MEM_DEBUG_RC)

#define solr_string_append_unsigned_long(dest, long_val) solr_string_append_unsigned_long((dest), (long_val) SOLR_MEM_DEBUG_RC)

#define solr_string_set(dest, value, length) solr_string_set_ex((dest), (value), (length) SOLR_MEM_DEBUG_RC)

#define solr_string_free(dest) solr_string_free_ex((dest) SOLR_MEM_DEBUG_RC)

PHP_SOLR_API void solr_string_appends_ex(solr_string_t *dest, const solr_char_t *src, size_t length SOLR_MEM_DEBUG_DC);

PHP_SOLR_API void solr_string_appendc_ex(solr_string_t *dest, solr_char_t ch SOLR_MEM_DEBUG_DC);

PHP_SOLR_API void solr_string_append_long_ex(solr_string_t *dest, long int long_val SOLR_MEM_DEBUG_DC);

PHP_SOLR_API void solr_string_append_unsigned_long_ex(solr_string_t *dest, unsigned long int long_val SOLR_MEM_DEBUG_DC);

PHP_SOLR_API void solr_string_remove_last_char(solr_string_t *dest);

PHP_SOLR_API int solr_string_equal(const solr_string_t *a, const solr_string_t *b);

PHP_SOLR_API void solr_string_free_ex(solr_string_t *dest SOLR_MEM_DEBUG_DC);

PHP_SOLR_API void solr_string_set_ex(solr_string_t *dest, const solr_char_t *value, size_t length SOLR_MEM_DEBUG_DC);

#endif /* SOLR_STRING_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

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

/* $Id: solr_string.c 290464 2009-11-10 05:59:49Z iekpo $ */

#include "php_solr.h"

/* {{{ static inline void solr_string_alloc(solr_string_t *dest, size_t length, size_t *new_length SOLR_MEM_DEBUG_DC) */
static inline void solr_string_alloc(solr_string_t *dest, size_t length, size_t *new_length SOLR_MEM_DEBUG_DC)
{
	/* If buffer is empty */
	if (!dest->str)
	{
		(*new_length) = length;

		dest->cap     = ((*new_length) < SOLR_STRING_START_SIZE) ? SOLR_STRING_START_SIZE : (length + SOLR_STRING_INCREMENT_SIZE);
		dest->str     = (solr_char_t *) perealloc(dest->str, dest->cap * sizeof(solr_char_t), SOLR_STRING_PERSISTENT);

	} else {

		(*new_length) = dest->len + length;

		/* If the buffer full, get more space */
		if ((*new_length) >= dest->cap)
		{
			dest->cap = (*new_length) + SOLR_STRING_INCREMENT_SIZE;

			dest->str = (solr_char_t *) perealloc(dest->str, dest->cap * sizeof(solr_char_t), SOLR_STRING_PERSISTENT);
		}
	}

#ifdef SOLR_MEM_DEBUG

php_printf("solr_string_alloc() [Re]allocated %u bytes at %p in %s(), %s Line %d \n", dest->cap, dest->str SOLR_MEM_DEBUG_CC);

#endif

}
/* }}} */

/* {{{ PHP_SOLR_API void solr_string_appends(solr_string_t *dest, const solr_char_t *src, size_t length SOLR_MEM_DEBUG_DC) */
PHP_SOLR_API void solr_string_appends_ex(solr_string_t *dest, const solr_char_t *src, size_t length SOLR_MEM_DEBUG_DC)
{
	auto size_t __new_length = 0U;

	/* (Re)allocates memory and increases the capacity if necessary */
	solr_string_alloc(dest, length, &__new_length SOLR_MEM_DEBUG_CC);

	/* Copy the data from the source to the destination */
	memcpy(dest->str + dest->len, src, length);

	/* Reset the length of the solr_string to the new value */
	dest->len = __new_length;

	/* Always make it a null-terminated string */
	dest->str[__new_length] = (solr_char_t) 0x00;
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_string_appendc(solr_string_t *dest, solr_char_t ch SOLR_MEM_DEBUG_DC) */
PHP_SOLR_API void solr_string_appendc_ex(solr_string_t *dest, solr_char_t ch SOLR_MEM_DEBUG_DC)
{
	auto size_t __new_length = 0U;

	/* (Re)allocates memory and increases the capacity if necessary */
	solr_string_alloc(dest, 1, &__new_length SOLR_MEM_DEBUG_CC);

	dest->str[dest->len] = ch;

	/* Reset the length of the solr_string to the new value (dest->len + 1) */
	dest->len = __new_length;

	/* Always make it a null-terminated string */
	dest->str[__new_length] = (solr_char_t) 0x00;
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_string_remove_last_char(solr_string_t *dest) */
PHP_SOLR_API void solr_string_remove_last_char(solr_string_t *dest)
{
	if (dest->str && dest->len)
	{
		dest->str[dest->len - 1] = (solr_char_t) 0x00;

		dest->len--;
	}
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_string_append_long(solr_string_t *dest, long int long_val) */
PHP_SOLR_API void solr_string_append_long_ex(solr_string_t *dest, long int long_val SOLR_MEM_DEBUG_DC)
{
	auto size_t __new_length = 0U;
	auto char tmp_buffer[SOLR_STRING_LONG_BUFFER_SIZE];
	size_t length = 0;

	/* Write the formated long to the buffer */
	php_sprintf(tmp_buffer, "%ld", long_val);

	length = strlen(tmp_buffer);

	/* (Re)allocates memory and increases the capacity if necessary */
	solr_string_alloc(dest, length, &__new_length SOLR_MEM_DEBUG_CC);

	/* Copy the data from the source to the destination */
	memcpy(dest->str + dest->len, tmp_buffer, length);

	/* Reset the length of the solr_string to the new value */
	dest->len = __new_length;

	/* Always make it a null-terminated string */
	dest->str[__new_length] = (solr_char_t) 0x00;
}
/* }}} */

/* {{{ PHP_SOLR_API void solr_string_append_unsigned_long(solr_string_t *dest, unsigned long int long_val) */
PHP_SOLR_API void solr_string_append_unsigned_long_ex(solr_string_t *dest, unsigned long int long_val SOLR_MEM_DEBUG_DC)
{
	auto size_t __new_length = 0U;
	auto char tmp_buffer[SOLR_STRING_UNSIGNED_LONG_BUFFER_SIZE];
	size_t length = 0;

	/* Write the formated unsigned long to the buffer */
	php_sprintf(tmp_buffer, "%lu", long_val);

	length = strlen(tmp_buffer);

	/* (Re)allocates memory and increases the capacity if necessary */
	solr_string_alloc(dest, length, &__new_length SOLR_MEM_DEBUG_CC);

	/* Copy the data from the source to the destination */
	memcpy(dest->str + dest->len, tmp_buffer, length);

	/* Reset the length of the solr_string to the new value */
	dest->len = __new_length;

	/* Always make it a null-terminated string */
	dest->str[__new_length] = (solr_char_t) 0x00;
}
/* }}} */

/**
 * Checks if both strings are equal OR have same exact content.
 *
 * Returns 1 if they are equal, 0 if they are different.
 */
/* {{{ PHP_SOLR_API int solr_string_equal(const solr_string_t *a, const solr_string_t *b) */
PHP_SOLR_API int solr_string_equal(const solr_string_t *a, const solr_string_t *b)
{
	const solr_char_t *str1 = a->str;
	const solr_char_t *str2 = b->str;

	if (str1 == str2) return 1;
    if (str1 == NULL) return 0;
    if (str2 == NULL) return 0;

    do {

        if (*str1++ != *str2) return(0);

    } while (*str2++);

    return 1;
}
/* }}} */

/* Deallocates memory for the buffer */
/* {{{ PHP_SOLR_API void solr_string_free(solr_string_t *dest SOLR_MEM_DEBUG_DC) */
PHP_SOLR_API void solr_string_free_ex(solr_string_t *dest SOLR_MEM_DEBUG_DC)
{
	/* Only attempt this if the buffer is still valid */
	if (dest->str)
	{

#ifdef SOLR_MEM_DEBUG

php_printf("solr_string_free_ex() Releasing %u bytes at %p in %s(), %s Line %d \n", dest->cap, dest->str SOLR_MEM_DEBUG_CC);

#endif
		pefree(dest->str, SOLR_STRING_PERSISTENT);

		dest->str = (solr_char_t *) 0x00;

		dest->cap = dest->len = 0U;
	}
}
/* }}} */

/* Update the contents of the dest solr_string */
/* {{{ PHP_SOLR_API void solr_string_set(solr_string_t *dest, const solr_char_t *value, size_t length SOLR_MEM_DEBUG_DC) */
PHP_SOLR_API void solr_string_set_ex(solr_string_t *dest, const solr_char_t *value, size_t length SOLR_MEM_DEBUG_DC)
{
	solr_string_free(dest);

	solr_string_appends(dest, value, length);
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

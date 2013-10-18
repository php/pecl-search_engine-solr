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

/* $Id: php_solr_bc_macros.h 288661 2009-09-24 17:06:52Z iekpo $ */

/**
 * PHP 5 backward compatibility macros
 *
 * With the arrival of ZE 2.3.0, some of the member structures of the zval struct
 * were renamed. These macros will allow us to still be able to use the
 * new macros introduced since php 5.3.0 to compile code in the PHP 5.2.x series.
 *
 * We should allow up to php version 5.2.11. The latest stable release as of the
 * time of the initial release of this extension.
 */

#ifndef PHP_SOLR_BC_MACROS_H
#define PHP_SOLR_BC_MACROS_H

/* Retrieves the refcount */
#ifndef Z_REFCOUNT_P
#define Z_REFCOUNT_P(pz) (pz)->refcount;
#define Z_REFCOUNT_PP(ppz) Z_REFCOUNT_P(*(ppz))
#endif

/* Sets the refcount to the specified value. */
#ifndef Z_SET_REFCOUNT_P
#define Z_SET_REFCOUNT_P(pz, rc) (pz)->refcount = rc;
#define Z_SET_REFCOUNT_PP(ppz) Z_SET_REFCOUNT_P((*ppz), rc)
#endif

/* Increases the recount by 1 */
#ifndef Z_ADDREF_P
#define Z_ADDREF_P(pz) (pz)->refcount++;
#define Z_ADDREF_PP(ppz) Z_ADDREF_P(*(ppz))
#endif

/* Reduces the refcount by 1 */
#ifndef Z_DELREF_P
#define Z_DELREF_P(pz) (pz)->refcount--;
#define Z_DELREF_PP(ppz) Z_DELREF_P(*(ppz))
#endif

/* Sets the isref member on the zval */
#ifndef Z_SET_ISREF_P
#define Z_SET_ISREF_P(pz) (pz)->is_ref = 1;
#define Z_SET_ISREF_PP(ppz) Z_SET_ISREF_P(*(ppz))
#endif

/* Unsets the isref member on the zval */
#ifndef Z_UNSET_ISREF_P
#define Z_UNSET_ISREF_P(pz) (pz)->is_ref = 0;
#define Z_UNSET_ISREF_PP(ppz ) Z_UNSET_ISREF_P(*(ppz))
#endif

/* Checks if is_ref is set on the zval */
#ifndef Z_ISREF_P
#define Z_ISREF_P(pz) ((pz)->is_ref)
#define Z_ISREF_PP(ppz) Z_ISREF_P(*(ppz))
#endif

/* Sets the is_ref member to the specified value */
#ifndef Z_SET_ISREF_TO_P
#define Z_SET_ISREF_TO_P(pz, isref) (pz)->is_ref = is_ref;
#define Z_SET_ISREF_TO_PP(ppz, isref) Z_SET_ISREF_TO_P(*(ppz), isref)
#endif

#endif /* PHP_SOLR_BC_MACROS_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */

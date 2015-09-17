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
   | Author: Omar Shaban <omars@php.net>                                  |
   +----------------------------------------------------------------------+
*/

#ifndef SOLR_DISMAX_QUERY_H_
#define SOLR_DISMAX_QUERY_H_

void init_solr_dismax_query(TSRMLS_D);
PHP_METHOD(SolrDisMaxQuery, __construct);
PHP_METHOD(SolrDisMaxQuery, setQueryAlt);
PHP_METHOD(SolrDisMaxQuery, addQueryField);
PHP_METHOD(SolrDisMaxQuery, removeQueryField);

PHP_METHOD(SolrDisMaxQuery, addPhraseField);
PHP_METHOD(SolrDisMaxQuery, removePhraseField);
PHP_METHOD(SolrDisMaxQuery, setPhraseFields);

PHP_METHOD(SolrDisMaxQuery, setPhraseSlop);
PHP_METHOD(SolrDisMaxQuery, setQueryPhraseSlop);

PHP_METHOD(SolrDisMaxQuery, setBoostQuery);
PHP_METHOD(SolrDisMaxQuery, addBoostQuery);
PHP_METHOD(SolrDisMaxQuery, removeBoostQuery);

PHP_METHOD(SolrDisMaxQuery, setBoostFunction);
PHP_METHOD(SolrDisMaxQuery, setMinimumMatch);
PHP_METHOD(SolrDisMaxQuery, setTieBreaker);

PHP_METHOD(SolrDisMaxQuery, useDisMaxQueryParser);
PHP_METHOD(SolrDisMaxQuery, useEDisMaxQueryParser);

PHP_METHOD(SolrDisMaxQuery, setBigramPhraseFields);
PHP_METHOD(SolrDisMaxQuery, addBigramPhraseField);
PHP_METHOD(SolrDisMaxQuery, removeBigramPhraseField);
PHP_METHOD(SolrDisMaxQuery, setBigramPhraseSlop);

PHP_METHOD(SolrDisMaxQuery, setTrigramPhraseFields);
PHP_METHOD(SolrDisMaxQuery, addTrigramPhraseField);
PHP_METHOD(SolrDisMaxQuery, removeTrigramPhraseField);
PHP_METHOD(SolrDisMaxQuery, setTrigramPhraseSlop);

PHP_METHOD(SolrDisMaxQuery, addUserField);
PHP_METHOD(SolrDisMaxQuery, removeUserField);
PHP_METHOD(SolrDisMaxQuery, setUserFields);

#endif /* SOLR_DISMAX_QUERY_H_ */

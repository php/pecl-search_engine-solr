/*
 * solr_dismax_query.h
 *
 *  Created on: Sep 10, 2014
 *      Author: omar
 */

#ifndef SOLR_DISMAX_QUERY_H_
#define SOLR_DISMAX_QUERY_H_

void init_solr_dismax_query(TSRMLS_D);
PHP_METHOD(SolrDisMaxQuery, setQueryAlt);
PHP_METHOD(SolrDisMaxQuery, __construct);
PHP_METHOD(SolrDisMaxQuery, addQueryField);
PHP_METHOD(SolrDisMaxQuery, removeQueryField);
PHP_METHOD(SolrDisMaxQuery, addPhraseField);
PHP_METHOD(SolrDisMaxQuery, removePhraseField);
PHP_METHOD(SolrDisMaxQuery, setPhraseSlop);
PHP_METHOD(SolrDisMaxQuery, setQueryPhraseSlop);
PHP_METHOD(SolrDisMaxQuery, setBoostQuery);
PHP_METHOD(SolrDisMaxQuery, addBoostQuery);
PHP_METHOD(SolrDisMaxQuery, setBoostFunction);
PHP_METHOD(SolrDisMaxQuery, setMinimumMatch);
PHP_METHOD(SolrDisMaxQuery, setTieBreaker);

#endif /* SOLR_DISMAX_QUERY_H_ */

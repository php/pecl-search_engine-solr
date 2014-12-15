/*
 * solr_dismax_query.h
 *
 *  Created on: Sep 10, 2014
 *      Author: omar
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
#endif /* SOLR_DISMAX_QUERY_H_ */

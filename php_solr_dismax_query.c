#include "php_solr.h"

extern function_entry;
//extern SOLR_ARG_PASS_BY_REF_FALSE;
//extern SOLR_ARG_PASS_REMAINING_BY_REF_FALSE;
//extern SOLR_METHOD_RETURN_REFERENCE_FALSE;
/*extern solr_ce_SolrQuery;*/

zend_class_entry *solr_ce_SolrDixMaxQuery;

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery_addQueryField_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(0, field_name)
ZEND_ARG_INFO(0, boost)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery__construct_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_ARG_INFO(0, q)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery_removeQueryField_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(0, field)
ZEND_END_ARG_INFO();

static zend_function_entry solr_dismax_query_methods[] = {
    PHP_ME(SolrDisMaxQuery, __construct, SolrDisMaxQuery__construct_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, setQueryAlt, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, addQueryField, SolrDisMaxQuery_addQueryField_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, removeQueryField, SolrDisMaxQuery_removeQueryField_args, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void init_solr_dismax_query(TSRMLS_D){
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "SolrDisMaxQuery", solr_dismax_query_methods);
    solr_ce_SolrDixMaxQuery = zend_register_internal_class_ex(
            &ce,
            solr_ce_SolrQuery,
            NULL TSRMLS_CC
    );

    solr_query_register_class_constants(solr_ce_SolrDixMaxQuery TSRMLS_CC);
}

/* {{{ proto SolrQuery::__construct([string q])
   Constructor for SolrDisMaxQuery */
PHP_METHOD(SolrDisMaxQuery, __construct)
{
    zval *param_value = NULL;
    int param_value_len = 0;
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &param_value, &param_value_len) == FAILURE){
            php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameters");
            RETURN_NULL();
    }
    if(param_value == NULL){
        zend_call_method_with_0_params(&getThis(), solr_ce_SolrDixMaxQuery, &solr_ce_SolrDixMaxQuery->parent->constructor, "__construct", NULL);
    }else{
        zend_call_method_with_1_params(&getThis(), solr_ce_SolrDixMaxQuery, &solr_ce_SolrDixMaxQuery->parent->constructor, "__construct", NULL, param_value);
    }
    //(obj, obj_ce, fn_proxy, function_name, retval, arg1)
}
/* }}} */
/* {{{ proto SolrQuery::setQueryAlt([string q])
   SetQueryAlt uses q.alt if the q param is not defined */
PHP_METHOD(SolrDisMaxQuery, setQueryAlt)
{
    solr_char_t *pname = "q.alt";
    int pname_len = sizeof("q.alt")-1;
    solr_char_t *param_value = NULL;
    int param_value_len = 0;
    int set_param_return = 0;
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_len) == FAILURE){
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameters");
        RETURN_NULL();
    }

    set_param_return = solr_add_or_set_normal_param(getThis(), pname, pname_len, param_value, param_value_len, 0 TSRMLS_CC);
    if(set_param_return == FAILURE)
    {
        RETURN_NULL();
    }
    solr_return_solr_params_object();
}
/* }}} */

/* {{{ proto SolrQuery::addQueryField([string field, bool boost])
   SetQueryAlt uses q.alt if the q param is not defined */
PHP_METHOD(SolrDisMaxQuery, addQueryField) {
    solr_char_t *pname = "qf";
    int pname_len = sizeof("qf")-1;
//    double boost=0.0;
    int boost_len;
    solr_char_t *boost_str = NULL;
    solr_char_t *field_name = NULL;
    int field_name_len = 0;
    int add_result = 0;
    zval * boost = NULL;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|z", &field_name, &field_name_len, &boost) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameters");
        RETURN_NULL();
    }

    if(boost != NULL)
    {
        convert_to_string(boost);
        boost_str = Z_STRVAL_P(boost);
//        printf("%s \n",boost_str);

    }

    add_result = solr_add_arg_list_param(getThis(), pname, pname_len, field_name, field_name_len, boost_str, Z_STRLEN_P(boost),' ','^' TSRMLS_CC);
    if(add_result == FAILURE)
    {
        RETURN_NULL();
    }
    solr_return_solr_params_object();
//    if (solr_add_arg_list_param(getThis(), param_name, param_name_length, param_value, param_value_length, avalue, avalue_length, ',', ' ' TSRMLS_CC) == FAILURE)
//        {
//            RETURN_NULL();
//        }

}
/* {{{  proto SolrDisMaxQuery SolrDisMaxQuery::removeQueryField(string field)
   Removes a sort field from the sort parameter. */
PHP_METHOD(SolrDisMaxQuery, removeQueryField)
{
    solr_char_t *pname = (solr_char_t*) "qf";
    int pname_len = sizeof("qf")-1;
    solr_char_t *field_name = NULL;
    int field_name_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &field_name, &field_name_len) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }
    solr_delete_arg_list_param_value(
            getThis(), pname, pname_len, field_name, field_name_len TSRMLS_CC
    );
}
/* }}} */

/* {{{  proto SolrQuery SolrQuery::removeSortField(string fl)
   Removes a sort field from the sort parameter. */
//PHP_METHOD(SolrQuery, removeSortField)
//{
//    solr_char_t *pname = (solr_char_t *) "sort";
//    int pname_length = sizeof("sort")-1;
//
//    solr_char_t *param_value = NULL;
//    int param_value_length = 0;
//
//    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_length) == FAILURE) {
//
//        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
//
//        RETURN_NULL();
//    }
//
//    solr_delete_arg_list_param_value(getThis(), pname, pname_length, param_value, param_value_length TSRMLS_CC);
//
//    solr_return_solr_params_object();
//}
/* }}} */

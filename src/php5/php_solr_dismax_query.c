#include "php_solr.h"

/* extern function_entry; */

zend_class_entry *solr_ce_SolrDixMaxQuery;

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery_zero_arg_info, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery_addQueryField_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(0, field)
ZEND_ARG_INFO(0, boost)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery__construct_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 0)
ZEND_ARG_INFO(0, q)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery__queryAlt_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(0, q)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery_remove_field_arg, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(0, field)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery_addPhraseField_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 2)
ZEND_ARG_INFO(0, field)
ZEND_ARG_INFO(0, boost)
ZEND_ARG_INFO(0, slop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery_addBoostQuery_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 2)
ZEND_ARG_INFO(0, field)
ZEND_ARG_INFO(0, value)
ZEND_ARG_INFO(0, boost)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery_setPhraseSlop_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(0, slop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery_setBoostFunction_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(0, function)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery_setMinimumMatch_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery_setTieBreaker_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(0, tieBreaker)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery_setFields_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(0, fields)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery_uf_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(0, field)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(SolrDisMaxQuery_setufs_args, SOLR_ARG_PASS_REMAINING_BY_REF_FALSE, SOLR_METHOD_RETURN_REFERENCE_FALSE, 1)
ZEND_ARG_INFO(0, fields)
ZEND_END_ARG_INFO()

static zend_function_entry solr_dismax_query_methods[] = {
    PHP_ME(SolrDisMaxQuery, __construct, SolrDisMaxQuery__construct_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, setQueryAlt, SolrDisMaxQuery__queryAlt_args, ZEND_ACC_PUBLIC)

    PHP_ME(SolrDisMaxQuery, addQueryField, SolrDisMaxQuery_addQueryField_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, removeQueryField, SolrDisMaxQuery_remove_field_arg, ZEND_ACC_PUBLIC)

    PHP_ME(SolrDisMaxQuery, addPhraseField, SolrDisMaxQuery_addPhraseField_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, removePhraseField, SolrDisMaxQuery_remove_field_arg, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, setPhraseFields, SolrDisMaxQuery_setFields_args, ZEND_ACC_PUBLIC)


    PHP_ME(SolrDisMaxQuery, setPhraseSlop, SolrDisMaxQuery_setPhraseSlop_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, setQueryPhraseSlop, SolrDisMaxQuery_setPhraseSlop_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, setBoostQuery, SolrDisMaxQuery__queryAlt_args   , ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, addBoostQuery, SolrDisMaxQuery_addBoostQuery_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, removeBoostQuery, SolrDisMaxQuery_remove_field_arg, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, setBoostFunction, SolrDisMaxQuery_setBoostFunction_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, setMinimumMatch, SolrDisMaxQuery_setMinimumMatch_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, setTieBreaker, SolrDisMaxQuery_setTieBreaker_args, ZEND_ACC_PUBLIC)

    PHP_ME(SolrDisMaxQuery, useDisMaxQueryParser, SolrDisMaxQuery_zero_arg_info, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, useEDisMaxQueryParser, SolrDisMaxQuery_zero_arg_info, ZEND_ACC_PUBLIC)

    PHP_ME(SolrDisMaxQuery, setBigramPhraseFields, SolrDisMaxQuery_setFields_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, addBigramPhraseField, SolrDisMaxQuery_addPhraseField_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, removeBigramPhraseField, SolrDisMaxQuery_remove_field_arg, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, setBigramPhraseSlop, SolrDisMaxQuery_setPhraseSlop_args, ZEND_ACC_PUBLIC)

    PHP_ME(SolrDisMaxQuery, setTrigramPhraseFields, SolrDisMaxQuery_setFields_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, addTrigramPhraseField, SolrDisMaxQuery_addPhraseField_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, removeTrigramPhraseField, SolrDisMaxQuery_remove_field_arg, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, setTrigramPhraseSlop, SolrDisMaxQuery_setPhraseSlop_args, ZEND_ACC_PUBLIC)

    PHP_ME(SolrDisMaxQuery, addUserField, SolrDisMaxQuery_uf_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, removeUserField, SolrDisMaxQuery_uf_args, ZEND_ACC_PUBLIC)
    PHP_ME(SolrDisMaxQuery, setUserFields, SolrDisMaxQuery_setufs_args, ZEND_ACC_PUBLIC)

    PHP_FE_END
};

void init_solr_dismax_query(TSRMLS_D){
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "SolrDisMaxQuery", solr_dismax_query_methods);
    solr_ce_SolrDixMaxQuery = zend_register_internal_class_ex(
            &ce,
            solr_ce_SolrQuery,
            NULL TSRMLS_CC
    );
}

/* {{{ proto SolrQuery::__construct([string q])
   Constructor for SolrDisMaxQuery */
PHP_METHOD(SolrDisMaxQuery, __construct)
{
    zval *param_value = NULL;
    solr_char_t *deftype_param_name = "defType", *deftype_param_value = SOLR_DISMAX_DEFAULT_PARSER;
    int deftype_param_name_len = strlen("defType"), deftype_param_value_len = strlen(SOLR_DISMAX_DEFAULT_PARSER);

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &param_value) == FAILURE){
            php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameters");
            RETURN_NULL();
    }
    if(param_value == NULL){
        zend_call_method_with_0_params(&getThis(), solr_ce_SolrDixMaxQuery, &solr_ce_SolrDixMaxQuery->parent->constructor, "__construct", NULL);
    }else{
        zend_call_method_with_1_params(&getThis(), solr_ce_SolrDixMaxQuery, &solr_ce_SolrDixMaxQuery->parent->constructor, "__construct", NULL, param_value);
    }
    solr_add_or_set_normal_param(
            getThis(),
            deftype_param_name,
            deftype_param_name_len,
            deftype_param_value,
            deftype_param_value_len,
            0 TSRMLS_CC
    );
}
/* }}} */

/* {{{ proto SolrQuery::useDisMaxQueryParser()
   Switch Query Parser to dismax */
PHP_METHOD(SolrDisMaxQuery, useDisMaxQueryParser)
{
    solr_char_t *param_name = "defType", *param_value = "dismax";
    int param_name_len = strlen("defType"), param_value_len = strlen("dismax"), result=1;

    result = solr_add_or_set_normal_param(
            getThis(),
            param_name,
            param_name_len,
            param_value,
            param_value_len,
            0 TSRMLS_CC
    );

    if(result != SUCCESS)
    {
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{ proto SolrQuery::useDisMaxQueryParser()
   Switch Query Parser to edismax */
PHP_METHOD(SolrDisMaxQuery, useEDisMaxQueryParser)
{
    solr_char_t *pname = "defType", *param_value = "edismax";
    int pname_len = strlen("defType"), param_value_len = strlen("edismax"), result=1;

    result = solr_add_or_set_normal_param(
            getThis(),
            pname,
            pname_len,
            param_value,
            param_value_len,
            0 TSRMLS_CC
    );

    if(result != SUCCESS)
    {
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{ proto SolrQuery::setQueryAlt(string q)
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
    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{ proto SolrQuery::addQueryField(string field[, bool boost])
   SetQueryAlt uses q.alt if the q param is not defined */
PHP_METHOD(SolrDisMaxQuery, addQueryField) {
    solr_char_t *pname = "qf";
    int pname_len = sizeof("qf")-1;
    solr_char_t *boost_str = NULL;
    solr_char_t *field_name = NULL;
    int field_name_len = 0;
    int add_result = 0;
    solr_char_t *delimiter = " ";
    solr_char_t *separator = "^";
    solr_char_t *separator_override="";
    zval * boost = NULL;
    int boost_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|z", &field_name, &field_name_len, &boost) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameters");
        RETURN_NULL();
    }

    if(boost != NULL)
    {
        convert_to_string(boost);
        boost_str = Z_STRVAL_P(boost);
        boost_len = Z_STRLEN_P(boost);
        add_result = solr_add_arg_list_param(
                getThis(), pname, pname_len, field_name, field_name_len,
                boost_str, boost_len, *delimiter, *separator TSRMLS_CC
        );
    }else{
        boost_str = "";
        add_result = solr_add_arg_list_param_ex(
                        getThis(), pname, pname_len, field_name, field_name_len,
                        boost_str, boost_len, *delimiter, *separator, *separator_override TSRMLS_CC
        );
    }

    if(add_result == FAILURE)
    {
        RETURN_NULL();
    }

    SOLR_RETURN_THIS();
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
    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{ proto SolrDisMaxQuery SolrDisMaxQuery::addPhraseField(string field, float boost [, float slop])
 * Adds a new phrase field
 */
PHP_METHOD(SolrDisMaxQuery, addPhraseField)
{
    solr_char_t *pname = (solr_char_t*) "pf";
    int pname_len = sizeof("pf")-1;
    solr_char_t *field_name = NULL;
    int field_name_len = 0;
    zval *boost = NULL;
    zval *slop = NULL;
    solr_char_t *boost_str = NULL;
    solr_char_t *slop_str = NULL;
    int add_result = 0;
    char * separator = "^";
    solr_char_t * delimiter_override = "";
    solr_string_t boost_slop_buffer;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sz|z", &field_name, &field_name_len, &boost, &slop) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }

    if(boost != NULL)
    {
        convert_to_string(boost);
        boost_str = Z_STRVAL_P(boost);
    }

    if (slop != NULL) {
        convert_to_string(slop);
        slop_str = Z_STRVAL_P(slop);
    }

    if (slop != NULL && boost !=NULL)
    {
        delimiter_override = "~";
        memset(&boost_slop_buffer, 0, sizeof(solr_string_t));
        solr_string_appends(&boost_slop_buffer, (solr_char_t *)slop_str , Z_STRLEN_P(slop));
        solr_string_appendc(&boost_slop_buffer, '^');
        solr_string_appends(&boost_slop_buffer, boost_str , Z_STRLEN_P(boost));
        add_result = solr_add_arg_list_param_ex(
                    getThis(), pname, pname_len, field_name, field_name_len,
                    boost_slop_buffer.str, boost_slop_buffer.len, ' ', *separator,
                    *delimiter_override TSRMLS_CC
        );

        solr_string_free(&boost_slop_buffer);
    } else {
        add_result = solr_add_arg_list_param(
                    getThis(), pname, pname_len, field_name, field_name_len,
                    boost_str, Z_STRLEN_P(boost),' ',*separator
                    TSRMLS_CC
        );
    }

    if(add_result == FAILURE)
    {
        RETURN_NULL();
    }

    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{  proto SolrDisMaxQuery SolrDisMaxQuery::removeQueryField(string field)
   Removes a phrase field from pf. */
PHP_METHOD(SolrDisMaxQuery, removePhraseField)
{
    solr_char_t *pname = (solr_char_t*) "pf";
    int pname_len = sizeof("pf")-1;
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
    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{ proto SolrQuery::setPhraseFields(string fields)
   setPhraseFields uses pf parameter */
PHP_METHOD(SolrDisMaxQuery, setPhraseFields)
{
    solr_char_t *pname = "pf";
    int pname_len = sizeof("pf")-1;
    int add_result = -1;
    solr_char_t *pvalue = NULL;
    int pvalue_len = 0;
    solr_param_t *param = NULL;
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &pvalue, &pvalue_len) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }

    /* if the parameter is registered with a different type, remove it first */
    if(solr_param_find(getThis(), pname, pname_len, &param TSRMLS_CC) == SUCCESS && param->type != SOLR_PARAM_TYPE_NORMAL)
    {
        php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Parameter %s value(s) was overwritten by this call", pname);
        solr_delete_solr_parameter(getThis(), pname, pname_len TSRMLS_CC);
    }

    add_result = solr_add_or_set_normal_param(getThis(), pname, pname_len, pvalue, pvalue_len, 0 TSRMLS_CC);

    if(add_result == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to add parameter %s", pname);
        RETURN_NULL();
    }

    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{  proto SolrDisMaxQuery SolrDisMaxQuery::setPhraseSlop(integer slop)
   sets Phrase Slop ps argument. */
PHP_METHOD(SolrDisMaxQuery, setPhraseSlop)
{
    solr_char_t *pname = (solr_char_t*) "ps";
    int pname_len = sizeof("ps")-1;
    int add_result = -1;
    solr_char_t *pvalue = NULL;
    int pvalue_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &pvalue, &pvalue_len) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }
    add_result = solr_add_or_set_normal_param(getThis(), pname, pname_len, pvalue, pvalue_len, 0 TSRMLS_CC);

    if(add_result == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter value");
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{  proto SolrDisMaxQuery SolrDisMaxQuery::setQueryPhraseSlop(integer slop)
   sets QueryPhrase Slop qs argument. */
PHP_METHOD(SolrDisMaxQuery, setQueryPhraseSlop)
{
    solr_char_t *pname = (solr_char_t*) "qs";
    int pname_len = sizeof("qs")-1;
    int add_result = -1;
    solr_char_t *pvalue = NULL;
    int pvalue_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &pvalue, &pvalue_len) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }
    add_result = solr_add_or_set_normal_param(getThis(), pname, pname_len, pvalue, pvalue_len, 0 TSRMLS_CC);

    if(add_result == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter value");
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */


/* {{{  proto SolrDisMaxQuery SolrDisMaxQuery::setBoostQuery(string q)
   sets Boost Query bq parameter. */
PHP_METHOD(SolrDisMaxQuery, setBoostQuery)
{
    solr_char_t *pname = (solr_char_t*) "bq";
    int pname_len = sizeof("bq")-1;
    int add_result = -1;
    solr_char_t *pvalue = NULL;
    int pvalue_len = 0;
    solr_param_t *param = NULL;
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &pvalue, &pvalue_len) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }

    /* if the parameter is registered with a different type, remove it first */
    if(solr_param_find(getThis(), pname, pname_len, &param TSRMLS_CC) == SUCCESS && param->type != SOLR_PARAM_TYPE_NORMAL)
    {
        php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Parameter %s value(s) was overwritten by this call", pname);
        solr_delete_solr_parameter(getThis(), pname, pname_len TSRMLS_CC);
    }

    add_result = solr_add_or_set_normal_param(getThis(), pname, pname_len, pvalue, pvalue_len, 0 TSRMLS_CC);

    if(add_result == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to add parameter %s", pname);
        RETURN_NULL();
    }

    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{ proto SolrDisMaxQuery SolrDisMaxQuery::addBoostQueryField(string field, string value [, float boost])
 * Adds a new boost query field using the bq parameter
 */
PHP_METHOD(SolrDisMaxQuery, addBoostQuery)
{
    solr_char_t *pname = (solr_char_t*) "bq";
    int pname_len = sizeof("bq")-1;
    solr_char_t *field_name = NULL;
    int field_name_len = 0;
    zval *boost = NULL;
    solr_char_t *field_value = NULL;
    int field_value_len = 0;
    solr_char_t *boost_str = NULL;
    int add_result = 0;
    char * separator = ":";
    solr_char_t *boost_separator = "^";
    solr_string_t *value_boost_str = NULL;
    solr_param_t *param = NULL;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|z", &field_name, &field_name_len, &field_value, &field_value_len, &boost) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }

    /* if the parameter is registered with a different type, remove it first */
    if(solr_param_find(getThis(), pname, pname_len, &param TSRMLS_CC) == SUCCESS && param->type != SOLR_PARAM_TYPE_ARG_LIST)
    {
        php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Parameter %s value(s) was overwritten by this call", pname);
        solr_delete_solr_parameter(getThis(), pname, pname_len TSRMLS_CC);
    }

    if(boost != NULL)
    {
        convert_to_string(boost);
        boost_str = Z_STRVAL_P(boost);
    }

    if(boost !=NULL)
    {
        value_boost_str = emalloc(sizeof(solr_string_t));
        memset(value_boost_str, 0, sizeof(solr_string_t));
        solr_string_appends(value_boost_str, field_value, field_value_len);
        solr_string_appendc(value_boost_str, *boost_separator);
        solr_string_appends(value_boost_str, boost_str, Z_STRLEN_P(boost));

        add_result = solr_add_arg_list_param(
                            getThis(),pname, pname_len, field_name, field_name_len,
                            value_boost_str->str, value_boost_str->len,' ',*separator
                            TSRMLS_CC
        );
        solr_string_free(value_boost_str);
        efree(value_boost_str);
    }else{
        add_result = solr_add_arg_list_param(
                    getThis(),pname, pname_len, field_name, field_name_len,
                    field_value, field_value_len,' ',*separator
                    TSRMLS_CC
        );
    }

    if(add_result == FAILURE)
    {
        RETURN_NULL();
    }

    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{  proto SolrDisMaxQuery SolrDisMaxQuery::removeBoostQuery(string field)
   Removes a sort field from the sort parameter. */
PHP_METHOD(SolrDisMaxQuery, removeBoostQuery)
{
    solr_char_t *pname = (solr_char_t*) "bq";
    int pname_len = sizeof("bq")-1;
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
    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{  proto SolrDisMaxQuery SolrDisMaxQuery::setBoostFunction(string function)
   sets Boost Query bf parameter. */
PHP_METHOD(SolrDisMaxQuery, setBoostFunction)
{
    solr_char_t *pname = (solr_char_t*) "bf";
    int pname_len = sizeof("bf")-1;
    int add_result = -1;
    solr_char_t *pvalue = NULL;
    int pvalue_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &pvalue, &pvalue_len) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }

    add_result = solr_add_or_set_normal_param(getThis(), pname, pname_len, pvalue, pvalue_len, 0 TSRMLS_CC);

    if(add_result == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to add parameter %s", pname);
        RETURN_NULL();
    }

    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{  proto SolrDisMaxQuery SolrDisMaxQuery::setMinimumMatch(string value)
   sets Minimum Match (mm) parameter. */
PHP_METHOD(SolrDisMaxQuery, setMinimumMatch)
{
    solr_char_t *pname = (solr_char_t*) "mm";
    int pname_len = sizeof("mm")-1;
    int add_result = -1;
    solr_char_t *pvalue = NULL;
    int pvalue_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &pvalue, &pvalue_len) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }

    add_result = solr_add_or_set_normal_param(getThis(), pname, pname_len, pvalue, pvalue_len, 0 TSRMLS_CC);

    if(add_result == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to add parameter %s", pname);
        RETURN_NULL();
    }

    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{  proto SolrDisMaxQuery SolrDisMaxQuery::setTieBreaker(float tieBreaker)
   sets Tie Breaker (tie) parameter. */
PHP_METHOD(SolrDisMaxQuery, setTieBreaker)
{
    solr_char_t *pname = (solr_char_t*) "tie";
    int pname_len = sizeof("tie")-1;
    int add_result = -1;
    solr_char_t *pvalue = NULL;
    int pvalue_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &pvalue, &pvalue_len) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }

    add_result = solr_add_or_set_normal_param(getThis(), pname, pname_len, pvalue, pvalue_len, 0 TSRMLS_CC);

    if(add_result == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to add parameter %s", pname);
        RETURN_NULL();
    }

    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{ proto SolrDisMaxQuery SolrDisMaxQuery::setBigramPhraseFields(string bigramFields)
   setBigramPhraseFields uses pf2 parameter */
PHP_METHOD(SolrDisMaxQuery, setBigramPhraseFields)
{
    solr_char_t *pname = "pf2";
    int pname_len = sizeof("pf2")-1;
    solr_char_t *param_value = NULL;
    int param_value_len = 0;
    int set_param_return = 0;
    solr_param_t *param = NULL;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_len) == FAILURE){
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameters");
        RETURN_NULL();
    }

    /* if the parameter is registered with a different type, remove it first */
    if(solr_param_find(getThis(), pname, pname_len, &param TSRMLS_CC) == SUCCESS && param->type != SOLR_PARAM_TYPE_NORMAL)
    {
        php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Parameter %s value(s) was overwritten by this call", pname);
        solr_delete_solr_parameter(getThis(), pname, pname_len TSRMLS_CC);
    }

    set_param_return = solr_add_or_set_normal_param(getThis(), pname, pname_len, param_value, param_value_len, 0 TSRMLS_CC);
    if(set_param_return == FAILURE)
    {
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */


/* {{{ proto SolrDisMaxQuery SolrDisMaxQuery::addBigramPhraseField(string field, float boost [, float slop])
 * Adds a new bigram phrase field (pf2) to the list of fields
 */
PHP_METHOD(SolrDisMaxQuery, addBigramPhraseField)
{
    solr_char_t *field_name = NULL;
    int field_name_len = 0;
    zval *boost = NULL;
    zval *slop = NULL;
    int add_result = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sz|z", &field_name, &field_name_len, &boost, &slop) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }
    add_result = add_phrase_field(getThis(), "pf2", boost, slop, field_name, field_name_len TSRMLS_CC);

    if(add_result == FAILURE)
    {
        RETURN_NULL();
    }

    SOLR_RETURN_THIS();
}
/* }}} */


/* {{{  proto SolrDisMaxQuery SolrDisMaxQuery::removeQueryField(string field)
   Removes a bigram phrase field. */
PHP_METHOD(SolrDisMaxQuery, removeBigramPhraseField)
{
    solr_char_t *pname = (solr_char_t*) "pf2";
    int pname_len = sizeof("pf2")-1;
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
    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{  proto SolrDisMaxQuery SolrDisMaxQuery::setBigramPhraseSlop(integer slop)
   sets Bigram Phrase Slop ps argument. */
PHP_METHOD(SolrDisMaxQuery, setBigramPhraseSlop)
{
    solr_char_t *pname = (solr_char_t*) "ps2";
    int pname_len = sizeof("ps2")-1;
    int add_result = -1;
    solr_char_t *pvalue = NULL;
    int pvalue_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &pvalue, &pvalue_len) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }
    add_result = solr_add_or_set_normal_param(getThis(), pname, pname_len, pvalue, pvalue_len, 0 TSRMLS_CC);

    if(add_result == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter value");
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */


/* {{{ proto SolrDisMaxQuery SolrDisMaxQuery::setTrigramPhraseFields(string fields)
   setTrigramPhraseFields uses pf3 parameter */
PHP_METHOD(SolrDisMaxQuery, setTrigramPhraseFields)
{
    solr_char_t *pname = "pf3";
    int pname_len = sizeof("pf3")-1;
    solr_char_t *param_value = NULL;
    int param_value_len = 0;
    int set_param_return = 0;
    solr_param_t *param = NULL;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_len) == FAILURE){
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameters");
        RETURN_NULL();
    }

    /* if the parameter is registered with a different type, remove it first */
    if(solr_param_find(getThis(), pname, pname_len, &param TSRMLS_CC) == SUCCESS && param->type != SOLR_PARAM_TYPE_NORMAL)
    {
        php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Parameter %s value(s) was overwritten by this call", pname);
        solr_delete_solr_parameter(getThis(), pname, pname_len TSRMLS_CC);
    }

    set_param_return = solr_add_or_set_normal_param(getThis(), pname, pname_len, param_value, param_value_len, 0 TSRMLS_CC);
    if(set_param_return == FAILURE)
    {
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */


/* {{{ proto SolrDisMaxQuery SolrDisMaxQuery::addTrigramPhraseField(string field, float boost [, float slop])
 * Adds a new trigram phrase field (pf3) to the list of fields
 */
PHP_METHOD(SolrDisMaxQuery, addTrigramPhraseField)
{
    solr_char_t *field_name = NULL;
    int field_name_len = 0;
    zval *boost = NULL;
    zval *slop = NULL;
    int add_result = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sz|z", &field_name, &field_name_len, &boost, &slop) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }
    add_result = add_phrase_field(getThis(), "pf3", boost, slop, field_name, field_name_len TSRMLS_CC);

    if(add_result == FAILURE)
    {
        RETURN_NULL();
    }

    SOLR_RETURN_THIS();
}
/* }}} */


/* {{{  proto SolrDisMaxQuery SolrDisMaxQuery::removeQueryField(string field)
   Removes a trigram phrase field. */
PHP_METHOD(SolrDisMaxQuery, removeTrigramPhraseField)
{
    solr_char_t *pname = (solr_char_t*) "pf3";
    int pname_len = sizeof("pf3")-1;
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
    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{  proto SolrDisMaxQuery SolrDisMaxQuery::setTrigramPhraseSlop(integer slop)
   sets Trigram Phrase Slop ps3 argument. */
PHP_METHOD(SolrDisMaxQuery, setTrigramPhraseSlop)
{
    solr_char_t *pname = (solr_char_t*) "ps3";
    int pname_len = sizeof("ps3")-1;
    int add_result = -1;
    solr_char_t *pvalue = NULL;
    int pvalue_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &pvalue, &pvalue_len) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }
    add_result = solr_add_or_set_normal_param(getThis(), pname, pname_len, pvalue, pvalue_len, 0 TSRMLS_CC);

    if(add_result == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameter value");
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */


/* {{{  proto SolrDisMaxQuery SolrDisMaxQuery::addUserField(string field)
   Adds a userfield rule to uf parameter. */
PHP_METHOD(SolrDisMaxQuery, addUserField)
{
    solr_char_t *pname = (solr_char_t*) "uf";
    int pname_len = sizeof("uf")-1;
    int add_result = -1;
    solr_char_t *pvalue = NULL;
    int pvalue_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &pvalue, &pvalue_len) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }
    add_result = solr_add_simple_list_param_ex(getThis(), pname, pname_len, pvalue, pvalue_len, " " TSRMLS_CC);

    if(add_result == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to add user field: Invalid parameter value");
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */

/* {{{  proto SolrDisMaxQuery SolrDisMaxQuery::removeUserField(string field)
   Removes a userfield rule from uf parameter. */
PHP_METHOD(SolrDisMaxQuery, removeUserField)
{
    solr_char_t *pname = (solr_char_t*) "uf";
    int pname_len = sizeof("uf")-1;
    solr_char_t *field_name = NULL;
    int field_name_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &field_name, &field_name_len) == FAILURE)
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid parameters");
        RETURN_NULL();
    }

    solr_delete_simple_list_param_value(getThis(), pname, pname_len, field_name, field_name_len TSRMLS_CC);

    SOLR_RETURN_THIS();
}
/* }}} */


/* {{{ proto SolrDisMaxQuery SolrDisMaxQuery::setUserFields(string fields)
   Sets user fields (uf parameter) */
PHP_METHOD(SolrDisMaxQuery, setUserFields)
{
    solr_char_t *pname = "uf";
    int pname_len = sizeof("uf")-1;
    solr_char_t *param_value = NULL;
    int param_value_len = 0;
    int set_param_return = 0;
    solr_param_t *param = NULL;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &param_value, &param_value_len) == FAILURE){
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid parameters");
        RETURN_NULL();
    }

    /* if the parameter is registered with a different type, remove it first */
    if(solr_param_find(getThis(), pname, pname_len, &param TSRMLS_CC) == SUCCESS && param->type != SOLR_PARAM_TYPE_NORMAL)
    {
        php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Parameter %s value(s) was overwritten by this call", pname);
        solr_delete_solr_parameter(getThis(), pname, pname_len TSRMLS_CC);
    }

    set_param_return = solr_add_or_set_normal_param(getThis(), pname, pname_len, param_value, param_value_len, 0 TSRMLS_CC);
    if(set_param_return == FAILURE)
    {
        RETURN_NULL();
    }
    SOLR_RETURN_THIS();
}
/* }}} */


int add_phrase_field(zval *obj, solr_char_t *pname, zval *boost, zval *slop, solr_char_t *field_name, int field_name_len TSRMLS_DC)
{
    int pname_len = strlen(pname);
    int add_result = 0;
    solr_char_t *boost_str = NULL;
    solr_char_t *slop_str = NULL;
    char * separator = "^";
    solr_char_t * delimiter_override = "";

    solr_string_t boost_slop_buffer;
    if(boost != NULL)
    {
        convert_to_string(boost);
        boost_str = Z_STRVAL_P(boost);
    }

    if (slop != NULL) {
        convert_to_string(slop);
        slop_str = Z_STRVAL_P(slop);
    }

    if (slop != NULL && boost !=NULL)
    {
        delimiter_override = "~";
        memset(&boost_slop_buffer, 0, sizeof(solr_string_t));
        solr_string_appends(&boost_slop_buffer, (solr_char_t *)slop_str , Z_STRLEN_P(slop));
        solr_string_appendc(&boost_slop_buffer, '^');
        solr_string_appends(&boost_slop_buffer, boost_str , Z_STRLEN_P(boost));
        add_result = solr_add_arg_list_param_ex(
                obj, pname, pname_len, field_name, field_name_len,
                boost_slop_buffer.str, boost_slop_buffer.len, ' ', *separator,
                *delimiter_override TSRMLS_CC
        );

        solr_string_free(&boost_slop_buffer);
    } else {
        add_result = solr_add_arg_list_param(
                obj, pname, pname_len, field_name, field_name_len,
                boost_str, Z_STRLEN_P(boost),' ',*separator
                TSRMLS_CC
        );
    }
    return add_result;
}

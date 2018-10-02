#ifndef PHP_7

PHPAPI extern zend_string *compat_php_base64_decode(const unsigned char * str, int length)
{
    int ret_length = 0L;
    unsigned char * return_str = php_base64_decode(str, length, &ret_length);
    return zend_string_init(return_str, ret_length, 1);
}

PHPAPI extern int compat_php_var_unserialize(zval *rval, const unsigned char **p, const unsigned char *max, php_unserialize_data_t *var_hash TSRMLS_DC)
{
    return php_var_unserialize(&rval, p, max, var_hash TSRMLS_CC);
}

#else
#define compat_php_base64_decode php_base64_decode
#define compat_php_var_unserialize php_var_unserialize
#endif

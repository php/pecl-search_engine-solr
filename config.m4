
dnl $Id$

dnl config.m4 for the solr extension

dnl Configuring the CURL external library
dnl This folder is the grand-parent folder of easy.h
PHP_ARG_WITH(curl, for cURL support, [  --with-curl[=DIR]		SOLR : libcurl install prefix])

if test -r $PHP_CURL/include/curl/easy.h; then
	CURL_DIR=$PHP_CURL
	AC_MSG_RESULT(curl headers found in $PHP_CURL)
else
	AC_MSG_CHECKING(for cURL in default path)
	for i in /usr/local /usr; do
	  	if test -r $i/include/curl/easy.h; then
			CURL_DIR=$i
			AC_MSG_RESULT(found in $i)
			break
	  	fi
	done
fi

if test -z "$CURL_DIR"; then
	AC_MSG_RESULT(not found)
	AC_MSG_ERROR([Please reinstall the libcurl distribution -
	easy.h should be in <curl-dir>/include/curl/])
fi

CURL_CONFIG="curl-config"
AC_MSG_CHECKING(for cURL 7.15.0 or greater)

if ${CURL_DIR}/bin/curl-config --libs > /dev/null 2>&1; then
	CURL_CONFIG=${CURL_DIR}/bin/curl-config
else
	if ${CURL_DIR}/curl-config --libs > /dev/null 2>&1; then
  		CURL_CONFIG=${CURL_DIR}/curl-config
	fi
fi

curl_version_full=`$CURL_CONFIG --version`
curl_version=`echo ${curl_version_full} | sed -e 's/libcurl //' | $AWK 'BEGIN { FS = "."; } { printf "%d", ($1 * 1000 + $2) * 1000 + $3;}'`

if test "$curl_version" -ge 7015000; then
	AC_MSG_RESULT($curl_version_full)
	CURL_LIBS=`$CURL_CONFIG --libs`
else
	AC_MSG_ERROR([The Solr extension does not support libcurl libraries < 7.15.0. Please update your libraries])
fi

PHP_ARG_ENABLE(solr, whether to enable the Solr extension,
[  --enable-solr         Enable solr support])

PHP_ARG_ENABLE(solr-debug, whether to compile with solr in verbose mode,
[  --enable-solr-debug          Compile with solr in verbose mode], no, no)

dnl Configuring the LibXML external Library
if test -z "$PHP_LIBXML_DIR"; then
  PHP_ARG_WITH(libxml-dir, libxml2 install dir,
  [  --with-libxml-dir=[DIR]     SOLR : libxml2 install prefix], no, no)
fi

PHP_ARG_ENABLE(coverage, whether to enable code coverage,
    [  --enable-coverage Enable developer code coverage information],, no)

dnl Setting up the apache Solr extension
if test "$PHP_SOLR" != "no"; then

	if test "$PHP_CURL" = "no"; then   
        AC_MSG_ERROR([Solr extension requires curl extension, add --with-curl])                
    fi
	
	PHP_CHECK_LIBRARY(curl,curl_easy_perform, 
    [ 
        AC_DEFINE(HAVE_CURL,1,[ ])
    ],[
        AC_MSG_ERROR(There is something wrong. Please check config.log for more information.)
    ],[
        $CURL_LIBS -L$CURL_DIR/$PHP_LIBDIR
    ])
    
    PHP_ADD_INCLUDE($CURL_DIR/include)
    PHP_EVAL_LIBLINE($CURL_LIBS, SOLR_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(curl, $CURL_DIR/lib, SOLR_SHARED_LIBADD)
  
	if test "$PHP_LIBXML" = "no"; then   
        AC_MSG_ERROR([Solr extension requires LIBXML extension, add --enable-libxml])                
	fi
	
	AC_MSG_CHECKING(for JSON)
    if test -f "$phpincludedir/ext/json/php_json.h" || test "$HAVE_JSON" != "no"; then
        AC_DEFINE(HAVE_JSON, 1, [JSON support])
        AC_MSG_RESULT(Yes)
    else
        AC_MSG_ERROR([Solr extension requires json or jsonc support])
    fi

	PHP_SETUP_LIBXML(SOLR_SHARED_LIBADD, [
    AC_DEFINE(HAVE_SOLR, 1,[Setting the value of HAVE_SOLR to 1 ])
    
    if test "$PHP_SOLR_DEBUG" != "no"; then
       AC_DEFINE(SOLR_DEBUG, 1,     [Setting the value of SOLR_DEBUG to 1 ])
    else
       AC_DEFINE(SOLR_DEBUG_OFF, 1, [Setting the value of SOLR_DEBUG_OFF to 1 ])
    fi
    
    if test "$PHP_COVERAGE" = "yes"; then
        PHP_CHECK_GCC_ARG(-fprofile-arcs,                     COVERAGE_CFLAGS="$COVERAGE_CFLAGS -fprofile-arcs")
        PHP_CHECK_GCC_ARG(-ftest-coverage,                    COVERAGE_CFLAGS="$COVERAGE_CFLAGS -ftest-coverage")
        EXTRA_LDFLAGS="$COVERAGE_CFLAGS"
    fi
    
    
    export OLD_CPPFLAGS="$CPPFLAGS"
    export CPPFLAGS="$CPPFLAGS $INCLUDES"
    
    AC_MSG_CHECKING(PHP version)
    
    AC_TRY_COMPILE([
    #include <php_version.h>
    ],[
#if PHP_MAJOR_VERSION > 5
#error PHP > 5
#endif
    ],[
    subdir=src/php5
    AC_MSG_RESULT([PHP 5])
    ],[
    subdir=src/php7
    AC_MSG_RESULT([PHP 7])
    ])
    
    
    PHP_SOLR_SRC_FILES="$subdir/php_solr.c \
                             $subdir/php_solr_object.c \
                             $subdir/php_solr_document.c \
                             $subdir/php_solr_input_document.c \
                             $subdir/php_solr_client.c \
                             $subdir/php_solr_params.c \
                             $subdir/php_solr_query.c \
                             $subdir/php_solr_response.c \
                             $subdir/php_solr_exception.c \
                             $subdir/php_solr_utils.c \
                             $subdir/php_solr_dismax_query.c \
                             $subdir/php_solr_collapse_function.c \
                             $subdir/solr_string.c \
                             $subdir/solr_functions_document.c \
                             $subdir/solr_functions_client.c \
                             $subdir/solr_functions_helpers.c \
                             $subdir/solr_functions_params.c \
                             $subdir/solr_functions_response.c \
                             $subdir/solr_functions_debug.c"
                             
    PHP_NEW_EXTENSION(solr, $PHP_SOLR_SRC_FILES, 
    						 $ext_shared,, [$COVERAGE_CFLAGS])
    PHP_ADD_BUILD_DIR($abs_builddir/$subdir, 1)
    PHP_SUBST(SOLR_SHARED_LIBADD)
  ], [
    AC_MSG_ERROR([xml2-config not found. Please check your libxml2 installation.])
  ])
fi



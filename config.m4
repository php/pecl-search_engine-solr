
dnl $Id: config.m4 298824 2010-04-30 21:36:26Z iekpo $

dnl config.m4 for the solr extension

AC_ARG_ENABLE(solr-debug,
[  --enable-solr-debug          Compile with solr in verbose mode],[
  AC_DEFINE(SOLR_DEBUG, 1,	[Setting the value of SOLR_DEBUG to 1 ])
],[
  AC_DEFINE(SOLR_DEBUG_OFF, 1,	[Setting the value of SOLR_DEBUG_OFF to 1 ])
])

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

PHP_ADD_INCLUDE($CURL_DIR/include)
PHP_EVAL_LIBLINE($CURL_LIBS, CURL_SHARED_LIBADD)
PHP_ADD_LIBRARY_WITH_PATH(curl, $CURL_DIR/$PHP_LIBDIR, CURL_SHARED_LIBADD)

PHP_ARG_ENABLE(solr, whether to enable the Solr extension,
[  --enable-solr         Enable solr support])

dnl Configuring the LibXML external Library
if test -z "$PHP_LIBXML_DIR"; then
  PHP_ARG_WITH(libxml-dir, libxml2 install dir,
  [  --with-libxml-dir=[DIR]     SOLR : libxml2 install prefix], no, no)
fi

dnl Setting up the apache Solr extension
if test "$PHP_SOLR" != "no"; then

	if test "$PHP_CURL" = "no"; then   
    	AC_MSG_ERROR([SOAP extension requires curl extension, add --with-curl])                
	fi
  
	if test "$PHP_LIBXML" = "no"; then   
    	AC_MSG_ERROR([SOAP extension requires LIBXML extension, add --enable-libxml])                
	fi

	PHP_SETUP_LIBXML(SOLR_SHARED_LIBADD, [
    AC_DEFINE(HAVE_SOLR, 1,[Setting the value of HAVE_SOLR to 1 ])
    
    PHP_NEW_EXTENSION(solr, [php_solr.c \
    						 php_solr_object.c \
    						 php_solr_document.c \
    						 php_solr_input_document.c \
    						 php_solr_client.c \
    						 php_solr_params.c \
    						 php_solr_query.c \
    						 php_solr_response.c \
    						 php_solr_exception.c \
    						 php_solr_utils.c \
    						 solr_string.c \
    						 solr_functions_document.c \
    						 solr_functions_client.c \
                             solr_functions_helpers.c \
                             solr_functions_params.c \
                             solr_functions_response.c \
    						 solr_functions_debug.c], 
    						 $ext_shared)
    PHP_SUBST(SOAP_SHARED_LIBADD)
  ], [
    AC_MSG_ERROR([xml2-config not found. Please check your libxml2 installation.])
  ])
fi

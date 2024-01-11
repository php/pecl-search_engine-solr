dnl config.m4 for the solr extension

PHP_ARG_ENABLE(solr, whether to enable the Solr extension,
[  --enable-solr         Enable solr support])

PHP_ARG_ENABLE(solr-debug, whether to compile with solr in verbose mode,
[  --enable-solr-debug          Compile with solr in verbose mode], no, no)

PHP_ARG_ENABLE(coverage, whether to enable code coverage,
    [  --enable-coverage Enable developer code coverage information],, no)

dnl Setting up the apache Solr extension
if test "$PHP_SOLR" != "no"; then

    AC_PATH_PROG(PKG_CONFIG, pkg-config, no)

    AC_MSG_CHECKING(for libcurl)
    if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists libcurl; then
      if $PKG_CONFIG libcurl --atleast-version 7.15.5; then
        CURL_CFLAGS=`$PKG_CONFIG libcurl --cflags`
        CURL_LIBS=`$PKG_CONFIG libcurl --libs`
        CURL_VERSON=`$PKG_CONFIG libcurl --modversion`
        AC_MSG_RESULT(from pkgconfig: version $CURL_VERSON found)
      else
        AC_MSG_ERROR(system libcurl must be upgraded to version >= 7.15.5)
      fi
    else
      AC_MSG_ERROR(pkg-config or libcurl not found)
    fi

	PHP_CHECK_LIBRARY(curl,curl_easy_perform,
    [
        AC_DEFINE(HAVE_CURL,1,[ ])
    ],[
        AC_MSG_ERROR(There is something wrong. Please check config.log for more information.)
    ],[
        $CURL_LIBS
    ])

    PHP_EVAL_INCLINE($CURL_CFLAGS)
    PHP_EVAL_LIBLINE($CURL_LIBS, SOLR_SHARED_LIBADD)

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

    dnl until PHP 7.3: xml2-config or pkg-config
    dnl since PHP 7.4: pkg-config only
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

    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
    #include <php_version.h>
    ]], [[
#if PHP_MAJOR_VERSION > 5
#error PHP > 5
#endif
    ]])],[
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
                             $subdir/php_solr_extract.c \
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

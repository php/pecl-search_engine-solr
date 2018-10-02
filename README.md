pecl-search_engine-solr
=======================

[![Build Status](https://travis-ci.org/php/pecl-search_engine-solr.svg?branch=master)](https://travis-ci.org/php/pecl-search_engine-solr)
[![Coverage Status](https://coveralls.io/repos/github/php/pecl-search_engine-solr/badge.svg?branch=master)](https://coveralls.io/github/php/pecl-search_engine-solr?branch=master)

The Apache Solr PHP extension is an extremely fast, light-weight, feature-rich library that allows PHP applications to communicate easily and efficiently with Apache Solr server instances using an object-oriented API.

http://pecl.php.net/package/solr


Please refer to http://www.php.net/manual/en/book.solr.php and README.* for more information


Installation
------------

This library requires curl and libxml2 development packages and php extensions

For Debian/Ubuntu/Mint

```bash
    sudo apt-get install php5-curl libcurl4-gnutls-dev libxml2 libxml2-dev
```
For RHEL/Fedora/CentOS/Scientific linux
```bash
    sudo yum install libxml2-devel curl-devel php-curl
```


Please make sure to install them before proceeding to the compilation process
```bash
    phpize
    ./configure
    make
    make test
    sudo make install
```

more details on README.INSTALLATION

Contributions
-------------
All forms of contributions are welcome! Whether contributing to tests, or the source.

Running Tests
-------------
Types of tests

1. Tests that do not require a Solr Server (some of them use fixture files)
2. Requires a running server with cores present and populated with data.

There is a configuration file for the test suite, located at tests/test.config.inc
It contains the fixture file definitions and other configurations for the Solr Server to be used for testing.

To run the type 2 tests, you'll need docker to run the test server using the following command:

```docker run -p 8983:8983 --name solr5 -t omars/solr53```

PHPQA Guide: http://qa.php.net/write-test.php


``` make test ```

How to Report Bugs
------------------

Please report bugs to http://bugs.php.net

If you experience a crash due to a segmentation fault, please follow the instructions on the link below
to get a gdb backtrace and then submit the trace in your bug report as well

http://bugs.php.net/bugs-generating-backtrace.php

Thank you for using PHP

pecl-search_engine-solr
=======================


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
    
How to Report Bugs
------------------

Please report bugs to http://bugs.php.net

If you experience a crash due to a segmentation fault, please follow the instructions on the link below 
to get a gdb backtrace and then submit the trace in your bug report as well

http://bugs.php.net/bugs-generating-backtrace.php

Thank you for using PHP

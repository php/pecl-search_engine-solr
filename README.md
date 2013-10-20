php-solr2
=========

PHP Solr PECL extension for Solr 4.


This project aims to continue solr extension development since it was abandoned a while ago, and Solr's Team is working rapidly with alot of new brilliant features so it's necessary to adapt to changes.


Forked from [PHP Solr 1.0.2 pecl extension] ( http://pecl.php.net/package/solr )


Please refer to docs/documentation.php for changes and additions in the extensions's API


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
  
    

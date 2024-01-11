pecl package package.xml
pecl install ./solr-2.7.0.tgz
echo "extension=solr.so" > /usr/local/etc/php/conf.d/solr.ini
php -m | grep solr
bash
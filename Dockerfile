FROM php:7.2-apache

RUN apt update && apt install libxml2-dev libcurl4-gnutls-dev --yes

RUN apt install  vim --yes

COPY . /opt/solr2

WORKDIR /opt/solr2
RUN pear package package.xml
RUN pecl install solr-2.5.0.tgz

RUN echo "extension=solr.so" > /usr/local/etc/php/conf.d/solr.ini

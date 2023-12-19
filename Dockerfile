FROM php:8.2.11-cli-alpine3.17

RUN apt update && apt install libxml2-dev libcurl4-gnutls-dev --yes

RUN apt install  vim --yes

COPY .docker/entrypoint.sh /opt/

RUN mkdir /opt/solr2

WORKDIR /opt/solr2

ENTRYPOINT ["sh","/opt/entrypoint.sh"]
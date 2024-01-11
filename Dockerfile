FROM php:8.3-cli

RUN apt update && apt install libxml2-dev libcurl4-gnutls-dev --yes

RUN apt install  vim --yes

COPY .docker/entrypoint.sh /opt/

RUN mkdir /opt/solr2

COPY ./ /opt/solr2

WORKDIR /opt/solr2

ENTRYPOINT ["sh","/opt/entrypoint.sh"]

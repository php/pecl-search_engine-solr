FROM php:8.4-cli-alpine3.20

RUN apk add --no-cache libxml2-dev libcurl-dev \
    && docker-php-ext-install xml curl \
    && rm -rf /var/cache/apk/*

RUN apk add --no-cache vim \
    && rm -rf /var/cache/apk/*

COPY .docker/entrypoint.sh /opt/

RUN mkdir /opt/solr2

COPY ./ /opt/solr2

WORKDIR /opt/solr2

ENTRYPOINT ["sh","/opt/entrypoint.sh"]
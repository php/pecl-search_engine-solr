FROM solr:7-slim

USER root

RUN apt-get update && \
    apt-get install -y --no-install-recommends curl && \
    rm -rf /var/lib/apt/lists/*

COPY collections /opt/solr-configs

COPY --chmod=755 init-solr.sh /docker-entrypoint-initdb.d/init-solr.sh

USER solr
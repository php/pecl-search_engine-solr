FROM solr:9.10.0-slim

COPY collections /opt/solr-configs

COPY --chmod=755 init-solr.sh /docker-entrypoint-initdb.d/init-solr.sh
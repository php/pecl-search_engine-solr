FROM bitnami/solr:9.8.1

COPY collections collections

RUN solr start &&\
    solr create -c collection1 &&\
    solr create -c metal_store &&\
    solr create -c myfiles &&\
    curl 'http://localhost:8983/solr/collection1/update/json?commit=true' --data-binary @collections/collection1.json -H 'Content-type:application/json' &&\
    curl 'http://localhost:8983/solr/metal_store/update/json?commit=true' --data-binary @collections/metal_store.json -H 'Content-type:application/json' &&\
    solr stop

#!/bin/bash
set -e

echo "Starting temporary Solr server for initialization..."
solr start

echo "Solr server is running. Creating collections with default configs..."

solr create -c collection1
solr create -c metal_store
solr create -c myfiles

echo "Collections created. Indexing data..."

curl 'http://localhost:8983/solr/collection1/update/json?commit=true' --data-binary @/opt/solr-configs/collection1.json -H 'Content-type:application/json'
curl 'http://localhost:8983/solr/metal_store/update/json?commit=true' --data-binary @/opt/solr-configs/metal_store.json -H 'Content-type:application/json'

echo "Data indexed. Stopping temporary Solr server..."
solr stop
echo "Solr initialization complete."
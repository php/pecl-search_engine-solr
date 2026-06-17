#!/bin/bash
set -e

echo "Starting temporary Solr server for initialization..."
solr start
echo "Solr server is running."

create_and_index() {
  CORE_NAME=$1
  DATA_FILE=$2

  echo "Checking if core '$CORE_NAME' exists..."

  if curl -s "http://localhost:8983/solr/admin/cores?action=STATUS&core=$CORE_NAME" | grep -q "uptime"; then
    echo "Core '$CORE_NAME' already exists. Skipping creation and indexing."
  else
    echo "Core '$CORE_NAME' not found. Creating..."

    # Force use of the common strict configset (schema-full not schemaless)
    solr create -c "$CORE_NAME" -d /opt/solr/server/solr/configsets/sample_techproducts_configs/conf

    if [ -n "$DATA_FILE" ] && [ -f "$DATA_FILE" ]; then
      echo "Indexing data for '$CORE_NAME' from $DATA_FILE..."
      curl "http://localhost:8983/solr/$CORE_NAME/update/json?commit=true" --data-binary @"$DATA_FILE" -H 'Content-type:application/json'
    else
      echo "No data file provided or found for '$CORE_NAME'. Skipping indexing."
    fi
  fi
}

create_and_index "collection1" "/opt/solr-configs/collection1.json"
create_and_index "metal_store" "/opt/solr-configs/metal_store.json"

create_and_index "myfiles" ""

echo "Data initialization finished. Stopping temporary Solr server..."
solr stop
echo "Solr initialization complete."
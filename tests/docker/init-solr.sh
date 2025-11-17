#!/bin/bash
set -e

echo "Starting temporary Solr server for initialization..."
solr start
echo "Solr server is running."

create_and_index() {
  COLLECTION_NAME=$1
  DATA_FILE=$2

  echo "Checking if collection '$COLLECTION_NAME' exists..."

  if curl -s "http://localhost:8983/solr/admin/collections?action=LIST" | grep -q "\"$COLLECTION_NAME\""; then
    echo "Collection '$COLLECTION_NAME' already exists. Skipping creation and indexing."
  else
    echo "Collection '$COLLECTION_NAME' not found. Creating..."
    solr create -c "$COLLECTION_NAME"

    if [ -n "$DATA_FILE" ] && [ -f "$DATA_FILE" ]; then
      echo "Indexing data for '$COLLECTION_NAME' from $DATA_FILE..."
      curl "http://localhost:8983/solr/$COLLECTION_NAME/update/json?commit=true" --data-binary @"$DATA_FILE" -H 'Content-type:application/json'
    else
      echo "No data file provided or found for '$COLLECTION_NAME'. Skipping indexing."
    fi
  fi
}

create_and_index "collection1" "/opt/solr-configs/collection1.json"
create_and_index "metal_store" "/opt/solr-configs/metal_store.json"

echo "Data initialization finished. Stopping temporary Solr server..."
solr stop
echo "Solr initialization complete."
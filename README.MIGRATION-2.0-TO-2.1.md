Migrating from PECL Solr 2.0 to PECL Solr 2.1
=============================================

If you are using json Response Writer:
Version 2.0 and 1.*
```php
$result = $client->query($query);
$result->getResponse();
// ^ SolrResponse::getResponse() returns an array
```

Version 2.1:
```php
SolrResponse::getResponse() returns a SolrObject
```

You can still get an array from the SolrResponse object but by using SolrResponse::getArrayResponse()

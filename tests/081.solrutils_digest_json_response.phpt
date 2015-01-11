--TEST--
SolrUtils::digestJsonResponse() - Testing Lucene Reserved Characters
--FILE--
<?php
$responseString = '
{
  "responseHeader":{
    "status":0,
    "QTime":1,
    "params":{
      "indent":"on",
      "wt":"json",
      "q":"lucene",
      "version":"2.2"}},
  "response":{"numFound":1,"start":0,"docs":[
      {
        "id":"SOLR1000",
        "name":"Solr, the Enterprise Search Server",
        "manu":"Apache Software Foundation",
        "cat":["software",
          "search"],
        "features":["Advanced Full-Text Search Capabilities using Lucene",
          "Optimized for High Volume Web Traffic",
          "Standards Based Open Interfaces - XML and HTTP",
          "Comprehensive HTML Administration Interfaces",
          "Scalability - Efficient Replication to other Solr Search Servers",
          "Flexible and Adaptable with XML configuration and Schema",
          "Good unicode support: hello (hello with an accent over the e)"],
        "price":0.0,
        "price_c":"0,USD",
        "popularity":10,
        "inStock":true,
        "incubationdate_dt":"2006-01-17T00:00:00Z",
        "_version_":1460602453694087168}]
  }}';
$response = SolrUtils::digestJsonResponse($responseString);
var_dump($response instanceof SolrObject);
?>
--EXPECTF--
bool(true)
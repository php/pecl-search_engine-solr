--TEST--
SolrUtils::digestJsonResponse() - Digest JSON Response
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
if (!json_decode($responseString)) {
	echo "PHP JSON DECODE failed with: ". json_last_error_msg().PHP_EOL;
}
$response = SolrUtils::digestJsonResponse($responseString);
var_dump($response instanceof SolrObject);
var_dump($response);
var_dump($response->response->docs[0]->_version_ == 1460602453694087168);
?>
--EXPECTF--
bool(true)
object(SolrObject)#%d (2) {
  ["responseHeader"]=>
  object(SolrObject)#4 (3) {
    ["status"]=>
    int(0)
    ["QTime"]=>
    int(1)
    ["params"]=>
    object(SolrObject)#5 (4) {
      ["indent"]=>
      string(2) "on"
      ["wt"]=>
      string(4) "json"
      ["q"]=>
      string(6) "lucene"
      ["version"]=>
      string(3) "2.2"
    }
  }
  ["response"]=>
  object(SolrObject)#%d (3) {
    ["numFound"]=>
    int(1)
    ["start"]=>
    int(0)
    ["docs"]=>
    array(1) {
      [0]=>
      object(SolrObject)#%d (11) {
        ["id"]=>
        string(8) "SOLR1000"
        ["name"]=>
        string(34) "Solr, the Enterprise Search Server"
        ["manu"]=>
        string(26) "Apache Software Foundation"
        ["cat"]=>
        array(2) {
          [0]=>
          string(8) "software"
          [1]=>
          string(6) "search"
        }
        ["features"]=>
        array(7) {
          [0]=>
          string(51) "Advanced Full-Text Search Capabilities using Lucene"
          [1]=>
          string(37) "Optimized for High Volume Web Traffic"
          [2]=>
          string(46) "Standards Based Open Interfaces - XML and HTTP"
          [3]=>
          string(44) "Comprehensive HTML Administration Interfaces"
          [4]=>
          string(64) "Scalability - Efficient Replication to other Solr Search Servers"
          [5]=>
          string(56) "Flexible and Adaptable with XML configuration and Schema"
          [6]=>
          string(61) "Good unicode support: hello (hello with an accent over the e)"
        }
        ["price"]=>
        float(0)
        ["price_c"]=>
        string(5) "0,USD"
        ["popularity"]=>
        int(10)
        ["inStock"]=>
        bool(true)
        ["incubationdate_dt"]=>
        string(20) "2006-01-17T00:00:00Z"
        ["_version_"]=>
        %s
      }
    }
  }
}
bool(true)
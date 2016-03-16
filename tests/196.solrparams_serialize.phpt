--TEST--
SolrParams::serialize() - serialize params
--FILE--
<?php

$params = new SolrModifiableParams();

$params
	->setParam('q', 'lucene')
	->setParam('start', 0)
	->setParam('rows', 10)
	->addParam('fq', 'popularity:[10 TO *]')
	->addParam('fq', 'section:0')
;

echo serialize($params);
?>
--EXPECTF--
C:20:"SolrModifiableParams":727:{<?xml version="1.0" encoding="UTF-8"?>
<solr_params>
  <params>
    <param name="q" type="1" allow_multiple="0" count="1" delimiter="38" arg_separator="0">
      <param_value>lucene</param_value>
    </param>
    <param name="start" type="1" allow_multiple="0" count="1" delimiter="38" arg_separator="0">
      <param_value>0</param_value>
    </param>
    <param name="rows" type="1" allow_multiple="0" count="1" delimiter="38" arg_separator="0">
      <param_value>10</param_value>
    </param>
    <param name="fq" type="1" allow_multiple="1" count="2" delimiter="38" arg_separator="0">
      <param_value>popularity:[10 TO *]</param_value>
      <param_value>section:0</param_value>
    </param>
  </params>
</solr_params>
}

--TEST--
SolrDocument - new serialize api
--SKIPIF--
<?php if (PHP_VERSION_ID < 80100) die("skip PHP 8.1+ only"); ?>
--FILE--
<?php

$old = 'C:12:"SolrDocument":172:{<?xml version="1.0" encoding="UTF-8"?>
<solr_document>
  <fields>
    <field name="id">
      <field_value>parent_2</field_value>
    </field>
  </fields>
</solr_document>
}';
$new = 'O:12:"SolrDocument":1:{s:3:"xml";s:172:"<?xml version="1.0" encoding="UTF-8"?>
<solr_document>
  <fields>
    <field name="id">
      <field_value>parent_2</field_value>
    </field>
  </fields>
</solr_document>
";}';

/** @var SolrDocument $docOld */
$docOld = unserialize($old);
/** @var SolrDocument $docNew */
$docNew = unserialize($new);
var_dump(
	json_encode($docOld->toArray()) === json_encode($docNew->toArray())
);
var_dump($docNew->__serialize());
?>
--EXPECT--
bool(true)
array(1) {
  ["xml"]=>
  string(172) "<?xml version="1.0" encoding="UTF-8"?>
<solr_document>
  <fields>
    <field name="id">
      <field_value>parent_2</field_value>
    </field>
  </fields>
</solr_document>
"
}

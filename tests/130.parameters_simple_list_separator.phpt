--TEST--
simple_list_parameter type - Use of default, non-default separator
--FILE--
<?php
// arg list change
$query = new SolrQuery();
$query->addField("te")->addField("te2");
echo $query.PHP_EOL;

$dismaxQuery = new SolrDisMaxQuery();
$dismaxQuery
->addUserField('cat')
->addUserField('text')
->addUserField('*_dt')
;
echo $dismaxQuery.PHP_EOL;

?>
--EXPECTF--
fl=te,te2
defType=edismax&uf=cat text *_dt
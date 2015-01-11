--TEST--
SolrDisMaxQuery - UserFields (uf parameter) (addUserField)
--FILE--
<?php
$dismaxQuery = new SolrDisMaxQuery('lucene');
$dismaxQuery
->addUserField('cat')
->addUserField('text')
->addUserField('*_dt')
;
echo $dismaxQuery.PHP_EOL;
// // reverse
$dismaxQuery
->removeUserField('text');
echo $dismaxQuery.PHP_EOL;

$dismaxQuery->setUserFields('field1 field2 *_txt');
echo $dismaxQuery.PHP_EOL;

?>
--EXPECTF--
q=lucene&defType=%s&uf=cat text *_dt
q=lucene&defType=%s&uf=cat *_dt

Notice: SolrDisMaxQuery::setUserFields(): Parameter uf value(s) was overwritten by this call in %s on line %d
q=lucene&defType=edismax&uf=field1 field2 *_txt
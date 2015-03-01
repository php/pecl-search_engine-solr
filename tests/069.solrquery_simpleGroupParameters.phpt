--TEST--
SolrQuery - testing SimpleGroupParameters
--FILE--
<?php

$query = new SolrQuery();

$query->setGroup(0);

$query->addGroupField('israel')->addGroupField('israel2');

//$query->addGroupFunction('funcwhat');

$query->addGroupQuery('silk')->addGroupQuery('name:june');

$query->setGroupLimit(98);

$query->setGroupOffset(110);

$query->setGroupSort('count DESC');

$query->setGroupFormat('simple');

$query->setGroupMain(1);

$query->setGroupNGroups(1);

$query->setGroupTruncate(1);

$query->setGroupFacet(1);

echo $query;
echo "\n";

?>
--EXPECTF--
group=false&group.field=israel&group.field=israel2&group.query=silk&group.query=name:june&group.limit=98&group.offset=110&group.sort=count+DESC&group.format=simple&group.main=true&group.ngroups=true&group.truncate=truncate&group.facet=true
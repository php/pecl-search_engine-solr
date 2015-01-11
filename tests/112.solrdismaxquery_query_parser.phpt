--TEST--
SolrDisMaxQuery - QueryParser Switch
--FILE--
<?php
$dismaxQuery = new SolrDisMaxQuery("hard drive");
echo $dismaxQuery.PHP_EOL;
$dismaxQuery->useDisMaxQueryParser();
echo $dismaxQuery.PHP_EOL;
$dismaxQuery->useEDisMaxQueryParser();
echo $dismaxQuery.PHP_EOL;
?>
--EXPECTF--
q=hard drive&defType=edismax
q=hard drive&defType=dismax
q=hard drive&defType=edismax
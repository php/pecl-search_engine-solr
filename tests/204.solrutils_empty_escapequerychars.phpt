--TEST--
SolrUtils::escapeQueryChars() - Testing empty queryString
--FILE--
<?php
var_dump(SolrUtils::escapeQueryChars(''));
var_dump(SolrUtils::queryPhrase(''));
?>
--EXPECTF--
string(0) ""
string(2) """"

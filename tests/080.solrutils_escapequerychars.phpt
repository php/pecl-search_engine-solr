--TEST--
SolrUtils::escapeQueryChars() - Testing Lucene Reserved Characters
--FILE--
<?php
// + - && || ! ( ) { } [ ] ^ " ~ * ? : \
$queryString = '+a - q{ } [^test] || && () ^ " ~ * ? : \\ /';
$escaped = SolrUtils::escapeQueryChars($queryString);
echo $escaped;
?>
--EXPECTF--
\+a \- q\{ \} \[\^test\] \|| \&& \(\) \^ \" \~ \* \? \: \\ \/
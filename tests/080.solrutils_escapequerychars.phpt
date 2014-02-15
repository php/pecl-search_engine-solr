--TEST--
SolrQuery - testing TermsComponent
--EXTENSIONS--
libxml
curl
--FILE--
<?php
// + - && || ! ( ) { } [ ] ^ " ~ * ? : \
$queryString = '+a - q{ } [^test] || && () ^ " ~ * ? : \\ /';
$escaped = SolrUtils::escapeQueryChars($queryString);
echo $escaped;
?>
--EXPECTF--
\+a \- q\{ \} \[\^test\] \|| \&& \(\) \^ \" \~ \* \? \: \\ \/
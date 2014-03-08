--TEST--
SolrQuery - testing HighlightingParameters
--FILE--
<?php

$query = new SolrQuery();

$query->setHighlight(0);

$query->addHighlightField('a')->addHighlightField('a')->addHighlightField('a');

$query->removeHighlightField('a')->removeHighlightField('a')->removeHighlightField('a');

$query->setHighlightSnippets(4)->setHighlightSnippets(5, 'june');

$query->setHighlightFragsize(41)->setHighlightFragsize(52, 'june');

$query->setHighlightMergeContiguous(true)->setHighlightMergeContiguous(false, 'june');

$query->setHighlightRequireFieldMatch(true);

$query->setHighlightMaxAnalyzedChars(44)->setHighlightMaxAnalyzedChars(53);

$query->setHighlightAlternateField('pizza')->setHighlightAlternateField('bread', 'june');

$query->setHighlightAlternateField('blue')->setHighlightAlternateField('red','june');

$query->setHighlightAlternateField('a')->setHighlightAlternateField('b','june');

$query->setHighlightMaxAlternateFieldLength(300)->setHighlightMaxAlternateFieldLength(335, 'june');

$query->setHighlightFormatter('F')->setHighlightFormatter('G', 'june');

$query->setHighlightSimplePre('OO')->setHighlightSimplePre('PP', 'june');

$query->setHighlightSimplePost('ZZ')->setHighlightSimplePost('YY', 'june');

$query->setHighlightFragmenter('gap')->setHighlightFragmenter('space', 'june');

$query->setHighlightUsePhraseHighlighter(false);

$query->setHighlightHighlightMultiTerm(1);

$query->setHighlightRegexSlop(0.0025);

$query->setHighlightRegexPattern("israel")->setHighlightRegexPattern("ekpo");

$query->setHighlightRegexMaxAnalyzedChars(444)->setHighlightRegexMaxAnalyzedChars(5.0);

echo $query;
echo "\n";

?>
--EXPECTF--
hl=false&hl.snippets=4&f.june.hl.snippets=5&hl.fragsize=41&f.june.hl.fragsize=52&hl.mergeContiguous=true&f.june.hl.mergeContiguous=false&hl.requireFieldMatch=true&hl.maxAnalyzedChars=53&hl.alternateField=a&f.june.hl.alternateField=b&hl.maxAlternateFieldLength=300&f.june.hl.maxAlternateFieldLength=335&hl.formatter=F&f.june.hl.formatter=G&hl.simple.pre=OO&f.june.hl.simple.pre=PP&hl.simple.post=ZZ&f.june.hl.simple.post=YY&hl.fragmenter=gap&f.june.hl.fragmenter=space&hl.usePhraseHighlighter=false&hl.highlightMultiTerm=true&hl.regex.slop=0.0025&hl.regex.pattern=ekpo&hl.regex.maxAnalyzedChars=5
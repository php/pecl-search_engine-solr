--TEST--
SolrQuery - testing HighlightingParameters
--FILE--
<?php

$query = new SolrQuery();

ob_start();
var_dump(
	$query->getHighlight(),
	$query->getHighlightFields(),
	$query->getHighlightSnippets(),
	$query->getHighlightSnippets('june'),
	$query->getHighlightFragsize(),
	$query->getHighlightFragsize('june'),
	$query->getHighlightMergeContiguous(),
	$query->getHighlightMergeContiguous('june'),
	$query->getHighlightRequireFieldMatch(),
	$query->getHighlightMaxAnalyzedChars(),
	$query->getHighlightAlternateField(),
	$query->getHighlightAlternateField('june'),
	$query->getHighlightMaxAlternateFieldLength(),
	$query->getHighlightMaxAlternateFieldLength('june'),
	$query->getHighlightFormatter(),
	$query->getHighlightFormatter('june'),
	$query->getHighlightSimplePre(),
	$query->getHighlightSimplePre('june'),
	$query->getHighlightSimplePost(),
	$query->getHighlightSimplePost('june'),
	$query->getHighlightFragmenter(),
	$query->getHighlightFragmenter('june'),
	$query->getHighlightUsePhraseHighlighter(),
	$query->getHighlightHighlightMultiTerm(),
	$query->getHighlightRegexSlop(),
	$query->getHighlightRegexPattern(),
	$query->getHighlightRegexMaxAnalyzedChars()
);
$nullOutput = ob_get_clean();


$query->setHighlight(0);

$query->addHighlightField('a')->addHighlightField('a')->addHighlightField('a')
	->addHighlightField('b');

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

echo $query . PHP_EOL . PHP_EOL;

var_dump(
	$query->getHighlight(),
	$query->getHighlightFields(),
	$query->getHighlightSnippets(),
	$query->getHighlightSnippets('june'),
	$query->getHighlightFragsize(),
	$query->getHighlightFragsize('june'),
	$query->getHighlightMergeContiguous(),
	$query->getHighlightMergeContiguous('june'),
	$query->getHighlightRequireFieldMatch(),
	$query->getHighlightMaxAnalyzedChars(),
	$query->getHighlightAlternateField(),
	$query->getHighlightAlternateField('june'),
	$query->getHighlightMaxAlternateFieldLength(),
	$query->getHighlightMaxAlternateFieldLength('june'),
	$query->getHighlightFormatter(),
	$query->getHighlightFormatter('june'),
	$query->getHighlightSimplePre(),
	$query->getHighlightSimplePre('june'),
	$query->getHighlightSimplePost(),
	$query->getHighlightSimplePost('june'),
	$query->getHighlightFragmenter(),
	$query->getHighlightFragmenter('june'),
	$query->getHighlightUsePhraseHighlighter(),
	$query->getHighlightHighlightMultiTerm(),
	$query->getHighlightRegexSlop(),
	$query->getHighlightRegexPattern(),
	$query->getHighlightRegexMaxAnalyzedChars()
);
echo PHP_EOL.$nullOutput;
?>
--EXPECT--
hl=false&hl.fl=b&hl.snippets=4&f.june.hl.snippets=5&hl.fragsize=41&f.june.hl.fragsize=52&hl.mergeContiguous=true&f.june.hl.mergeContiguous=false&hl.requireFieldMatch=true&hl.maxAnalyzedChars=53&hl.alternateField=a&f.june.hl.alternateField=b&hl.maxAlternateFieldLength=300&f.june.hl.maxAlternateFieldLength=335&hl.formatter=F&f.june.hl.formatter=G&hl.simple.pre=OO&f.june.hl.simple.pre=PP&hl.simple.post=ZZ&f.june.hl.simple.post=YY&hl.fragmenter=gap&f.june.hl.fragmenter=space&hl.usePhraseHighlighter=false&hl.highlightMultiTerm=true&hl.regex.slop=0.0025&hl.regex.pattern=ekpo&hl.regex.maxAnalyzedChars=5

bool(false)
array(1) {
  [0]=>
  string(1) "b"
}
int(4)
int(5)
int(41)
int(52)
bool(true)
bool(false)
bool(true)
int(53)
string(1) "a"
string(1) "b"
int(300)
int(335)
string(1) "F"
string(1) "G"
string(2) "OO"
string(2) "PP"
string(2) "ZZ"
string(2) "YY"
string(3) "gap"
string(5) "space"
bool(false)
bool(true)
float(0.0025)
string(4) "ekpo"
int(5)

NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL

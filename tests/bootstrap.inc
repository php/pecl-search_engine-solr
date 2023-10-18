<?php

require_once "test.config.inc";

function separator($label) {
	echo str_pad(' '.$label.' ', 80, '=', STR_PAD_BOTH) . PHP_EOL;
}

function print_exception(SolrException $e) {
	echo sprintf("%s %d: %s", get_class($e), $e->getCode(), $e->getMessage()). PHP_EOL;
}

/**
 * Prints a test case title
 * 
 * @param int $case_id
 * @param string $title
 */
function case_title(int $case_id, string $title) {
	$caseTemplate = PHP_EOL . "case #%d: %s" . PHP_EOL;
	echo sprintf($caseTemplate, $case_id, $title);
}

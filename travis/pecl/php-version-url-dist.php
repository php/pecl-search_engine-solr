#!/usr/bin/env php
<?php


$versions = @json_decode(stream_get_contents(STDIN), 1);
$mirror = getenv("PHP_MIRROR");






$by_minor = array();
# build the tree of latest versions per minor
if (!empty($versions) && !isset($versions["error"])) {
	foreach (array_keys((array) $versions) as $release) {
		list($major, $minor, $patch) = explode(".", $release);
		if (isset($by_minor["$major.$minor"])) {
			if (version_compare($release, $by_minor["$major.$minor"], "<")) {
				continue;
			}
		}
		$by_minor["$major.$minor"] = $release;
	}
}

foreach ($by_minor as $v => $r) {
	printf("%s\t%s\tcurl -sSL %s%s | tar xj\n", $v, $r, $mirror,
			$versions[$r]["source"][0]["filename"]);
}

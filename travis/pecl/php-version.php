#!/usr/bin/env php
<?php

$version = $argv[1];
$versions = @json_decode(stream_get_contents(STDIN), 1);

# check if we've got a distinct version
if (isset($versions[$version])) {
	printf("%s\n", $version);
	exit;
}

$by_minor = array();
# build the tree of latest versions per minor
foreach (array_keys((array) $versions) as $release) {
	list($major, $minor, $patch) = explode(".", $release);
	if (isset($by_minor["$major.$minor"])) {
		if (version_compare($release, $by_minor["$major.$minor"], "<")) {
			continue;
		}
	}
	$by_minor["$major.$minor"] = $release;
}

# check latest release
if (isset($by_minor[$version])) {
	printf("%s\n", $by_minor[$version]);
} else {
	# failsafe
	switch ($version) {
	case "5.4":
		print("5.4.45\n");
		break;
	case "5.5":
		print("5.5.30\n");
		break;
	case "5.6":
		print("5.6.16\n");
		break;
	case "7.0":
		printf("7.0.0\n");
		break;
	case "master":
		print("master\n");
		break;
	default:
		printf("%s\n", $version);
	}
}

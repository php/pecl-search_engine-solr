#!/usr/bin/env php
<?php

error_reporting(E_ALL & ~(E_DEPRECATED|E_STRICT));

if ($argc < 2) {
	fprintf(STDERR, "Usage: %s <path/to/package.xml>\n", $argv[0]);
	exit(1);
}

require_once "PEAR/Config.php";
require_once "PEAR/PackageFile.php";

define("PACKAGE_XML", $argv[1]);
define("PACKAGE_DIR", dirname(PACKAGE_XML));

$factory = new PEAR_PackageFile(PEAR_Config::singleton());
$pf = $factory->fromPackageFile($argv[1], PEAR_VALIDATE_NORMAL);

if (PEAR::isError($pf)) {
	fprintf(STDERR, "ERROR: %s\n", $pf->getMessage());
	exit(1);
}

foreach ($pf->getValidationWarnings() as $warning) {
	fprintf(STDERR, "%s: %s\n", strtoupper($warning["level"]), $warning["message"]);
}

$exit = 0;
foreach ($pf->getFilelist() as $file => $attr) {
	if (!file_exists(PACKAGE_DIR."/".$file)) {
		$exit++;
		fprintf(STDERR, "File '%s' with role '%s' not found in '%s'\n",
			$file, $attr["role"], PACKAGE_DIR);
	}
}

if ($exit) {
	fprintf(STDERR, "%3d failure(s)\n", $exit);
	exit(1);
}

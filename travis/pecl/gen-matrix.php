<?php

return function ($array) {
	foreach ($array as $key => $values) {
		if (is_numeric($key) && is_string($values)) {
			$key = $values;
			$values = ["no","yes"];
		}
		if (empty($apc)) {
			// seed
			foreach ($values as $val) {
				$apc[] = "$key=$val";
			}
		} else {
			// combine
			$cpc = $apc;
			$apc = [];
			foreach ($values as $val) {
				foreach ($cpc as $e) {
					$apc[] = "$e $key=$val";
				}
			}
		}
	}
	return $apc;
};

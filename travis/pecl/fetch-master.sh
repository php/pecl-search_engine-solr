#!/bin/bash

if test -d php-master; then
	cd php-master
	git pull
else
	git clone --depth 1 -b master https://github.com/php/php-src php-master 
	cd php-master
fi

./buildconf

export

PHP ?= 5.6
JOBS ?= 2
PHP_MIRROR ?= http://us1.php.net/distributions/

ifdef TRAVIS_JOB_NUMBER
prefix ?= $(HOME)/job-$(TRAVIS_JOB_NUMBER)
else
prefix ?= $(HOME)
endif
exec_prefix ?= $(prefix)
bindir = $(exec_prefix)/bin
srcdir := $(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

enable_maintainer_zts ?= no
enable_debug ?= no
enable_all ?= no
with_config_file_scan_dir ?= $(prefix)/etc/php.d

with_php_config ?= $(bindir)/php-config
extdir = $(shell test -x $(with_php_config) && $(with_php_config) --extension-dir)

PECL_MIRROR ?= http://pecl.php.net/get/
PECL_EXTENSION ?= $(shell echo $(PECL) | cut -d: -f1)
PECL_SONAME ?= $(if $(shell echo $(PECL) | cut -d: -f2),$(shell echo $(PECL) | cut -d: -f2),$(PECL_EXTENSION))
PECL_VERSION ?= $(shell echo $(PECL) | cut -d: -f3 -s)
PECL_INI = $(with_config_file_scan_dir)/pecl.ini

PHP_VERSION_MAJOR = $(firstword $(subst ., ,$(PHP)))
PHP_VERSIONS_JSON = $(srcdir)/php-versions$(PHP_VERSION_MAJOR).json
PHP_VERSION ?= $(shell test -e $(PHP_VERSIONS_JSON) && cat $(PHP_VERSIONS_JSON) | $(srcdir)/php-version.php $(PHP))

.SUFFIXES:

.PHONY: all
all: php

## -- PHP

.PHONY: clean
clean:
	@if test -d $(srcdir)/php-$(PHP_VERSION); then cd $(srcdir)/php-$(PHP_VERSION); make distclean || true; fi

.PHONY: check
check: $(PHP_VERSIONS_JSON)
	@if test -z "$(PHP)"; then echo "No php version specified, e.g. PHP=5.6"; exit 1; fi

.PHONY: reconf
reconf: check $(srcdir)/php-$(PHP_VERSION)/configure
	cd $(srcdir)/php-$(PHP_VERSION) && ./configure -C --prefix=$(prefix)

.PHONY: php
php: check $(bindir)/php

$(PHP_VERSIONS_JSON): $(srcdir)/php-version.php
	curl -Sso $@ "http://php.net/releases/index.php?json&version=$(PHP_VERSION_MAJOR)&max=-1"

$(srcdir)/php-$(PHP_VERSION)/configure: | $(PHP_VERSIONS_JSON)
	if test $(PHP_VERSION) = "master"; then \
		cd $(srcdir) && git clone --depth 1 -b master https://github.com/php/php-src php-master && cd php-master && ./buildconf; \
	else \
		curl -Ss $(PHP_MIRROR)/php-$(PHP_VERSION).tar.bz2 | tar xj -C $(srcdir); \
	fi

$(srcdir)/php-$(PHP_VERSION)/Makefile: $(srcdir)/php-$(PHP_VERSION)/configure | $(PHP_VERSIONS_JSON)
	cd $(srcdir)/php-$(PHP_VERSION) && ./configure -C --prefix=$(prefix)

$(srcdir)/php-$(PHP_VERSION)/sapi/cli/php: $(srcdir)/php-$(PHP_VERSION)/Makefile | $(PHP_VERSIONS_JSON)
	cd $(srcdir)/php-$(PHP_VERSION) && make -j $(JOBS) || make

$(bindir)/php: $(srcdir)/php-$(PHP_VERSION)/sapi/cli/php | $(PHP_VERSIONS_JSON)
	cd $(srcdir)/php-$(PHP_VERSION) && make install

$(with_config_file_scan_dir):
	mkdir -p $@

## -- PECL

.PHONY: pecl-check
pecl-check:
	@if test -z "$(PECL)"; then echo "No pecl extension specified, e.g. PECL=pecl_http:http"; exit 1; fi

.PHONY: pecl-clean
pecl-clean:
	@if test -d $(srcdir)/pecl-$(PECL_EXTENSION); then cd $(srcdir)/pecl-$(PECL_EXTENSION); make distclean || true; fi

.PHONY: pecl-rm
pecl-rm:
	rm -f $(extdir)/$(PECL_SONAME).so

$(PECL_INI): | $(with_config_file_scan_dir)
	touch $@

$(srcdir)/pecl-$(PECL_EXTENSION):
	test -e $@ || ln -s $(CURDIR) $@

$(srcdir)/pecl-$(PECL_EXTENSION)/config.m4:
	mkdir -p $(srcdir)/pecl-$(PECL_EXTENSION)
	curl -Ss $(PECL_MIRROR)/$(PECL_EXTENSION)$(if $(PECL_VERSION),/$(PECL_VERSION)) | tar xz --strip-components 1 -C $(srcdir)/pecl-$(PECL_EXTENSION)

$(srcdir)/pecl-$(PECL_EXTENSION)/configure: $(srcdir)/pecl-$(PECL_EXTENSION)/config.m4
	cd $(srcdir)/pecl-$(PECL_EXTENSION) && $(bindir)/phpize

$(srcdir)/pecl-$(PECL_EXTENSION)/Makefile: $(srcdir)/pecl-$(PECL_EXTENSION)/configure
	cd $(srcdir)/pecl-$(PECL_EXTENSION) && ./configure -C

$(srcdir)/pecl-$(PECL_EXTENSION)/.libs/$(PECL_SONAME).so: $(srcdir)/pecl-$(PECL_EXTENSION)/Makefile
	cd $(srcdir)/pecl-$(PECL_EXTENSION) && make -j $(JOBS) || make

$(extdir)/$(PECL_SONAME).so: $(srcdir)/pecl-$(PECL_EXTENSION)/.libs/$(PECL_SONAME).so
	cd $(srcdir)/pecl-$(PECL_EXTENSION) && make install

.PHONY: pecl
pecl: pecl-check php $(extdir)/$(PECL_SONAME).so | $(PECL_INI)
	grep -q extension=$(PECL_SONAME).so $(PECL_INI) || echo extension=$(PECL_SONAME).so >> $(PECL_INI)

.PHONY: ext-clean
ext-clean: pecl-clean

.PHONY: ext-rm
ext-rm: pecl-rm

.PHONY: ext
ext: pecl-check $(srcdir)/pecl-$(PECL_EXTENSION) pecl
	$(srcdir)/check-packagexml.php package.xml

.PHONY: php
test: php
	REPORT_EXIT_STATUS=1 $(bindir)/php run-tests.php -q -p $(bindir)/php --set-timeout 300 --show-diff tests

pharext/%: $(PECL_INI) php | $(srcdir)/../%.ext.phar
	for phar in $|; do $(bindir)/php $$phar --prefix=$(prefix) --ini=$(PECL_INI); done

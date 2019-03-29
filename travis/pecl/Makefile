export

PHP ?= 7.2.16
JOBS ?= 2
PHP_MIRROR ?= https://www.php.net/distributions

ifdef TRAVIS_JOB_NUMBER
prefix ?= $(HOME)/job-$(TRAVIS_JOB_NUMBER)
else
prefix ?= $(HOME)
endif
exec_prefix ?= $(prefix)
bindir = $(exec_prefix)/bin
srcdir := $(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))
ifdef TRAVIS_BUILD_DIR
curdir ?= $(TRAVIS_BUILD_DIR)
else
# CURDIR is a make builtin
curdir ?= $(CURDIR)
endif

enable_maintainer_zts ?= no
enable_debug ?= no
enable_all ?= no
with_config_file_scan_dir ?= $(prefix)/etc/php.d

with_php_config ?= $(bindir)/php-config
extdir = $(shell test -x $(with_php_config) && $(with_php_config) --extension-dir)

PECL_MIRROR ?= http://pecl.php.net/get/
PECL_WORDS := $(subst :, ,$(PECL))
PECL_EXTENSION ?= $(word 1,$(PECL_WORDS))
PECL_SONAME ?= $(if $(word 2,$(PECL_WORDS)),$(word 2,$(PECL_WORDS)),$(PECL_EXTENSION))
PECL_VERSION ?= $(word 3,$(PECL_WORDS))
PECL_INI = $(with_config_file_scan_dir)/pecl.ini
PECL_DIR := $(if $(filter ext ext%, $(MAKECMDGOALS)), $(curdir), $(srcdir)/pecl-$(PECL_EXTENSION))

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
		curl --http1.0 -Ss $(PHP_MIRROR)/php-$(PHP_VERSION).tar.bz2 | tar xj -C $(srcdir); \
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
	@if test -d $(PECL_DIR); then cd $(PECL_DIR); make distclean || true; fi

.PHONY: pecl-rm
pecl-rm:
	rm -f $(extdir)/$(PECL_SONAME).so

$(PECL_INI): | $(with_config_file_scan_dir)
	touch $@

$(PECL_DIR)/config.m4:
	mkdir -p $(PECL_DIR)
	curl -Ss $(PECL_MIRROR)/$(PECL_EXTENSION)$(if $(PECL_VERSION),/$(PECL_VERSION)) | tar xz --strip-components 1 -C $(PECL_DIR)

$(PECL_DIR)/configure: $(PECL_DIR)/config.m4
	cd $(PECL_DIR) && $(bindir)/phpize

$(PECL_DIR)/Makefile: $(PECL_DIR)/configure
	cd $(PECL_DIR) && ./configure --enable-coverage -C

$(PECL_DIR)/.libs/$(PECL_SONAME).so: $(PECL_DIR)/Makefile
	cd $(PECL_DIR) && make -j $(JOBS) || make

$(extdir)/$(PECL_SONAME).so: $(PECL_DIR)/.libs/$(PECL_SONAME).so
	cd $(PECL_DIR) && make install

.PHONY: pecl
pecl: pecl-check php $(extdir)/$(PECL_SONAME).so | $(PECL_INI)
	grep -q extension=$(PECL_SONAME).so $(PECL_INI) || echo extension=$(PECL_SONAME).so >> $(PECL_INI)

.PHONY: ext-clean
ext-clean: pecl-clean

.PHONY: ext-rm
ext-rm: pecl-rm

.PHONY: ext
ext: pecl-check pecl
	$(srcdir)/check-packagexml.php package.xml

.PHONY: php
test: php
	REPORT_EXIT_STATUS=1 $(bindir)/php run-tests.php -q -p $(bindir)/php --set-timeout 300 --show-diff tests

pharext/%: $(PECL_INI) php | $(srcdir)/../%.ext.phar
	for phar in $|; do $(bindir)/php $$phar --prefix=$(prefix) --ini=$(PECL_INI); done
	
.PHONY: install-logbt
install-logbt:
	mkdir ./mason/; \
	curl -sSfL https://github.com/mapbox/mason/archive/v0.2.0.tar.gz | tar --gunzip --extract --strip-components=1 --directory=./mason/; \
	./mason/mason install gdb 7.12;
	curl -sSfL https://github.com/mapbox/logbt/archive/v1.6.0.tar.gz | tar --gunzip --extract --strip-components=2 --exclude="*md" --exclude="test*" --directory=. 
	
	

test-core-dumps: install-logbt
	$(eval GDB_PATH := $(shell ./mason/mason prefix gdb 7.12))
	$(eval PATH=${GDB_PATH}/bin:${PATH})
	$(shell export PATH)
	$(shell sudo bash -c "echo '/tmp/logbt-coredumps/core.%p.%E' > /proc/sys/kernel/core_pattern")
	./logbt make -f travis/pecl/Makefile test
	

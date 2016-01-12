#!/usr/bin/env bash
# build and test against a phpenv managed php version

set -e

SCRIPT_DIR=$(dirname $0)

make distclean &>/dev/null || true
phpize &&
CFLAGS="--coverage -fprofile-arcs -ftest-coverage" \
CXXFLAGS="-ftest-coverage" \
LDFLAGS="--coverage" \
./configure 
make -j4 &&
lcov --directory . --zerocounters &&
lcov --directory . --capture --initial --no-external --output-file coverage.info 

USE_PHP=${TEST_PHP_EXECUTABLE:-$(which php)}

TEST_PHP_EXECUTABLE=${USE_PHP} \
REPORT_EXIT_STATUS=0 \
${USE_PHP} \
  -n -d open_basedir= -d output_buffering=0 -d memory_limit=-1 \
  run-tests.php -q -n -d extension_dir=modules -d extension=solr.so tests/

lcov --remove coverage.info "/usr*" -o coverag.info # remove output for external libraries
lcov --no-checksum --directory . --capture --output-file coverage.info
genhtml --highlight --legend --output-directory report coverage.info

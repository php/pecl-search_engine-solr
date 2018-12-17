#!/usr/bin/env bash
# build and test against a phpenv managed php version

set -e

SCRIPT_DIR=$(dirname $0)

make distclean &>/dev/null || true
phpize &&
./configure --enable-coverage
make -j4 &&
lcov --directory . --zerocounters  &&
lcov --directory . --capture --initial --output-file coverage.info

USE_PHP=${TEST_PHP_EXECUTABLE:-$(which php)}

TEST_PHP_EXECUTABLE=${USE_PHP} \
REPORT_EXIT_STATUS=0 \
${USE_PHP} \
  -n -d open_basedir= -d output_buffering=0 -d memory_limit=-1 \
  run-tests.php -q -n -d extension=json.so -d extension=$PWD/modules/solr.so tests

lcov --no-checksum --directory . --capture --output-file coverage.info
lcov --remove coverage.info "/usr/*" -o coverage.info
genhtml --highlight --legend --output-directory report coverage.info

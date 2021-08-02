rebuild:
	docker-compose build --force-rm pecl-solr

logs:
	docker-compose logs -f pecl-solr

start:
	docker-compose up -d

stop:
	docker-compose stop

clean-restart:
	docker-compose stop pecl-solr && docker-compose rm -f pecl-solr && make -f dev/Makefile rebuild && docker-compose up -d

bash:
	docker-compose exec pecl-solr zsh

test:
	TEST_PHP_EXECUTABLE=/usr/bin/php REPORT_EXIT_STATUS=1 php run-tests.php -q --set-timeout 300 --show-diff tests
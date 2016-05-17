<?php

define('SOLR_SERVER_CONFIGURED', true);

define('ROOT_DIRECTORY', dirname(__FILE__));

define('EXAMPLE_RESPONSE_XML_1', ROOT_DIRECTORY . '/files/response_xml.1.xml');
define('EXAMPLE_RESPONSE_XML_2', ROOT_DIRECTORY . '/files/response_xml.2.xml');
define('EXAMPLE_RESPONSE_XML_3', ROOT_DIRECTORY . '/files/response_xml.3.xml');
define('EXAMPLE_RESPONSE_XML_4', ROOT_DIRECTORY . '/files/response_xml.4.xml');
define('EXTRACT_FILE_1', ROOT_DIRECTORY . '/files/extract_file.1.pdf');

/* Whether or not to run in secure mode */
define('SOLR_SECURE', false);

/* Domain name of the Solr server */
define('SOLR_SERVER_HOSTNAME', '127.0.0.1');

/* HTTP Port to connection */
define('SOLR_SERVER_PORT', ((SOLR_SECURE) ? 8443 : 8983));

/* SOLR CORE to test on */
define('SOLR_SERVER_PATH', 'solr/collection1');

/* used to test child documents */
define('SOLR_SERVER_STORE_PATH', 'solr/metal_store');

define('SOLR_SERVER_FILES_PATH', 'solr/myfiles');

/* HTTP Basic Authentication Username */
define('SOLR_SERVER_USERNAME', 'admin');

/* HTTP Basic Authentication password */
define('SOLR_SERVER_PASSWORD', 'changeit');

/* HTTP connection timeout */
/* This is maximum time in seconds allowed for the http data transfer operation. Default value is 30 seconds */
define('SOLR_SERVER_TIMEOUT', 10);

/* File name to a PEM-formatted private key + private certificate (concatenated in that order) */
define('SOLR_SSL_CERT', 'certs/combo.pem');

/* File name to a PEM-formatted private certificate only */
define('SOLR_SSL_CERT_ONLY', 'certs/solr.crt');

/* File name to a PEM-formatted private key */
define('SOLR_SSL_KEY', 'certs/solr.key');

/* Password for PEM-formatted private key file */
define('SOLR_SSL_KEYPASSWORD', 'StrongAndSecurePassword');

/* Name of file holding one or more CA certificates to verify peer with*/
define('SOLR_SSL_CAINFO', 'certs/cacert.crt');

/* Name of directory holding multiple CA certificates to verify peer with */
define('SOLR_SSL_CAPATH', 'certs/');

?>

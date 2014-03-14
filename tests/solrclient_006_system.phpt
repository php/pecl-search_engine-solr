--TEST--
SolrClient::system() - Retrieve Solr Server/System Info
--SKIPIF--
<?php 
include 'skip.if.server_not_configured.inc';
?>
--FILE--
<?php 

require_once "bootstrap.inc";

$options = array
(
		'hostname' => SOLR_SERVER_HOSTNAME,
		'login'    => SOLR_SERVER_USERNAME,
		'password' => SOLR_SERVER_PASSWORD,
		'port'     => SOLR_SERVER_PORT,
);

$client = new SolrClient($options);

$genericResponse = $client->system();
print_r($genericResponse->getResponse());

?>
--EXPECTF--
SolrObject Object
(
    [responseHeader] => SolrObject Object
        (
            [status] => 0
            [QTime] => %d
        )

    [core] => SolrObject Object
        (
            [schema] => %s
            [host] => %s
            [now] => %s
            [start] => %s
            [directory] => SolrObject Object
                (
                    [instance] => %s
                    [data] => %s
                    [index] => %s
                )

        )

    [lucene] => SolrObject Object
        (
            [solr-spec-version] => 3.%s
            [solr-impl-version] => 3.%s
            [lucene-spec-version] => 3.%d.%d
            [lucene-impl-version] => 3.%d.%d %s
        )

    [jvm] => SolrObject Object
        (
            [version] => %s
            [name] => %s
            [processors] => %d
            [memory] => SolrObject Object
                (
                    [free] => %f MB
                    [total] => %f MB
                    [max] => %f MB
                    [used] => %f MB (%%f)
                )

            [jmx] => SolrObject Object
                (
                    [bootclasspath] => %s
                    [classpath] => %s
                    [commandLineArgs] => Array
                        (
                        )

                    [startTime] => %s
                    [upTimeMS] => %d
                )

        )

    [system] => SolrObject Object
        (
            [name] => %s
            [version] => %s
            [arch] => %s
            [systemLoadAverage] => %f
            [committedVirtualMemorySize] => %d
            [freePhysicalMemorySize] => %d
            [freeSwapSpaceSize] => %d
            [processCpuTime] => %d
            [totalPhysicalMemorySize] => %d
            [totalSwapSpaceSize] => %d
            [openFileDescriptorCount] => %d
            [maxFileDescriptorCount] => %d
            [uname] => %s

            [uptime] =>  %s

        )

)


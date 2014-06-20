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
                    [cwd] => %s
                    [instance] => %s
                    [data] => %s
                    [index] => %s
                )

        )

    [lucene] => SolrObject Object
        (
            [solr-spec-version] => 4.%s
            [solr-impl-version] => 4.%s
            [lucene-spec-version] => 4.%d.%d
            [lucene-impl-version] => 4.%d.%d %s
        )

    [jvm] => SolrObject Object
        (
            [version] => %s
            [name] => %s
            [processors] => %d
            [memory] => SolrObject Object
                (
                    [free] => %f %s
                    [total] => %f %s
                    [max] => %f %s
                    [used] => %f %s (%%f)
                    [raw] => SolrObject Object
                        (
                            [free] => %d
                            [total] => %d
                            [max] => %d
                            [used] => %d
                            [used%] => %f
                        )

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


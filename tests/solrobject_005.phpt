--TEST--
SolrObject - checking dimension access on properties.
--FILE--
<?php

require_once "bootstrap.inc";

$xml_reponse = file_get_contents(EXAMPLE_RESPONSE_XML_1);

$solrObject = SolrUtils::digestXMLResponse($xml_reponse);

$header = ($solrObject['responseHeader']);

$system = $solrObject['system'];

print_r($header);

print_r($system);

?>
--EXPECT--
SolrObject Object
(
    [status] => 0
    [QTime] => 72
)
SolrObject Object
(
    [threadCount] => SolrObject Object
        (
            [current] => 15
            [peak] => 15
            [daemon] => 13
        )

    [threadDump] => SolrObject Object
        (
            [thread] => SolrObject Object
                (
                    [id] => 1
                    [name] => main
                    [state] => RUNNABLE
                    [native] => 1
                    [cpuTime] => 3340.0000ms
                    [userTime] => 3180.0000ms
                    [stackTrace] => Array
                        (
                            [0] => java.net.PlainSocketImpl.socketAccept(Native Method)
                            [1] => java.net.PlainSocketImpl.accept(PlainSocketImpl.java:384)
                            [2] => java.net.ServerSocket.implAccept(ServerSocket.java:450)
                            [3] => java.net.ServerSocket.accept(ServerSocket.java:421)
                            [4] => org.apache.catalina.core.StandardServer.await(StandardServer.java:389)
                            [5] => org.apache.catalina.startup.Catalina.await(Catalina.java:642)
                            [6] => org.apache.catalina.startup.Catalina.start(Catalina.java:602)
                            [7] => sun.reflect.NativeMethodAccessorImpl.invoke0(Native Method)
                            [8] => sun.reflect.NativeMethodAccessorImpl.invoke(NativeMethodAccessorImpl.java:39)
                            [9] => sun.reflect.DelegatingMethodAccessorImpl.invoke(DelegatingMethodAccessorImpl.java:25)
                            [10] => java.lang.reflect.Method.invoke(Method.java:585)
                            [11] => org.apache.catalina.startup.Bootstrap.start(Bootstrap.java:288)
                            [12] => org.apache.catalina.startup.Bootstrap.main(Bootstrap.java:413)
                        )

                )

        )

)

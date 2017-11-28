<?php
require 'vendor/autoload.php';

$client = new MongoDB\Client;
$mydb1 = $client->mydb1;
#$res1 = $mydb1->createCollection('allData');  //used to create collection.
$allData = $mydb1->allData;
#$res2 = $mydb1->createCollection('results');  //used to create collection.
$results = $mydb1->results;
#################################################################################



$url = "http://sbsrv1.cs.nuim.ie/lora/list.php?node=08-00-AA-00-C0-22-04-08&format=json";

$json =file_get_contents($url);
$jsonData =json_decode($json, TRUE);

var_dump($jsonData);

#################################################################################

#$insertArray = $allData->insertMany($jsonData);

?>
<?php
require 'vendor/autoload.php';

$client = new MongoDB\Client;
$mydb1 = $client->mydb1;
#$res1 = $mydb1->createCollection('allData');  //used to create collection.
$allData = $mydb1->allData;
#$res2 = $mydb1->createCollection('results');  //used to create collection.
$results = $mydb1->results;
#################################################################################

$insertManyData = $allData->insertMany([
	['ts' => '2017-11-27 20:45:33', 'data' => '92eb1e'],
	['ts' => '2017-11-27 20:46:33', 'data' => '92eb1e'],
	['ts' => '2017-11-27 20:47:33', 'data' => '92eb1e'],
	['ts' => '2017-11-27 20:48:33', 'data' => '92eb1e']
]);

printf("Inserted %d documents", $insertManyData->getInsertedCount());
var_dump($insertManyData->getInsertedIds());

?>
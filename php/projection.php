<?php
require 'vendor/autoload.php';

$client = new MongoDB\Client;
$mydb1 = $client->mydb1;
#$res1 = $mydb1->createCollection('allData');  //used to create collection.
$allData = $mydb1->allData;
#$res2 = $mydb1->createCollection('results');  //used to create collection.
$results = $mydb1->results;
#################################################################################



$documentlist = $allData->find(
	['data' => '1111'],
	['projection' => ['_id' => 0, 'ts' => 1]]
);

foreach($documentlist as $doc)
{
	var_dump($doc);
}


?>
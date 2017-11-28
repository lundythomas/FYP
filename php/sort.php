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
	[],
	[
		//'limit' => 2,  //lets you limit to 2 documents.
		//'skip' => 2,   //lets you skip documents.
		'sort' => ['ts' => -1] //lets you sort, 1 for ASC, -1 for DESC.
		
	]
);

foreach($documentlist as $doc)
{
	var_dump($doc);
}


?>
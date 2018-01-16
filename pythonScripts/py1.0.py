import sys
import urllib2
import bson
import pymongo
import json
from pymongo import MongoClient
from bson import json_util

url = "http://sbsrv1.cs.nuim.ie/lora/list.php?node=08-00-AA-00-C0-22-04-08&format=json"

response = urllib2.urlopen(url)
data = json_util.loads(response.read())

connection = MongoClient()
connection.database_names()
db = connection.test
collection = db.col1
post_id = collection.insert_many(data).inserted_id

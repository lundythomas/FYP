<html>


<script>

var settings = {
  "async": true,
  "crossDomain": true,
  "url": "http://sbsrv1.cs.nuim.ie/lora/list.php?node=08-00-AA-00-C0-22-04-08&format=json",
  "method": "GET",
  "headers": {
    "cache-control": "no-cache",
    "postman-token": "c1edaa1b-0cdb-85dc-112e-a3ec81b19a5b"
  }
}

$.ajax(settings).done(function (response) {
  console.log(response);
});

</script>

<body>

	<div>
	
	</div>

</body>
<html>
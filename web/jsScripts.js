var latestTime;
var updatedData;
var updatedTime;
var tempNew1;
var humNew1;
var tempNew2;
var humNew2;
var currTemp1;
var currHum1;
var currTemp2;
var currHum2;
var degrees ="&#8451;";
var percent = "&#37;";

google.charts.load('current', {'packages':['gauge']});
google.charts.setOnLoadCallback(updateData);

function roundToTwo(num) // function that rounds to two decimal points.
{
  return +(Math.round(num + "e+2")  + "e-2");
}

//$(document).ready(getLatestData);

function getLatestData() //functaion that retrives the lastest data from the db.
{
  $.getJSON("http://sbsrv1.cs.nuim.ie/lora/list.php?node=08-00-AA-00-C0-22-04-08&format=json", function(l)
  {
    latestTime = l[0].ts;
    var latestData = l[0].data;
    var len = l[0].data.length;

    if (len==6)  // This separates the data into the temp and humidity.
    {
      var tempNew1 = latestData.substring(0, 3);
      var humNew1 = latestData.substring(3, 7);
    }
    else if (len==8) //This is for when the temp and or humidity are above a certain figure.
    {
      var tempNew1 = latestData.substring(0, 4);
      var humNew1 = latestData.substring(4, 8);
    }
    else
    {
      console.log("There is something wrong with your data array length");
    }

    currTemp1 = (parseInt(tempNew1, 16)/100);
    currHum1 = (parseInt(humNew1, 16)/100);

    currTemp1 = roundToTwo(currTemp1);
    currHum1 = roundToTwo(currHum1);

    document.getElementById("test1.1").innerHTML = roundToTwo(currTemp1) + " " + degrees;
    document.getElementById("test2.2").innerHTML = roundToTwo(currHum1) + " " + percent;;
    document.getElementById("timeCollected").innerHTML = latestTime;
  });
}

function updateData() // Function that updates the data by retriving only the lastest data from the previous time.
{
  $.getJSON("http://sbsrv1.cs.nuim.ie/lora/list.php?node=08-00-AA-00-C0-22-04-08&format=json&since"+latestTime, function(u)
  {
    updatedData = u[0].data;
    updatedTime =  u[0].ts;
    latestTime = updatedTime;  // sets the most updated time to the lastest time.
    var len2 = u[0].data.length;

    if (len2==6) // This separates the data into the temp and humidity.
    {
      tempNew2 = updatedData.substring(0, 3);
      humNew2 = updatedData.substring(3, 7);
    }
    else if (len2==8) //This is for when the temp and or humidity are above a certain figure.
    {
      tempNew2 = updatedData.substring(0, 4);
      humNew2 = updatedData.substring(4, 8);
    }
    else
    {
      console.log("There is something wrong with your data array length");
    }

    currTemp2 = (parseInt(tempNew2, 16)/100);
    currHum2 = (parseInt(humNew2, 16)/100);

    document.getElementById("test1.1").innerHTML = roundToTwo(currTemp2) + " " + degrees;
    document.getElementById("test2.2").innerHTML = roundToTwo(currHum2) + " " + percent;;
    document.getElementById("timeCollected").innerHTML = updatedTime;

    currTemp2 = roundToTwo(currTemp2);
    currHum2 = roundToTwo(currHum2);
    ////////////////////////////////////////////////////////////////////////////////////
    var data = google.visualization.arrayToDataTable([
      ['Label', 'Value'],
      ['Temp', currTemp2], 
    ]);

    var options = {
      width: 400, height: 120,
      redFrom: 35, redTo: 50,
      yellowFrom:30, yellowTo: 35,
      greenFrom: 15, greenTo: 30,
      minorTicks: 5, max: 50, min: -10
    };

    var chart = new google.visualization.Gauge(document.getElementById('test1'));

    chart.draw(data, options);
    /////////////////////////////////////////////////////////////////////////////////////
    var data = google.visualization.arrayToDataTable([
      ['Label', 'Value'],
      ['Humidity', currHum2],
    ]);

    var options = {
      width: 400, height: 120,
      redFrom: 80, redTo: 100,
      yellowFrom:60, yellowTo: 80,
      greenFrom: 0, greenTo: 60,
      minorTicks: 5, max: 100
    };

    var chart = new google.visualization.Gauge(document.getElementById('test2'));

    chart.draw(data, options);
  });
}

setInterval(updateData, 10000);  // Interval of 10 seconds between updating data.

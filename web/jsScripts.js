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
var latestUid;

google.charts.load('current', {'packages':['gauge']});
google.charts.setOnLoadCallback(getLatestData);
google.charts.setOnLoadCallback(updateData);
google.charts.load('current', {packages: ['corechart', 'line']});
//google.charts.setOnLoadCallback(chartFun);

function roundToTwo(num) // function that rounds to two decimal points.
{
  return +(Math.round(num + "e+2")  + "e-2");
}

//$(document).ready(getLatestData);

function getLatestData() //functaion that retrives the lastest data from the db.
{
  $.getJSON("http://sbsrv1.cs.nuim.ie/lora/list.php?node=08-00-AA-00-C0-22-04-08&format=json", function(l)
  {
    //console.log("fun1");
    latestUid = l[0].uid;
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

    ////////////////////////////////////////////////////////////////////////////////////
    var data = google.visualization.arrayToDataTable([
      ['Label', 'Value'],
      ['Temp', currTemp1],
    ]);

    var options = {
      width: 400, height: 120,
      redFrom: 30, redTo: 50,
      yellowFrom: 25, yellowTo: 30,
      greenFrom: 15, greenTo: 25,
      minorTicks: 5, max: 50, min: -10
    };

    var chart = new google.visualization.Gauge(document.getElementById('test1'));

    chart.draw(data, options);
    /////////////////////////////////////////////////////////////////////////////////////
    var data = google.visualization.arrayToDataTable([
      ['Label', 'Value'],
      ['Humidity', currHum1],
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

function updateData() // Function that updates the data by retriving only the lastest data from the previous time.
{
  $.getJSON("http://sbsrv1.cs.nuim.ie/lora/list.php?node=08-00-AA-00-C0-22-04-08&format=json&since"+latestTime, function(u)
  {
    //console.log("fun2");
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
      redFrom: 30, redTo: 50,
      yellowFrom: 25, yellowTo: 30,
      greenFrom: 15, greenTo: 25,
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

////////////////////////////////////////////////////////////////////////////////////////

function chartFun1() {


      var data = new google.visualization.DataTable();
      data.addColumn('number', 'X');
      data.addColumn('number', 'Temp');

      data.addRows([
        [0, 0],   [1, currTemp2],  [2, currTemp2],  [3, currTemp2],  [4,currTemp2],  [5, currTemp2],
        [6, currTemp2],  [7, 27],  [8, 33],  [9, 40],  [10, 32], [11, 35],
        [12, 30], [13, 40], [14, 42], [15, 47], [16, 44], [17, 48],
        [18, 52], [19, 54], [20, 42], [21, 55], [22, 56], [23, 57],
        [24, 60], [25, 50], [26, 52], [27, 51], [28, 49], [29, 53],
        [30, 55], [31, 60], [32, 61], [33, 59], [34, 62], [35, 65],
        [36, 62], [37, 58], [38, 55], [39, 61], [40, 64], [41, 65],
        [42, 63], [43, 66], [44, 67], [45, 69], [46, 69], [47, 70]
      ]);

      var options = {
        hAxis: {
          title: 'Time'
        },
        vAxis: {
          title: 'Temp'
        },
        backgroundColor: '#f1f8e9'
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_temp1'));
      chart.draw(data, options);
    }

    $(window).resize(function(){
      chartFun1();
    });
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


function chartFun2() {


      var data = new google.visualization.DataTable();
      data.addColumn('number', 'X');
      data.addColumn('number', 'Humidity');

      data.addRows([
        [0, 0],   [1, 10],  [2, 23],  [3, 17],  [4, 18],  [5, 9],
        [6, 11],  [7, 27],  [8, 33],  [9, 40],  [10, 32], [11, 35],
        [12, 30], [13, 40], [14, 42], [15, 47], [16, 44], [17, 48],
        [18, 52], [19, 54], [20, 42], [21, 55], [22, 56], [23, 57],
        [24, 60], [25, 50], [26, 52], [27, 51], [28, 49], [29, 53],
        [30, 55], [31, 60], [32, 61], [33, 59], [34, 62], [35, 65],
        [36, 62], [37, 58], [38, 55], [39, 61], [40, 64], [41, 65],
        [42, 63], [43, 66], [44, 67], [45, 69], [46, 69], [47, 70]
      ]);

      var options = {
        hAxis: {
          title: 'Time'
        },
        vAxis: {
          title: 'Humidity'
        },
        backgroundColor: '#f1f8e9'
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_hum1'));
      chart.draw(data, options);
    }

    $(window).resize(function(){
      chartFun2();
    });

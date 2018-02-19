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
var updatedUid;
var tempNew3;
var humNew3;
var tempArray = [];
var humArray = [];
var test1;

$(document).ready(getLatestData);

google.charts.load('current', {'packages':['gauge']});
google.charts.load('current', {packages: ['corechart', 'line']});
google.charts.setOnLoadCallback(getLatestData);
google.charts.setOnLoadCallback(updateData);

function roundToTwo(num) // function that rounds to two decimal points.
{
  return +(Math.round(num + "e+2")  + "e-2");
}

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

    if (currTemp1>26)
    {
      emailTempWarning();
    }

    if (currHum1>60)
    {
      emailHumWarning();
    }

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
    updatedUid = u[0].uid;

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

    if (currTemp2>26)
    {
      emailTempWarning();
    }

    if (currHum2>60)
    {
      emailHumWarning();
    }

    ////////////////////////////////////////////////////////////////////////////////////

    for (var i=0; i<60; i++)
    {
          if (u[i].data.length==6) // This separates the data into the temp and humidity.
          {
            tempNew3 = u[i].data.substring(0, 3);
            humNew3 = u[i].data.substring(3, 7);
          }
          else if (u[i].data.length==8) //This is for when the temp and or humidity are above a certain figure.
          {
            tempNew3 = u[i].data.substring(0, 4);
            humNew3 = u[i].data.substring(4, 8);
          }
          else
          {
            console.log("There is something wrong with your data array length");
          }

          tempArray.push(roundToTwo(parseInt(tempNew3, 16)/100));
          humArray.push(roundToTwo(parseInt(humNew3, 16)/100));
    }
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
        [0, tempArray[59]],  [1, tempArray[58]],  [2, tempArray[57]], [3, tempArray[56]], [4, tempArray[55]], [5, tempArray[54]],
        [6, tempArray[53]],  [7, tempArray[52]],  [8, tempArray[51]], [9, tempArray[50]], [10, tempArray[49]], [11, tempArray[48]],
        [12, tempArray[47]],  [13, tempArray[46]],  [14, tempArray[45]], [15, tempArray[44]], [16, tempArray[43]], [17, tempArray[42]],
        [18, tempArray[41]],  [19, tempArray[40]],  [20, tempArray[39]], [21, tempArray[38]], [22, tempArray[37]], [23, tempArray[36]],
        [24, tempArray[35]],  [25, tempArray[34]],  [26, tempArray[33]], [27, tempArray[32]], [28, tempArray[31]], [29, tempArray[30]],
        [30, tempArray[29]],  [31, tempArray[28]],  [32, tempArray[27]], [33, tempArray[26]], [34, tempArray[25]], [35, tempArray[24]],
        [36, tempArray[23]],  [37, tempArray[22]],  [38, tempArray[21]], [39, tempArray[20]], [40, tempArray[19]], [41, tempArray[18]],
        [42, tempArray[17]],  [43, tempArray[16]],  [44, tempArray[15]], [45, tempArray[14]], [46, tempArray[13]], [47, tempArray[12]],
        [48, tempArray[11]],  [49, tempArray[10]],  [50, tempArray[9]], [51, tempArray[8]], [52, tempArray[7]], [53, tempArray[6]],
        [54, tempArray[5]],  [55, tempArray[4]],  [56, tempArray[3]], [57, tempArray[2]], [58, tempArray[1]], [59, tempArray[0]]
      ]);

      var options = {
        hAxis: {
          title: 'Time (Mins)'
        },
        curveType: 'function',
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
      data.addColumn('number', 'Humidity %');

      data.addRows([
        [0, humArray[59]],  [1, humArray[58]],  [2, humArray[57]], [3, humArray[56]], [4, humArray[55]], [5, humArray[54]],
        [6, humArray[53]],  [7, humArray[52]],  [8, humArray[51]], [9, humArray[50]], [10, humArray[49]], [11, humArray[48]],
        [12, humArray[47]],  [13, humArray[46]],  [14, humArray[45]], [15, humArray[44]], [16, humArray[43]], [17, humArray[42]],
        [18, humArray[41]],  [19, humArray[40]],  [20, humArray[39]], [21, humArray[38]], [22, humArray[37]], [23, humArray[36]],
        [24, humArray[35]],  [25, humArray[34]],  [26, humArray[33]], [27, humArray[32]], [28, humArray[31]], [29, humArray[30]],
        [30, humArray[29]],  [31, humArray[28]],  [32, humArray[27]], [33, humArray[26]], [34, humArray[25]], [35, humArray[24]],
        [36, humArray[23]],  [37, humArray[22]],  [38, humArray[21]], [39, humArray[20]], [40, humArray[19]], [41, humArray[18]],
        [42, humArray[17]],  [43, humArray[16]],  [44, humArray[15]], [45, humArray[14]], [46, humArray[13]], [47, humArray[12]],
        [48, humArray[11]],  [49, humArray[10]],  [50, humArray[9]], [51, humArray[8]], [52, humArray[7]], [53, humArray[6]],
        [54, humArray[5]],  [55, humArray[4]],  [56, humArray[3]], [57, humArray[2]], [58, humArray[1]], [59, humArray[0]]
      ]);

      var options = {
        hAxis: {
          title: 'Time (Mins)'
        },
        curveType: 'function',
        vAxis: {
          title: 'Humidity %'
        },
        backgroundColor: '#f1f8e9'
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_hum1'));
      chart.draw(data, options);
    }

    $(window).resize(function(){
      chartFun2();
    });

/////////////////////////////////////////////////////////////////////////////////////////////

function emailTempWarning()
{
    Email.send("tomlundycsse@gmail.com",
    "tomlundycsse@gmail.com",
    "Temperaure Warning!!",
    "The Temperature in the room has exceeded 26 Degrees and is now at : " + roundToTwo(currTemp2) + " °C",
    {token: "ae4fe9c4-63b0-4c5a-8dd4-efbd78108ecf"});
}

function emailHumWarning()
{
    Email.send("tomlundycsse@gmail.com",
    "tomlundycsse@gmail.com",
    "Humidity Warning!!",
    "The Humidity in the room has exceeded 50 % and is now at : " + roundToTwo(currHum2) + " %" ,
    {token: "ae4fe9c4-63b0-4c5a-8dd4-efbd78108ecf"});
}

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN            7         // Pin which is connected to the DHT sensor.
#define DHTTYPE           DHT22     // DHT 22 (AM2302)

unsigned char sending;
int pin_reset = 2;
String myPort = "10";  // Specify here which port you are using.
unsigned long trigger;
unsigned long period = 58000; // Period of Seconds x 1000 between sending data.
String SendCmd = "";
String tempInHex = "";
String humInHex = "";

void connJoin()
{
  pinMode(pin_reset, OUTPUT);
  digitalWrite(pin_reset, LOW); // reset-disable RN2483.
  SerialUSB.begin(57600);
  delay(2000);
  digitalWrite(pin_reset, HIGH);
  sending = 0;
  Serial5.begin(57600);
  delay(2000);
  Serial5.print("mac join otaa\r\n");
  trigger = millis() + period;
}

String sendData (String port, String tempData, String humData)
{
  String p = port;
  String t = tempData;
  String h = humData;
  String combinedData = t + h;
  //SerialUSB.println("hum is: " + h + ".  temp is: " + t + ".");
  //SerialUSB.println("combined is : " + combinedData + '\n');

  String SendCmd = "mac tx uncnf " + p + " " + combinedData + "\r\n";
  Serial5.print(SendCmd);

  return SendCmd;
}

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void setup() {

  connJoin();

  SerialUSB.begin(9600);
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
}

void loop() {

  String FtempInHex = "";

  if (millis() > trigger) {  //This sets a delay of x seconds between sendind data.
    sensors_event_t event;

    dht.temperature().getEvent(&event);
    float tempInFloat = event.temperature;
    int tempInInt = tempInFloat * 100;
    String tempInHex = String(tempInInt, HEX);

    dht.humidity().getEvent(&event);
    float humInFloat = event.relative_humidity;
    int humInInt = humInFloat * 100;
    String humInHex = String(humInInt, HEX);

    sendData(myPort, tempInHex, humInHex);  //Sending specified port number and data.
    trigger = millis() + period;


  }
  delay(delayMS);  // Delay between measurements.
}

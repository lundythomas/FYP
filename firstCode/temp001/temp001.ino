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

String sendData (String port, String data)
{
  String p = port;
  String d = data;
  String SendCmd = "mac tx uncnf " + p + " " + d + "\r\n";
  Serial5.print(SendCmd);

  return SendCmd;
}

float convertCtoF(float c) {
  return c * 1.8 + 32;
}
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void setup() {

  connJoin();

  SerialUSB.begin(9600);
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
}

void loop() {

  String FtempInHex="";

  if (millis() > trigger) {  //This sets a delay of x seconds between sendind data.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      SerialUSB.println("Error reading temperature!");
    }
    else {
      float temperature = convertCtoF(event.temperature);
      int CtempInDec = temperature * 100;
      String FtempInHex = String(CtempInDec, HEX);
      sendData(myPort, FtempInHex);  //Sending specified port number and data.
      trigger = millis() + period;
    }
    
  }
  delay(delayMS);  // Delay between measurements.
}



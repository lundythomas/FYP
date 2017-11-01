// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            5         // Pin which is connected to the DHT sensor.

// Uncomment the type of sensor in use:
//#define DHTTYPE           DHT11     // DHT 11 
#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup() {
  SerialUSB.begin(9600); 
  // Initialize device.
  dht.begin();
  SerialUSB.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  SerialUSB.println("------------------------------------");
  SerialUSB.println("Temperature");
  SerialUSB.print  ("Sensor:       "); SerialUSB.println(sensor.name);
  SerialUSB.print  ("Driver Ver:   "); SerialUSB.println(sensor.version);
  SerialUSB.print  ("Unique ID:    "); SerialUSB.println(sensor.sensor_id);
  SerialUSB.print  ("Max Value:    "); SerialUSB.print(sensor.max_value); SerialUSB.println(" *C");
  SerialUSB.print  ("Min Value:    "); SerialUSB.print(sensor.min_value); SerialUSB.println(" *C");
  SerialUSB.print  ("Resolution:   "); SerialUSB.print(sensor.resolution); SerialUSB.println(" *C");  
  SerialUSB.println("------------------------------------");
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  SerialUSB.println("------------------------------------");
  SerialUSB.println("Humidity");
  SerialUSB.print  ("Sensor:       "); SerialUSB.println(sensor.name);
  SerialUSB.print  ("Driver Ver:   "); SerialUSB.println(sensor.version);
  SerialUSB.print  ("Unique ID:    "); SerialUSB.println(sensor.sensor_id);
  SerialUSB.print  ("Max Value:    "); SerialUSB.print(sensor.max_value); SerialUSB.println("%");
  SerialUSB.print  ("Min Value:    "); SerialUSB.print(sensor.min_value); SerialUSB.println("%");
  SerialUSB.print  ("Resolution:   "); SerialUSB.print(sensor.resolution); SerialUSB.println("%");  
  SerialUSB.println("------------------------------------");
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    SerialUSB.println("Error reading temperature!");
  }
  else {
    SerialUSB.print("Temperature: ");
    SerialUSB.print(event.temperature);
    SerialUSB.println(" *C");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    SerialUSB.println("Error reading humidity!");
  }
  else {
    SerialUSB.print("Humidity: ");
    SerialUSB.print(event.relative_humidity);
    SerialUSB.println("%");
  }
}

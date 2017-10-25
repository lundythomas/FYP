//  Tom Lundy
//  25/10/2017 17:00
//  V.1.11
//  Sends abcd up to server every 60 seconds.

unsigned char sending;
int pin_reset = 2;
unsigned int myPort = 10;  // Specify here which port you are using.
unsigned long myData1 = 43981; // Add your data in decimal here to send.
unsigned long trigger;
unsigned long period = 60000; // Period of Seconds x 1000 between sending data.
String SendCmd = "";

void conn()
{
  pinMode(pin_reset, OUTPUT);
  digitalWrite(pin_reset, LOW); // reset-disable RN2483.

  SerialUSB.begin(57600);

  delay(2000);
  digitalWrite(pin_reset, HIGH);
  sending = 0;

  Serial5.begin(57600);
  delay(3000);
  Serial5.print("mac join otaa\r\n");

  trigger = millis() + period;
}

String sendData (int port, int data)
{
  String p = "";
  p = port;
  String d = "";
  d = String(data, HEX); // convert dec data into hex for transport.
  String SendCmd = "mac tx uncnf " + p + " " + d + "\r\n";  // Here the tx command string is created.
  Serial5.print(SendCmd);

  /*if (check_response("ok"))
    {
    if (check_response("mac_tx_ok"))
    {
      success=true;
      SerialUSB.println("successfully sent - mac tx " + p + " " + d);
    }
    }

    if (success=false)
    {
    SerialUSB.println("failed to transmit");
    }*/

  return SendCmd;
}

void setup() {

  conn();
}

void loop() {

  if (millis() > trigger) {  //This sets a delay of 30 seconds between sendind data.
    sendData(myPort, myData1);  //Sending specified port number and data.
    trigger = millis() + period;
  }

  if (Serial5.available() > 0) {   // This is just for development purposes to see repsonses via SerialUSB.
    SerialUSB.write(Serial5.read());
  }
}


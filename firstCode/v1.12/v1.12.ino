//  Tom Lundy
//  27/10/2017
//  V.1.12

unsigned char sending;
int pin_reset = 2;
unsigned int myPort = 10;  // Specify here which port you are using.
unsigned long myData1 = 43981; // Add your data in decimal here to send.
unsigned long trigger;
unsigned long period = 20000; // Period of Seconds x 1000 between sending data.
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

  /*if (checkResponse("ok"))
  {
    if (checkResponse("accepted"))
    {
      SerialUSB.println("You are now connected to the PN Network!");
    }
  }
  else
  {
    SerialUSB.println("You are not connected!");
  }*/

  trigger = millis() + period;
}

String sendData (int port, int data)
{
  String p = "";
  p = port;
  String d = "";
  d = String(data, HEX);
  String SendCmd = "mac tx uncnf " + p + " " + d + "\r\n";
  Serial5.print(SendCmd);
  /*if (checkResponse("ok"))
  {
    if (checkResponse("mac_tx_ok"))
    {
      SerialUSB.println("Data sent ok!");
    }
  }
  else
  {
    SerialUSB.println("Data has NOT been sent!");
  }*/
  return SendCmd;
}

String readIn()
{
  String buffer = "";
  char ch;

  while (ch != '\n')
  {
    ch = Serial5.read();
    if ((ch != '\r') && (ch != '\n'))
    {
      buffer += ch;
    }
  }
  return buffer;
}

bool checkResponse(String expected)
{
  String resp = readIn();
  return resp == expected;
  resp = "";
}

void setup() {

  connJoin();
}

void loop() {
  if (millis() > trigger) {  //This sets a delay of x seconds between sendind data.
    sendData(myPort, myData1);  //Sending specified port number and data.
    trigger = millis() + period;
  }
}


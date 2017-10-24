// Tom's program v1.01
// Wed 18/10/2017

bool con = false;
char response[32];
int pin_reset = 2;
int pin_led = 13;
unsigned long trigger;
unsigned long period = 500;
unsigned char ledon;
unsigned char sending;
unsigned char started;

// Function to connect to the LoRa (PN) Network.
void conn()
{
  Serial5.print("mac join otaa\n\r");

  delay(5000);

  sendData(8, 2748);

  /*if (check_response("ok"))
    {
    if (check_response("accepted"))
    {
      con=true;
      SerialUSB.println("connection successful!");
      sendData(8, 2748);
    }
    else
    {
     SerialUSB.println("connection has failed!");
    }
    }*/
}

// function to check the response from the LoRa.
bool check_response(String expected)
{
  int i = 0;

  for (int i = 0; i < 32; i++)
  {
    char ch;

    do {
      ch = Serial5.read();

      if ((ch != '\r') || (ch != '\n'))
      {
        response[i++] = ch;

      }
    } while ((ch != '\n') && (i < 31));
    while (ch != '\n')
      ch = Serial5.read();
  }
  //return (response==expected);
}

void reset() //Function to reset the RN2483.
{
  Serial5.print("sys reset\n\r");
  SerialUSB.println("system reset");

}

bool sendData (int port, int data)
{
  bool success = false;
  String p = "";
  p = String(port, HEX);
  //convert data to HEX
  String d = "";
  d = String(data, HEX);

  String cmd = "mac tx uncnf " + p + " " + d + "\n\r";
  SerialUSB.println("Command sent: " + cmd + "\n\r");


  if (check_response("ok"))
  {
    if (check_response("mac_tx_ok"))
    {
      success = true;
      SerialUSB.println("successfully sent - mac tx " + p + " " + d);
    }
  }

  if (success = false)
  {
    SerialUSB.println("failed to transmit");
  }

  return success;

}

void setup() {

  pinMode(pin_reset, OUTPUT);
  digitalWrite(pin_reset, LOW); // reset-disable RN2483

  SerialUSB.begin(9600);
  while (!SerialUSB);
  SerialUSB.println("SerialUSB relay running...");

  pinMode(pin_led, OUTPUT);
  digitalWrite(pin_led, LOW);

  trigger = millis() + 2000;
  ledon = 0;
  sending = 0;
  started = 0;

  Serial5.begin(57600);
  while (!Serial5);
  SerialUSB.println("Serial5 relay running...");

  reset();
  delay(6000);
  conn();

  //time_t t = time.now() + 60000;

}

void loop() {

  if (Serial5.available() > 0) {
    SerialUSB.write(Serial5.read());
  }

  if (millis() > trigger) {
    if (!started) {
      SerialUSB.print(".");
      digitalWrite(pin_reset, HIGH); // enable RN2483
      started = 1;
    }
    if (ledon) {
      digitalWrite(pin_led, LOW);
      ledon = 0;
    }
    else {
      digitalWrite(pin_led, HIGH);
      ledon = 1;
    }
    trigger = millis() + period;
  }




}

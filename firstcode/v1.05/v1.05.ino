unsigned long trigger;
unsigned long period = 500;
unsigned char ledon;
unsigned char sending;
unsigned char started;
int pin_reset = 2;
int pin_led = 13;

bool con=false;

bool conn(){
  Serial5.print("mac join otaa\n\r");

  if (check_response("ok"))
      {
        if (check_response("accepted"))
        {
          con=true;
          SerialUSB.println("connection successful!");
        }
      }
      if (!connected)
      {
        SerialUSB.println("connection has failed!");
      }
}

// function to check the response from the LoRa.
  bool check_response(String expected)
  {
   int i=0;
   
    for (int i=0;i<32;i++)
    {
      char ch;

    do {
      ch=Serial5.read();
      
      if((ch!='\n') || (ch!='\r'))
      {
        response[i++]=ch;
        
      }
    }while ((ch!='\n') && (i<31));
      while(ch!='\n')
      ch=Serial5.read();
    }
   //return (response==expected);
  }

  bool reset()
  {
    Serial5.print("sys reset\n\r");
    SerialUSB.println("system reset");
    
  }

  bool send (int port, int data)
  {
    bool success=false;
    String p="";
    p = String(port, HEX);
    //convert data to HEX
    String d=""; 
    d = String(data, HEX);

    String cmd = "mac tx uncnf " + p + " " + d + "\n\r";

    
    if (check_response("ok"))
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
    }

    return success;
    
  }

void setup() {

  pinMode(pin_reset, OUTPUT);
  digitalWrite(pin_reset, LOW); // reset-disable RN2483

  SerialUSB.begin(57600);

  trigger = millis() + 2000;
  ledon = 0;
  sending = 0;
  started = 0;

  Serial5.begin(57600);


}

void loop() {

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

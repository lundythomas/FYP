// Tom's program v1.01
// Wed 18/10/2017

bool connected=false;
char response[32];

// Function to connect to the LoRa (PN) Network.
  bool conn()
  {
      Serial5.print("mac join otaa\r\n");
      
      if (check_response("ok"))
      {
        if (check_response("accepted"))
        {
          connected=true;
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
   int i;
   
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
    }
    //string res = response[i];

  
  }

  bool reset()
  {
    Serial5.print("sys reset");
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

    String cmd = "mac tx uncnf " + p + " " + d + "\r\n";

    
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

  Serial5.begin(57600);
  SerialUSB.begin(9600);

  reset();
  delay(6000);
  conn();  

  //time_t t = time.now() + 60000;

}

void loop() {

  delay(10000);
  
  send(8, 2748);

}

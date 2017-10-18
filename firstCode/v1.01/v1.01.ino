// Tom's program v1.01
// Wed 18/10/2017

bool connected=false;
String response[32];

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
   
    //for (int i=0;i<32;i++)
   // {
   //   response[i]=0;
   // }

    char ch;

    do {
      ch=Serial5.read();
      
      if((ch!='\n') || (ch!='\r'))
      {
        response[i++]=ch;
      }
    }while ((ch!='\n') && (i<31));

    
    
    return (response==expected); 
  }

  bool reset()
  {
    Serial5.print("sys reset");
    
  }

void setup() {

  Serial5.begin(57600);
  SerialUSB.begin(9600);

  reset();
  conn();  

}

void loop() {
  // put your main code here, to run repeatedly:

}

//Tom Lundy
//24/10/2017 19:15
//V.1.10
//Sends abcd up to server every 30 seconds.

unsigned char sending;
int pin_reset = 2;
unsigned int myPort = 10;  // Specify here which port you are using.
unsigned long myData1 = 43981; // Add your data in decimal here to send.
unsigned long trigger;
unsigned long period = 30000; // Period of Seconds x 1000 between sending data.
String SendCmd = "";

String sendData (int port, int data)
  {
    //bool success=false;
    String p="";
    //p = String(port, HEX); port number does not need to be in HEX.
    p=port;
    String d=""; 
    d = String(data, HEX); // convert dec data into hex for transport.
    String SendCmd = "mac tx uncnf " + p + " " + d + "\r\n";
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

   pinMode(pin_reset,OUTPUT);
   digitalWrite(pin_reset,LOW); // reset-disable RN2483

   SerialUSB.begin(57600);
 
   delay(2000);
   digitalWrite(pin_reset,HIGH);
   sending = 0;

   Serial5.begin(57600);
   delay(3000);
   Serial5.print("mac join otaa\r\n");

   trigger = millis()+period;
}

void loop() {

    if(millis() > trigger) {
      sendData(myPort, myData1);
      trigger = millis()+period;
    }
    
   if (Serial5.available()>0) {
      SerialUSB.write(Serial5.read());
   }
}


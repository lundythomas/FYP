unsigned char sending;
int pin_reset=2;

unsigned long trigger;
unsigned long period=10000;

unsigned long andy=2342;

/* bool check_response(String expected)
  {
    String response = "";
    char ch;

    while(Serial5.available()>0){
      if(ch!='\n' || ch!='\r'){
        SerialUSB.write(ch);
        response+=ch;
        ch = Serial5.read();
      }
    }

    SerialUSB.print(response==expected);
    return (response==expected);
    
    /*for (int i=0;i<32;i++)
    {
      char ch;
    do {
      ch=Serial5.read();
      
      if((ch!='\n') || (ch!='\r'))
      {
        response+=ch;
      }
    }while ((ch!='\n') && (i<31));
      //while(ch!='\n')
      //ch=Serial5.read();
    }
    SerialUSB.print(response==expected);
    return (response==expected);
  }*/

void setup() {

   pinMode(pin_reset,OUTPUT);
   digitalWrite(pin_reset,LOW); // reset-disable RN2483

   SerialUSB.begin(57600);
 
   delay(3000);
   digitalWrite(pin_reset,HIGH);
   sending = 0;

   Serial5.begin(57600);
   delay(3000);
   Serial5.print("mac join otaa\r\n");

   trigger = millis()+period;
}

void loop() {

    if(millis() > trigger) {
      Serial5.print("mac tx uncnf 8 9999\r\n");
      //check_response("ok");
      trigger = millis()+period;
    }
    
   
   if (Serial5.available()>0) {
      SerialUSB.write(Serial5.read());
   }
}




unsigned char sending;
int pin_reset=2;

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
}

void loop() {

 // char ch;

   /*if (SerialUSB.available()>0) {
      ch = SerialUSB.read();
      if (ch!='$') {
         if (!sending) {
            SerialUSB.print("Sending: ");
            sending = 1;
         }
         SerialUSB.write(ch);
         Serial5.write(ch);
      }
      else {
         SerialUSB.println("^M^J");
         sending = 0;
         Serial5.write(13);
         Serial5.write(10);
      }

      
   }*/
   
   //delay(2000);
   //Serial5.print("mac tx uncnf 8 7777\n\r");
   
   if (Serial5.available()>0) {
      SerialUSB.write(Serial5.read());
   }
}


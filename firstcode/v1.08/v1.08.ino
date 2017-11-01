unsigned char sending;
int pin_reset=2;

unsigned long trigger;
unsigned long period=15000;

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
      Serial5.print("mac tx uncnf 8 7777\r\n");
      trigger = millis()+period;
    }
    
   
   if (Serial5.available()>0) {
      SerialUSB.write(Serial5.read());
   }
}


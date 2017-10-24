//unsigned long trigger;
//unsigned long period=500;
//unsigned char ledon;
//unsigned char sending;
//unsigned char started;
//int pin_reset=2;
//int pin_led=13;

void setup() {

 //pinMode(pin_reset,OUTPUT);
 //digitalWrite(pin_reset,LOW); // reset-disable RN2483

 //pinMode(pin_led, OUTPUT);
 //digitalWrite(pin_led, LOW);
 
 Serial5.begin(57600);
 //Serial5.print("sys reset\n\r");
 SerialUSB.begin(9600);

 delay(5000);
 
 Serial5.print("mac join otaa");
 Serial5.write('\n');

 SerialUSB.print("here");

 delay(5000);

 Serial5.print("mac tx uncnf 8 7777");
 Serial5.write('\n');

 //trigger = millis() + 2000;
  // ledon = 0;
   //sending = 0;
   //started = 0;

}

void loop() {
  
//if (millis() > trigger) {
  //    if (!started) {
    //     SerialUSB.print(".");
      //   digitalWrite(pin_reset,HIGH); // enable RN2483
        // started = 1;
      //}
      //if (ledon) {
        // digitalWrite(pin_led, LOW);
         //ledon = 0;
      //}
      //else {
       //  digitalWrite(pin_led, HIGH);
        // ledon = 1;
      //}
      //trigger = millis()+period;
   //}
}

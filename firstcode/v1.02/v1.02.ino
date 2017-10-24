unsigned long trigger;
unsigned long period=500;
unsigned char ledon;
unsigned char sending;
unsigned char started;
int pin_reset=2;
int pin_led=13;

void conn()
  {
    Serial5.print("mac join otaa\r\n");
    SerialUSB.println("Connecting");
  }

 void sen()
  {
    Serial5.print("mac tx 10 uncnf 123\r\n");
    SerialUSB.println("sent");
  }

void setup() {

  pinMode(pin_reset,OUTPUT);
  digitalWrite(pin_reset,LOW); // reset-disable RN2483

  SerialUSB.begin(9600);
  while (!SerialUSB);
  SerialUSB.println("Serial relay running...");

  pinMode(pin_led, OUTPUT);
  digitalWrite(pin_led, LOW);

  trigger = millis() + 2000;
   ledon = 0;
   sending = 0;
   started = 0;
  
  Serial5.begin(57600);

  delay(3000);

  conn();
}

void loop() {

 char ch;

   if (SerialUSB.available()>0) {
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
   }
   if (Serial5.available()>0) {
      SerialUSB.write(Serial5.read());
   }

   if (millis() > trigger) {
      if (!started) {
         SerialUSB.print(".");
         digitalWrite(pin_reset,HIGH); // enable RN2483
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
      trigger = millis()+period;
   }

   delay(10000);

   sen();

}

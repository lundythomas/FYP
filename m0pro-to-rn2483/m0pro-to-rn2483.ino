//
// Relay data USBSerial<-->Serial5
//
// Works with USB Native port on Arduino M0 PRO and Tools->Serial Monitor
//
// Arduino 1.8.4
//

unsigned long trigger;
unsigned long period=500;
unsigned char ledon;
unsigned char sending;
unsigned char started;
int pin_reset=2;
int pin_led=13;

void setup() {

   pinMode(pin_reset,OUTPUT);
   digitalWrite(pin_reset,LOW); // reset-disable RN2483

   SerialUSB.begin(57600);
   while (!SerialUSB);
   SerialUSB.println("Serial relay running...");
   SerialUSB.println("Don't type anything until a . appears");
   SerialUSB.println("Note: you should then see the reset message: RN2483 0.9.5 Mar 24 14:15:33");
   SerialUSB.println("Then try typing: 'sys reset$' and click the send key");
   SerialUSB.println("Then enter: 'mac join otaa$");
   SerialUSB.println("And then enter: 'mac tx uncnf 10 123456$");
   SerialUSB.println("Note: the program converts $ to ^M^J");

   pinMode(pin_led, OUTPUT);
   digitalWrite(pin_led, LOW);

   trigger = millis() + 2000;
   ledon = 0;
   sending = 0;
   started = 0;

   Serial5.begin(57600);
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

}


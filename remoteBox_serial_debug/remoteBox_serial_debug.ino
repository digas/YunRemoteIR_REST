// This program allows an Arduino to power on/off a Duraflame heater using infrared
//
// Usage: hook up an IR led with Annode on pin 13.  Then send serial data "POWER"
// to the arduino.  It should flash the LED code.
//
// By Rick Osgood with code borrowed from adafruit.com
//
#include <IRremote.h>
IRsend irsend;

void setup(void) {
 
  Serial.begin(9600);            //Initialize Serial port
}

void loop() {
  char data[6];
  int index = 0;

  delay(1000);  //Serial input seems to need some kind of short delay or the data gets screwed up.

  while (Serial.available() > 0) {            //Loop if there data on the serial line
    if (index < 5) {                          //Make sure we don't overflow
      data[index] = Serial.read();            //Load a character into the string
      index++;                                //Increment the index to get the next character
    }
  }
  data[5]='\0';  //Null terminate the string
  
  if (strcmp(data, "kyPWR") == 0){
    irsend.sendNEC(0x1FC22DD, 32); // NEC TV power code
    Serial.println("Power");
    data[0]='\0';
  }
  if (strcmp(data, "curUP") == 0){
    irsend.sendNEC(0x1FC30CF, 32); // NEC TV power code
    Serial.println("cursor Up");
    data[0]='\0';
  }
    if (strcmp(data, "curDN") == 0){
    irsend.sendNEC(0x1FC708F, 32); // NEC TV power code
    Serial.println("cursor Down");
    data[0]='\0';
  }
  if (strcmp(data, "curOK") == 0){
    irsend.sendNEC(0x1FC8877, 32); // NEC TV power code
    Serial.println("cursor Ok");
    data[0]='\0';
  }
  delay(40);
}
//codigos
//
//curUP    1FC30CF
//curDN  1FC708F
//
//kyPwr  1FC22DD
//
//curOK    1FC8877
//key1    1FC6897
//key2    1FCE817


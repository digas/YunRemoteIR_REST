/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println("Codigo: ");
    Serial.println(results.value, HEX);
    switch (results.value) {
      case 0x1FC708F:
        Serial.println("curso baixo");
        break;
      case 0x1FC30CF:
        Serial.println("curso cima");
        break;
      case 0x1FC22DD:
        Serial.println("curso power");    
        break;
      case 0x1FC8877:
        Serial.println("curso ok");
        break;
      default:
        Serial.println("nada carregado");
    }
    irrecv.resume(); // Receive the next value
  }
}

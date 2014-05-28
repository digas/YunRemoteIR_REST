/*
  Arduino Yun Bridge example
 
 This example for the Arduino Yun shows how to use the 
 Bridge library to receive text through REST calls /url and 
 show the text in a SerialLCD 
 you can create your own API when using REST style 
 calls through the browser.
 
 use below commands to send string via REST calls

 * "/arduino/YOUR_TEXT"     
 
 */

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

// include the library code:
#include <IRremote.h>
#include <SoftwareSerial.h>

// Listen on default port 5555, the webserver on the Yun
// will forward there all the HTTP requests for us.
IRsend irsend;
YunServer server;

void setup() {
  // Bridge startup
  Bridge.begin();

  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();
  
}

void loop() {
  // Get clients coming from server
  YunClient client = server.accept();



  // There is a new client?
  if (client) {
    // Process request
    process(client);

    // Close connection and free resources.
    client.stop();
  }

  delay(50); // Poll every 50ms
}

void process(YunClient client) {
  // read the text from REST calls
  String text = client.readStringUntil('\r');
  
  //Convert the string to char array
  char data[text.length()+1];
  text.toCharArray(data,text.length()+1);
  
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

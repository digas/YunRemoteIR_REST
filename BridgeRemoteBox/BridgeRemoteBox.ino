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

  delay(100); // Poll every 100ms
}

void process(YunClient client) {
  // read the text from REST calls
  String text = client.readStringUntil('\r');
  // valor para pwr da TV samsung
  unsigned int S_pwr[68]={4600,4350,700,1550,650,1550,650,1600,650,450,650,450,650,450,650,450,700,400,700,1550,650,1550,650,1600,650,450,650,450,650,450,700,450,650,450,650,450,650,1550,700,450,650,450,650,450,650,450,650,450,700,400,650,1600,650,450,650,1550,650,1600,650,1550,650,1550,700,1550,650,1550,650};
  unsigned int SRC_tv[68]={4500,4400,600,1650,550,1650,550,1700,550,550,550,550,550,550,550,550,550,600,550,1650,550,1650,550,1700,550,550,550,550,550,550,550,550,550,550,550,1700,550,550,550,550,550,550,550,550,550,600,550,550,550,550,550,550,550,1650,550,1700,550,1650,550,1650,550,1700,550,1650,550,1650,550};
  unsigned int exit_tv[68]={4500,4400,600,1650,550,1650,550,1650,550,600,550,550,550,500,600,550,550,550,550,1700,550,1650,550,1650,550,550,550,550,600,550,550,500,600,500,600,1650,550,550,550,1700,550,1650,550,550,550,1650,550,600,550,550,550,550,550,1650,550,550,550,550,600,1650,550,550,550,1650,550,1700,550}; 
  
  //Convert the string to char array
  char data[text.length()+1];
  text.toCharArray(data,text.length()+1);
  
  if (strcmp(data, "satkPWR") == 0){
    irsend.sendNEC(0x1FC22DD, 32); // OpenBoxs9 power code
    Serial.println("sat Power");
    data[0]='\0';
  }
  if (strcmp(data, "Recall") == 0){
    irsend.sendNEC(0x1FC00FF, 32); // OpenBoxs9 recall channel
    Serial.println("Air is On");
    data[0]='\0';
  }
  if (strcmp(data, "curUP") == 0){
    irsend.sendNEC(0x1FC30CF, 32); // OpenBoxs9 cursor UP
    Serial.println("cursor Up");
    data[0]='\0';
  }
    if (strcmp(data, "curDN") == 0){
    irsend.sendNEC(0x1FC708F, 32); // OpenBoxs9 cursor Down
    Serial.println("cursor Down");
    data[0]='\0';
  }
  if (strcmp(data, "curOK") == 0){
    irsend.sendNEC(0x1FC8877, 32); // OpenBoxs9 cursor OK
    Serial.println("cursor Ok");
    data[0]='\0';
  }
  delay(40);
  if (strcmp(data, "tvkPWR") == 0){
    irsend.sendRaw(S_pwr,68,38); // Samsung TV power code
    Serial.println("TV POWER ON or OFF");
    data[0]='\0';
  }
  delay(40);
  if (strcmp(data, "curSRC") == 0){
    irsend.sendRaw(SRC_tv,68,38); // Samsung TV source button
    Serial.println("TV SOURCE Ok");
    data[0]='\0';
  }
  delay(40);
  if (strcmp(data, "curEXIT") == 0){
    irsend.sendRaw(exit_tv,68,38); // Samsung TV exit button
    Serial.println("TV Exit Ok");
    data[0]='\0';
  }
  delay(40);
  if (strcmp(data, "logiVolUP") == 0){
    irsend.sendNEC(0x10EF58A7, 32); // Logitech 5.1 volume UP code
    Serial.println("Volume UP");
    data[0]='\0';
  }
  if (strcmp(data, "logiVolDN") == 0){
    irsend.sendNEC(0x10EF708F, 32); // Logitech 5.1 volume UP code
    Serial.println("Volume Down");
    data[0]='\0';
  }
  delay(40);
  if (strcmp(data, "logiVolMute") == 0){
    irsend.sendNEC(0x10EF6897, 32); // Logitech 5.1 volume Mute code
    Serial.println("Volume Mute");
    data[0]='\0';
  }
  delay(40);
  if (strcmp(data, "teste") == 0){
    irsend.sendNEC(0x1FC8877, 32); // OpenBoxs9 cursor OK
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FC708F, 32); // OpenBoxs9 cursor curDN
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FC708F, 32); // OpenBoxs9 cursor curDN
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FC708F, 32); // OpenBoxs9 cursor curDN
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FC8877, 32); // OpenBoxs9 cursor OK
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FC8877, 32); // OpenBoxs9 cursor OK
    Serial.println("cursor OK down down ok ok");
    data[0]='\0';
  }
  delay(40);
  if (strcmp(data, "btvhd1") == 0){
    irsend.sendNEC(0x1FC6897, 32); // OpenBoxs9 cursor 1
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FCE817, 32); // OpenBoxs9 cursor 2
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FC6897, 32); // OpenBoxs9 cursor 1
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FC8877, 32); // OpenBoxs9 cursor OK
    data[0]='\0';
    delay(200);
    Serial.println("Canal 121 + ok");
    data[0]='\0';
  }
  delay(40);
  if (strcmp(data, "sportvhd1") == 0){
    irsend.sendNEC(0x1FC6897, 32); // OpenBoxs9 cursor 1
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FC6897, 32); // OpenBoxs9 cursor 1
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FC6897, 32); // OpenBoxs9 cursor 1
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FC8877, 32); // OpenBoxs9 cursor OK
    data[0]='\0';
    delay(200);
    Serial.println("Canal 111 + ok");
    data[0]='\0';
  }
  delay(40);
  if (strcmp(data, "sportvhd2") == 0){
    irsend.sendNEC(0x1FC6897, 32); // OpenBoxs9 cursor 1
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FC6897, 32); // OpenBoxs9 cursor 1
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FCE817, 32); // OpenBoxs9 cursor 2
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FC8877, 32); // OpenBoxs9 cursor OK
    data[0]='\0';
    delay(200);
    Serial.println("Canal 112 + ok");
    data[0]='\0';
  }
  delay(40);
  if (strcmp(data, "sportingtv") == 0){
    irsend.sendNEC(0x1FCD827, 32); // OpenBoxs9 cursor 6
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FC38C7, 32); // OpenBoxs9 cursor 7
    data[0]='\0';
    delay(200);
    irsend.sendNEC(0x1FC8877, 32); // OpenBoxs9 cursor OK
    data[0]='\0';
    Serial.println("Canal 67 + ok");
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

// Ar condicionado ligar NEC: 5676CA00
// Ar condicionado ligar NEC: 5606CA00










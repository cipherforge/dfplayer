#include <OneButton.h>
#include <DFRobotDFPlayerMini.h>
#include "SoftwareSerial.h"

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

SoftwareSerial mySoftwareSerial(4,5); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
ESP8266WebServer server ( 80 );
String content;   // web output 


#include "OneButton.h"
OneButton button3(D3, true);
OneButton button4(D4, true);
OneButton button5(D5, true);
OneButton button6(D6, true);
OneButton button7(D7, true);


void setup() {
  Serial.begin(115200);
  Serial.println();

 
  // link the doubleclick function to be called on a doubleclick event.  
  Serial.println("attach button"); 
  button3.attachClick(click3);
  button4.attachClick(click4);  
  button5.attachClick(click5);  
  button6.attachClick(click6); 
  button7.attachClick(click7); 
  
  WiFiManager wifiManager;
  //wifiManager.resetSettings();
  wifiManager.autoConnect("AutoConnectAP");
  
  if ( MDNS.begin ( "esp8266" ) ) {
    // got mdns
  }
  Serial.println("software serial begin");
  mySoftwareSerial.begin(9600);
  Serial.println("dfplayer setup begin");
  if (!myDFPlayer.begin(mySoftwareSerial)) { 
    // usless if we cant talk to the mp3 player
    while(true);
  }
  Serial.println("dfplayer setup complete");
   
  //Set serial communictaion time out 500ms
  myDFPlayer.setTimeOut(500); 

  server.on ( "/", handleRoot );
 
  server.on ( "/mp3/play", handlePlay);
  server.on ( "/mp3/pause", handlePause);
  server.on ( "/mp3/volume", handleVolume );
  
  
  server.on ( "/test.svg", drawGraph );
  server.onNotFound ( handleNotFound );
  server.begin();

  //myDFPlayer.loop(1);  //Loop the first mp3
  
  /*  
   myDFPlayer.next();  //Play next mp3
   myDFPlayer.previous();  //Play previous mp3
   myDFPlayer.loop(1);  //Loop the first mp3
   DFPlayer.advertise(3); //advertise specific mp3 in SD:/ADVERT/0003.mp3; File Name(0~65535)
   myDFPlayer.stopAdvertise(); //stop advertise
   myDFPlayer.randomAll(); //Random play all the mp3.
  */  

}

void click3() {
  Serial.println("dblclick 3 button"); 
  myDFPlayer.play(1);  
} 

void click4() {
  Serial.println("dblclick 4 button"); 
  myDFPlayer.play(2);  
} 

void click5() {
  Serial.println("dblclick 5 button"); 
  myDFPlayer.play(3);  
} 

void click6() {
  Serial.println("dblclick 6 button"); 
  myDFPlayer.play(4);    
} 
void click7() {
  Serial.println("dblclick 7 button"); 
  myDFPlayer.play(5);  
} 

void loop() {
  server.handleClient();
  
    // keep watching the push button:
  button3.tick();  
  button4.tick();
  button5.tick();
  button6.tick();
  button7.tick();
}

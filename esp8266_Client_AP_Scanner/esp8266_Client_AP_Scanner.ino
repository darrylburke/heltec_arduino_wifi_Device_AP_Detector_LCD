// by Ray Burnette 20161013 compiled on Linux 16.3 using Arduino 1.6.12 
#include <ESP8266WiFi.h> 
bool doprint = true;
#include "./heltecLCD.h"
#include "./functions.h" 

#define disable 0 
#define enable  1 
// uint8_t channel = 1; 
unsigned int channel = 1; 


void setup() { 
 Serial.begin(115200); 


  heltecLCDsetup();
  heltecDrawBC();
  delay(500);
  heltecDrawMacSniffer();
  delay(3000);
  
  
  heltecLCDClear();

 
if(doprint) Serial.printf("\n\nSDK version:%s\n\r", system_get_sdk_version()); 
if(doprint)  Serial.println(F("Original ESP8266 mini-sniff by Ray Burnette http://www.hackster.io/rayburne/projects")); 
if(doprint)  Serial.println(F("Type:   /-------MAC------/-----WiFi Access Point SSID-----/  /----MAC---/  Chnl  RSSI")); 
 wifi_set_opmode(STATION_MODE);            // Promiscuous station mode 
 wifi_set_channel(channel); 
 wifi_promiscuous_enable(disable); 
 wifi_set_promiscuous_rx_cb(promisc_cb);   // Set up promiscuous callback 
 wifi_promiscuous_enable(enable); 
} 
void loop() { 
 channel = 1; 

 wifi_set_channel(channel); 
 while (true) { 
   nothing_new++;                          // Check bounds 
   if (nothing_new > 250) { 
    heltecDisplayMsg("a",2000,0,false,true);
     nothing_new = 0; 
     channel++; 
     if (channel == 15) break;             // Only scan channels 1 to 14 
     wifi_set_channel(channel); 
   } 
   delay(1);                              // critical processing timeslice 
 } 
}

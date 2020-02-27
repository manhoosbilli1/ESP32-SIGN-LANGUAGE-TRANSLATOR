#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
BlynkTimer timer;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "EcMKFw5c5xLG9FA2K4-VEvyuqnF0kypw";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Shoaib";
char pass[] = "A0123456789";
String latitude, longitude, com,COM;
WidgetMap myMap(V0);
unsigned int move_index = 1;
String command;         //using serial 2 to receive data
 
void pushData() {

  Blynk.virtualWrite(V3, COM);
  Blynk.virtualWrite(V4, latitude);
  Blynk.virtualWrite(V5, longitude);
  myMap.location(move_index, latitude, longitude, "GPS_LOCATION");
  Serial.print("Data uploaded");
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  Blynk.begin(auth,ssid,pass);
  timer.setInterval(3000L, pushData);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial2.available()) {
    String c = Serial2.readString();
    Serial.println(c);
    parseData(c);
  }
  
  Blynk.run();
  timer.run();
}

void parseData(String com) {   //data structure lat,long`cmd

  latitude = com.substring(com.indexOf('#')+1, com.indexOf(','));           //read the string from 0th index up until the space but not including
  longitude = com.substring(com.indexOf(',') + 1, com.indexOf('`'));       //read from the space but not including
  COM= com.substring(com.indexOf('`') +1);
  Serial.println(latitude);
  Serial.println(longitude);
  Serial.println(COM);
}

#include <Blynk.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <BlynkSimpleEsp32.h>
#define BLYNK_PRINT Serial
WidgetMap myMap(V0);  // V0 for virtual pin of Map Widget
BlynkTimer timer;
TinyGPSPlus gps;
HardwareSerial SerialGPS(1);      //look into what this instantiation does

#define TASK_SERIAL_RATE 100
uint32_t nextSerialTaskTs = 0;
uint32_t nextOledTaskTs = 0;
char auth[] = "U3R3NQltBEZUOfRckVj317_z1MqCPCWM";
char ssid[] = "Mi A2 Lite-Shoaib";
char pass[] = "D01234567890";
float lat_val = 22.44556667;
float long_val = 15.233665346;
const int led = 13;
float sats;      //Variable to store no. of satellites response
float longitude;                                       //these are the values you need to change..just throw in real gps value into this variable and the program should do the rest
float latitude;
unsigned int move_index = 1;       // fixed location for now
void checkGPS() {
  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    Blynk.virtualWrite(V4, "GPS ERROR");  // Value Display widget  on V4 if GPS not detected
  }
}

void displayInfo() {
  if (gps.location.isValid() )
  {
    float latitude = (gps.location.lat());     //Storing the Lat. and Lon.
    float longitude = (gps.location.lng());
    Serial.print("LAT:  ");
    Serial.println(latitude, 6);  // float to x decimal places
    Serial.print("LONG: ");
    Serial.println(longitude, 6);
    Blynk.virtualWrite(V1, String(lat_val, 6));
    Blynk.virtualWrite(V2, String(long_val, 6));
    myMap.location(move_index, latitude, longitude, "GPS_Location");
    sats = gps.satellites.value();    //get number of satellites
    Blynk.virtualWrite(V4, sats);
  }
  Serial.println();
}

//look into qumotile library from esp git

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);       //tx rx pins
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, checkGPS); // every 5s check if GPS is connected, only really need
}


void loop(void) {
  while (SerialGPS.available() > 0)
  {
    // sketch displays information every time a new sentence is correctly encoded.
    if (gps.encode(SerialGPS.read()))
      displayInfo();
  }
  Blynk.run();
  timer.run();
}

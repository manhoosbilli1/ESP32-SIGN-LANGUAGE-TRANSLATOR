#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define  BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

TinyGPSPlus gps;
SoftwareSerial  ss(4, 5);
char auth[] = "EcMKFw5c5xLG9FA2K4-VEvyuqnF0kypw";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Mi A2 Lite-Shoaib";
char pass[] = "D01234567890";
String command = "BED";
float latitude = 22.367787;
float longitude = 01.496638;
String lat_str;
String lng_str;
void checkGPS() {

  Blynk.virtualWrite(V3, command);
  Blynk.virtualWrite(V4, lat_str);
  Blynk.virtualWrite(V5, lng_str);
}

void setup()
{
  // Debug console
  ss.begin(9600);
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT); //Set the LED (D8) as an output
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, checkGPS);

}

void loop()
{
  if(arduino.available()) {
    command = Serial.readString();
  }
  while (ss.available() > 0) //while data is available
    if (gps.encode(ss.read())) //read gps data
    {
      if (gps.location.isValid()) //check whether gps location is valid
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6); // latitude location is stored in a string
        longitude = gps.location.lng();
        lng_str = String(longitude , 6); //longitude location is stored in a string
      }
    }
      Blynk.run();
      timer.run();

    }

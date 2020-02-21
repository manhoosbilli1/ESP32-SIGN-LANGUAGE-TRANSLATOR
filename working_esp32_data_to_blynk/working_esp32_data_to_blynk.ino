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
float latitude;
float longitude; 

void uploadData() {

  Blynk.virtualWrite(V3, command);
  Blynk.virtualWrite(V4, latitude);
  Blynk.virtualWrite(V5, longitude);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Serial2.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); //Set the LED (D8) as an output
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, uploadData);

}

void loop()
{
  if (Serial2.available() > 0) {          //GATHER DATA FROM SERIAL PORT
    char c = Serial.read();
    if (c == '\n') {             //when the command is finished it will feed that data into the function
      parseData(command);
      command = "";                //empty command
    } else {
      command += c;                 //else add to the string
    }
  }
  Blynk.run();                           //PUSH DATA TO APP 
  timer.run(); 

}

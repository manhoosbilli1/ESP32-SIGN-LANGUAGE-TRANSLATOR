#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"

//save the wav files with the same same as the command or speech
char *filename = "";
char *lastFN =""; 
//other variables
char*lastS;
bool cmd1Flag, cmd2Flag,cmd3Flag,cmd4Flag,cmd5Flag,cmd6Flag,playFlag,timerFlag;
String command, com,lastPath;
unsigned long lastTrigger,timer;             //timers
float latitude, longitude;                                         //for gps

//flex sensor
#define fingerPin1 A0
const int minimumVal1;
const int maximumVal1;

#define fingerPin2 A1                // sensors one leg to vcc via a 10k resistor.connect node of 10k resistor and sensor leg to input pin. and the other to ground
const int minimumVal2;
const int maximumVal2;

#define fingerPin3 A2
const int minimumVal3;
const int maximumVal3;

#define fingerPin4 A6
const int minimumVal4;
const int maximumVal4;

#define fingerPin5 A7
const int minimumVal5;
const int maximumVal5;

//-------------


//instantiations and initializations
#define SD_ChipSelectPin 10
LiquidCrystal_I2C lcd(0x27,16,2);
TMRpcm tmrpcm;
SoftwareSerial esp(4, 5);   //4rx 5tx
SoftwareSerial SerialGPS(6, 7); //6rx 7tx
TinyGPSPlus gps;
//---------------


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  esp.begin(9600);
  SerialGPS.begin(9600);
  tmrpcm.speakerPin = 9;
  tmrpcm.setVolume(3);
  tmrpcm.loop(0);                        //turn off audio looping
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Command:      ");
  lcd.setCursor(0, 1);
  if (!SD.begin(SD_ChipSelectPin)) {
    return;
  }


}

void loop() {
  // put your main code here, to run repeatedly:
  poseCalculator();                                              //calculates hand pose by measuring flex sensor and assigning it a command..then feeds it to say command which speaks
  gpsHandler();                                                  //gets lat and long positions
  if (millis() - lastTrigger > 2000) {                            //will continously print to serial every 2 second with values
    command_encoder(latitude, longitude, com);
    lastTrigger = millis();
  }
}

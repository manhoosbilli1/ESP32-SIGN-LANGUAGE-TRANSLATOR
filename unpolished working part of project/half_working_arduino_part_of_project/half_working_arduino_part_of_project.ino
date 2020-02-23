#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"
#include <Wire.h>
//save the wav files with the same same as the command or speech

bool cmd1Flag, cmd2Flag, cmd3Flag, cmd4Flag, cmd5Flag, cmd6Flag, playFlag, timerFlag;
String command = "";
String com, lastPath, lastS;
float latitude, longitude;
unsigned long lastTrigger, timer;            //timers
//flex sensor
#define fingerPin1 A2
const int minimumVal1 = 465;
const int maximumVal1 = 485;

#define fingerPin2 A1                // sensors one leg to vcc via a 10k resistor.connect node of 10k resistor and sensor leg to input pin. and the other to ground
const int minimumVal2 = 485 ;
const int maximumVal2 = 492 ;

#define fingerPin3 A0
const int minimumVal3 = 450;
const int maximumVal3 = 460;


//-------------


//instantiations and initializations
#define SD_ChipSelectPin 10
LiquidCrystal_I2C lcd(0x27, 16, 2);
TMRpcm tmrpcm;
SoftwareSerial esp(4, 5);   //4rx 5tx
SoftwareSerial SerialGPS(6, 7); //6rx 7tx
TinyGPSPlus gps;
//---------------


void setup() {
  // put your setup code here, to run once:
  tmrpcm.speakerPin = 3;
  Serial.begin(9600);
  esp.begin(9600);
  SerialGPS.begin(9600);


  // tmrpcm.loop(0);                        //turn off audio looping
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Command:      ");
  lcd.setCursor(0, 1);
  if (!SD.begin(SD_ChipSelectPin)) {
    return;
  }
  delay(100);
  tmrpcm.setVolume(3);
  tmrpcm.play("A.wav");
  delay(1000);
}

void loop() {
  //getting ADC reading
  int finger1 = analogRead(fingerPin1);
  int finger2 = analogRead(fingerPin2);
  int finger3 = analogRead(fingerPin3);
  bool Finger1, Finger2, Finger3;

  //mapping values
  if (finger1 <= minimumVal1) {
    Finger1 = 1;
  } else if (finger1 >= maximumVal1) {
    Finger1 = 0;
  }
  if (finger2 <= minimumVal2) {
    Finger2 = 1;
  } else if (finger2 >= maximumVal2) {
    Finger2 = 0;
  }
  if (finger3 <= minimumVal3) {
    Finger3 = 1;
  } else if (finger3 >= maximumVal3) {
    Finger3 = 0;
  }

  if (Finger1 == 1 && Finger2 == 1 && Finger3 == 1) {
    say("bed");
  } else if (Finger1 == 0 && Finger2 == 1 && Finger3 == 1) {

  } else if (Finger1 == 0 && Finger2 == 1 && Finger3 == 0) {

  } else if (Finger1 == 1 && Finger2 == 0 && Finger3 == 0) {

  } else if (Finger1 == 0 && Finger2 == 0 && Finger3 == 0) {
    say("sleep");
  }                                              //calculates hand pose by measuring flex sensor and assigning it a command..then feeds it to say command which speaks
  //  gpsHandler();                                                  //gets lat and long positions

  if (millis() - lastTrigger > 2000) {                            //will continously print to serial every 2 second with values
    command_encoder(23.2767676, 12.2336667, "Hello esp");
    lastTrigger = millis();
    Serial.println("data sent");
  }

}

//this will print to lcd, feed the com string to send to esp, and also say it using speaker
char* string2char(String command) {
  if (command.length() != 0) {
    char *p = const_cast<char*>(command.c_str());
    return p;
  }
}

void say(String s) {
  char* filename;
  if (s != lastS) {                      //if command has changed
    String i = s;                        //make a string i concat the space and feed to function
    i += "               ";
    lcd.setCursor(0, 1);                 //print to lcd
    lcd.print(i);
    com = s;
    String wavPath = s;                  //setting up the filename string here
    wavPath += ".wav";
    filename = string2char(wavPath);      //feeding it to filename to convert to char
    playFlag = true;
    timerFlag = true;
    lastS = s;                           //save the current command to compare later
  }
  if (playFlag) {
    if (timerFlag) {                                                                      //DIDNT WORK CAUSE OF FILEPATH CHAR
      timer = millis();                  //record the time
      timerFlag = false;
    }
    tmrpcm.play(filename);               //if timer expires or if audio is not playing anymore
    if ((millis() - timer > 1000) || (!tmrpcm.isPlaying())) {        //get out of the loop
      playFlag = false;
    }
  } else {
    tmrpcm.stopPlayback();              //stop the music if not already stopped
  }
}

#include <LiquidCrystal_I2C.h>
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
unsigned long lastTrigger, lastTrigger1, lastTrigger2, timer;         //timers
;
//flex sensor
#define fingerPin1 A0
int minimumVal1 = 850;
int maximumVal1 = 930;

#define fingerPin2 A6                // sensors one leg to vcc via a 10k resistor.connect node of 10k resistor and sensor leg to input pin. and the other to ground
int minimumVal2 = 930 ;
int maximumVal2 = 960 ;

#define fingerPin3 A5
int minimumVal3 = 835;
int maximumVal3 = 865;


//-------------
bool Finger1, Finger2, Finger3;
int finger1, finger2, finger3;

//instantiations and initializations
#define SD_ChipSelectPin 53
LiquidCrystal_I2C lcd(0x27, 16, 2);
TMRpcm tmrpcm;
//serial2 is esp
//serial3 is gps
TinyGPSPlus gps;
bool test = false;
//---------------

String path;
void setup() {
  // put your setup code here, to run once:
  tmrpcm.speakerPin = 11;
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial3.begin(9600);   //esp


  // tmrpcm.loop(0);                        //turn off audio looping
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Command:      ");
  lcd.setCursor(0, 1);
  //tmrpcm.loop(0);
  if (!SD.begin(SD_ChipSelectPin)) {
    return;
  }
  delay(100);
  tmrpcm.setVolume(7);
  tmrpcm.quality(0);

}


void loop() {
  //getting ADC reading
  finger1 = analogRead(fingerPin1);
  finger2 = analogRead(fingerPin2);
  finger3 = analogRead(fingerPin3);



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

  lcd.setCursor(9, 0);
  lcd.print(Finger1);
  lcd.print(",");
  lcd.print(Finger2);
  lcd.print(",");
  lcd.print(Finger3);
  delay(10);

  Serial.println("In loop");
  if (Finger1 == 1 && Finger2 == 1 && Finger3 == 1) {
    cmd1Flag = true;
    path = "A.wav";
  } else if (Finger1 == 0 && Finger2 == 1 && Finger3 == 1) {
    cmd2Flag = true;
    path = "B.wav";
  } else if (Finger1 == 0 && Finger2 == 1 && Finger3 == 0) {
    cmd3Flag = true;
    path = "C.wav";
  } else if (Finger1 == 1 && Finger2 == 0 && Finger3 == 0) {
    cmd4Flag = true;
    path = "D.wav";
  } else if (Finger1 == 0 && Finger2 == 0 && Finger3 == 0) {
    cmd5Flag = true;
    path = "E.wav";

  }
  if (path != lastPath) {
    if (cmd1Flag) {
      lcd.setCursor(0, 1);
      lcd.print("Command 1         ");
      com = "command 5";
      tmrpcm.play("A.wav");
      Serial.print("playing A.wav");
      cmd1Flag = false;
    } else if (cmd2Flag) {
      lcd.setCursor(0, 1);
      lcd.print("Command 2         ");
      com = "command 2";
      tmrpcm.play("B.wav");
      Serial.print("Playing B.wav");
      cmd2Flag = false;
    } else if (cmd3Flag) {
      lcd.setCursor(0, 1);
      lcd.print("Command 3         ");
      tmrpcm.play("C.wav");
      com = "command 3";
      Serial.print("Playing C.wav");
      cmd3Flag = false;
    } else if (cmd4Flag) {
      lcd.setCursor(0, 1);
      lcd.print("Command 4         ");
      com = "command 4";
      tmrpcm.play("D.wav");
      Serial.print("Playing D.wav");
      cmd4Flag = false;
    } else if (cmd5Flag) {
      lcd.setCursor(0, 1);
      lcd.print("Command 5         ");
      com = "command 5";
      tmrpcm.play("E.wav");
      Serial.print("Playing E.wav");
      cmd5Flag = false;
    }
    lastPath = path;
  }
  if (millis() - lastTrigger >= 2000) {                            //will continously print to serial every 2 second with values
    command_encoder(latitude, longitude, com);
    lastTrigger = millis();
    Serial.println("data sent");
  }
  while (Serial1.available() > 0) {
    gps.encode(Serial1.read());
    if (gps.location.isUpdated()) {
      latitude = gps.location.lat();
      longitude = gps.location.lng();
    }
  }

}//calculates hand pose by measuring flex sensor and assigning it a command..then feeds it to say command which speaks
//  gpsHandler();                                                  //gets lat and long positions




void command_encoder(float lati, float longi, String com) {
  char latitude[12];
  char longitude[12];
  Serial3.print('#');
  dtostrf(lati, 9, 6, latitude);      //convert to char
  Serial3.print(latitude);
  Serial3.print(',');
  dtostrf(longi, 9, 6, longitude);
  Serial3.print(longitude);
  Serial3.print('`');
  Serial3.print(com);
  Serial.print('\n');
}
/*
  //this will print to lcd, feed the com string to send to esp, and also say it using speaker
  char* string2char(String command) {
  if (command.length() != 0) {
    char *p = const_cast<char*>(command.c_str());
    return p;
  }
  }

  void say(String s) {                  //NEW FUNCTION UNCONFIRMED
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

  /*
  void playAudio(String path) {       //turn on flag when you want to play

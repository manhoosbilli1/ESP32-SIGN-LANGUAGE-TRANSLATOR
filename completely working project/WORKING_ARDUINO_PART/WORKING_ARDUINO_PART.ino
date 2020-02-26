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
unsigned long lastTrigger, lastTrigger1, lastTrigger2, timer, lastTrigger3;        //timers
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

TinyGPSPlus gps;
//---------------

String path;
void setup() {
  // put your setup code here, to run once:
  tmrpcm.speakerPin = 11;
  Serial.begin(9600);    //SERIAL MONITOR
  Serial1.begin(9600);   //GPS
  Serial3.begin(9600);   //esp
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Command:      ");
  lcd.setCursor(0, 1);
  if (!SD.begin(SD_ChipSelectPin)) {
    return;
  }
  delay(100);
  tmrpcm.setVolume(7);
  tmrpcm.quality(0);
}

void loop() {
  // ----------------------------GETS ADC VALUES AND ASSISNS THEM TO BINARY--------------------
  if (millis() - lastTrigger3 > 200) {
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

    //--------------------------SHOWS FINGERS POSITION ON LCD

    lcd.setCursor(9, 0);
    lcd.print(Finger1);
    lcd.print(",");
    lcd.print(Finger2);
    lcd.print(",");
    lcd.print(Finger3);

    //1 IS FINGERS EXTENDED AND FLAT 0 IS FINGERS CURLED AND BENT
    //assign values to finger positions

    if (Finger1 == 1 && Finger2 == 1 && Finger3 == 1) {
      cmd1Flag = true;
      path = "a";
    } else if (Finger1 == 0 && Finger2 == 1 && Finger3 == 1) {
      cmd2Flag = true;
      path = "b";
    } else if (Finger1 == 0 && Finger2 == 1 && Finger3 == 0) {
      cmd3Flag = true;
      path = "c";
    } else if (Finger1 == 1 && Finger2 == 0 && Finger3 == 0) {
      cmd4Flag = true;
      path = "d";
    } else if (Finger1 == 0 && Finger2 == 0 && Finger3 == 0) {
      cmd5Flag = true;
      path = "e";
    }
    lastTrigger3 = millis();
  }

  //           ***********************actual code***************************  set lcd to value, prints to serial, and plays the sound
  if (path != lastPath) {
    if (!tmrpcm.isPlaying() || (millis() - lastTrigger2 > 500)) {
      if (cmd1Flag) {
        lcd.setCursor(0, 1);
        lcd.print("FOOD           ");
        com = "FOOD";
        tmrpcm.play("food.wav");
        cmd1Flag = false;
      } else if (cmd2Flag) {
        lcd.setCursor(0, 1);
        lcd.print("SLEEP           ");
        com = "SLEEP";
        tmrpcm.play("B.wav");
        Serial.print("Playing B.wav");
        cmd2Flag = false;
      } else if (cmd3Flag) {
        lcd.setCursor(0, 1);
        lcd.print("PEE         ");
        tmrpcm.play("C.wav");
        com = "PEE";
        cmd3Flag = false;
      } else if (cmd4Flag) {
        lcd.setCursor(0, 1);
        lcd.print("DRINK        ");
        com = "DRINK";
        tmrpcm.play("D.wav");
        cmd4Flag = false;
      } else if (cmd5Flag) {
        lcd.setCursor(0, 1);
        lcd.print("OUTSIDE        ");
        com = "OUTSIDE";
        tmrpcm.play("E.wav");
        cmd5Flag = false;
      }
      lastTrigger2 = millis();
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
}

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

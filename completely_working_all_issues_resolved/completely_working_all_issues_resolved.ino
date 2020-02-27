#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"
#include <Wire.h>


//the finger movement assigns an int value to the cmd and we correlate that with the filename and command array so whatever 
//value cmd is the other char array will choose that index. 


int cmd, lastCmd;      // main int value
char *filename[] = {"", "A.wav", "B.wav", "C.wav", "D.wav", "E.wav","F.wav"};     //last position is going to be null character
String command[] = {"", "Food", "Sleep", "Drink", "PEE", "important","outside"};

String com, lastPath, lastS;
float latitude, longitude;
unsigned long lastTrigger, lastTrigger1, lastTrigger2, timer, lastTrigger3, playingTimer;       //timers
;
//flex sensor
#define fingerPin1 A7
int minimumVal1 = 850;
int maximumVal1 = 960;

#define fingerPin2 A6                // sensors one leg to vcc via a 10k resistor.connect node of 10k resistor and sensor leg to input pin. and the other to ground
int minimumVal2 = 950;
int maximumVal2 = 980;

#define fingerPin3 A0
int minimumVal3 = 830;
int maximumVal3 = 900;


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
  lcd.print("COMMAND:");
  lcd.setCursor(0, 1);
  if (!SD.begin(SD_ChipSelectPin)) {
    return;
  }
  delay(100);
  tmrpcm.setVolume(3 );
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
    lcd.print("       ");

    //1 IS FINGERS EXTENDED AND FLAT 0 IS FINGERS CURLED AND BENT
    //assign values to finger positions

    if (Finger1 == 1 && Finger2 == 1 && Finger3 == 1) {
      cmd = 0;
    } else if (Finger1 == 0 && Finger2 == 1 && Finger3 == 1) {
      cmd = 1;
    } else if (Finger1 == 0 && Finger2 == 1 && Finger3 == 0) {
      cmd = 2;
    } else if (Finger1 == 1 && Finger2 == 0 && Finger3 == 0) {
      cmd = 3;
    } else if (Finger1 == 0 && Finger2 == 0 && Finger3 == 0) {
      cmd = 4;
    } else if (Finger1 == 0 && Finger2 == 0  && Finger3 == 1) {
      cmd = 5;
    } else if (Finger1 == 1 && Finger2 == 0  && Finger3 == 1) {
      cmd = 6;
    }
    lastTrigger3 = millis();
  }

  //           ***********************actual code***************************  set lcd to value, prints to serial, and plays the sound
  if (cmd != lastCmd) {
    tmrpcm.play(filename[cmd]);
    lcd.setCursor(0, 1);
    lcd.print(command[cmd]);
    lcd.print("        ");
    com = command[cmd];
    lastCmd = cmd;
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

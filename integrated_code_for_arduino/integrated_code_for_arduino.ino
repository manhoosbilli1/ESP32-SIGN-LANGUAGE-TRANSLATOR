#include <LiquidCrystal_I2C.h>

//libraries
#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"

                                          //save the wav files with the same same as the command or speech
String command, com;
unsigned long lastTrigger, lastTrigger1, lastTrigger2;             //timers
float latitude, longitude;                                         //for gps
bool playedOnce = false;
unsigned int counter, prevCounter;
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
TMRpcm tmrpcm;
LiquidCrystal lcd(16, 2);
//---------------


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  tmrpcm.speakerPin = 9;
  tmrpcm.setVolume(3);
  tmrpcm.loop(0);                        //turn off audio looping
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Command:      ");
  lcd.setCursor(0, 1);
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    return;   // don't do anything more if not
  }


}

void loop() {
  // put your main code here, to run repeatedly:
  pose_calculator();
  gps_handler();
  if (millis() - lastTrigger > 2000) {                            //will continously print to serial every 2 second with new values
    command_encoder(latitude, longitude, com);
    lastTrigger = millis();
  }

}

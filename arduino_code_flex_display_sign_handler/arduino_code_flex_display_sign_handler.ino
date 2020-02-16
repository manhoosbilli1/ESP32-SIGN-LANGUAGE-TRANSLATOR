#include <LiquidCrystal.h>

//mpu 6050 settings
#include <Wire.h>


//lcd
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

//sd and audio
#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"
TMRpcm tmrpcm;

//button and sensors

#define FLEX_PIN1 A0
int flexADC1 = 0;
int sensorMin1 = 1023;
int sensorMax1 = 0;

#define FLEX_PIN2 A2
int flexADC2 = 0;
int sensorMin2 = 1023;
int sensorMax2 = 0;

#define FLEX_PIN3 A1
int flexADC3 = 0;
int sensorMin3 = 1023;
int sensorMax3 = 0;
#define button 2      //pin undefined

//flags and extra variables
bool cmd1Flag = false;
bool cmd2Flag, cmd3Flag, cmd4Flag, cmd5Flag, cmd6Flag;
String path;
String lastPath;
#define speaker_pin
unsigned long lastTrigger;
bool timerRunning = false;
bool finger1, finger2, finger3;

void setup() {
  // put your setup code here, to run once
  tmrpcm.speakerPin = 9;
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Command:      ");
  lcd.setCursor(0, 1);
  Serial.begin(9600);
  delay(20);
  pinMode(button, INPUT_PULLUP);
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    return;   // don't do anything more if not
  }
  tmrpcm.volume(7);

}


void loop() {

  readAndPrint();

}

void playAudio(String path) {       //turn on flag when you want to play
  if (path != lastPath) {
    if (path == "tea") cmd1Flag = true;
    if (path == "food") cmd2Flag = true;
    if (path == "bed") cmd3Flag = true;
    if (path == "pee") cmd4Flag = true;
    if (path == "sleep") cmd5Flag = true;
    if (path == "cmd6") cmd6Flag = true;
    if (cmd1Flag) {
      tmrpcm.play("A.wav");  //for 'ok' sign
      delay(1000);
      cmd1Flag = false;
    }
    else if (cmd2Flag) {
      tmrpcm.play("B.wav");    // for 1 sign
      delay(1000);
      cmd2Flag = false;
    }
    else if (cmd3Flag) {
      tmrpcm.play("C.wav");
      delay(1000);
      cmd3Flag = false;
    }
    else if (cmd4Flag) {
      tmrpcm.play("D.wav");
      delay(1000);
      cmd4Flag = false;
    }
    else if (cmd5Flag) {
      tmrpcm.play("E.wav");
      delay(1000);
      cmd5Flag = false;
    }
    else if (cmd6Flag) {
      tmrpcm.play("command1.wav");
      delay(1000);
      cmd6Flag = false;
    }
    lastPath = path;
  }
}


void readAndPrint() {
  int flexADC1 = analogRead(FLEX_PIN1);
  int flexADC2 = analogRead(FLEX_PIN2);
  int flexADC3 = analogRead(FLEX_PIN3);

  int angle1 = map(flexADC1, 0, 1023, 0, 90);
  int angle2 = map(flexADC2, 0, 1023, 0, 90);
  int angle3 = map(flexADC3, 0, 1023, 0, 90);

  if (angle1 > 12) finger1 = 1;   //finger is up
  if (angle1 < 7) finger1 = 0;   //finger is down

  if (angle2 > 7) finger2 = 1;
  if (angle2 < 4) finger2 = 0;

  if (angle3 > 15) finger3 = 1;
  if (angle3 < 12) finger3 = 0;
  if (finger1 == 1 && finger2 == 1 && finger3 == 0) {  //110
    lcd.setCursor(0, 1);
    lcd.print("BED        ");
    Serial.println("BED");
    playAudio("bed");                        //play bed.wav
  } else if (finger1 == 1 && finger2 == 0 && finger3 == 1) { //100
    lcd.setCursor(0, 1);
    lcd.print("TEA        ");
    Serial.println("TEA");
    playAudio("tea");
  } else if (finger1 == 0 && finger2 == 1 && finger3 == 1) { //100
    lcd.setCursor(0, 1);
    lcd.print("FOOD        ");
    Serial.println("FOOD");
    playAudio("food");
  } else if (finger1 == 1 && finger2 == 0 && finger3 == 0) { //100
    lcd.setCursor(0, 1);
    lcd.print("PEE        ");
    Serial.println("PEE");
    playAudio("pee");
  } else if (finger1 == 1 && finger2 == 1 && finger3 == 1) {
    lcd.setCursor(0, 1);
    lcd.print("             ");
  }
}

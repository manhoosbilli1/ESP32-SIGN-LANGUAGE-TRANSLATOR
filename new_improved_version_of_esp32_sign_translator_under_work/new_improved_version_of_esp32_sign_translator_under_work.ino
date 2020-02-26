#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"
#include <Wire.h>


//mpu6050
#define MPU 0x68
long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;
long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;

//save the wav files with the same same as the command or speech
int cmd;       // main int value
char *filename[6] = {"", "A.wav", "B.wav", "C.wav", "D.wav", "E.wav"};     //last position is going to be null character
String command[6] = {"", "Food", "Sleep", "Drink", "PEE", "important"};
bool cmd1Flag, cmd2Flag, cmd3Flag, cmd4Flag, cmd5Flag, cmd6Flag, playFlag, timerFlag;

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

#define fingerPin3 A7
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
  Wire.begin();
  setupMPU();
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
  recordGyroRegisters();
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
      cmd = 0;
    } else if (Finger1 == 0 && Finger2 == 1 && Finger3 == 1) {
      cmd = 1;
    } else if (Finger1 == 0 && Finger2 == 1 && Finger3 == 0) {
      cmd = 2;
    } else if (Finger1 == 1 && Finger2 == 0 && Finger3 == 0) {
      cmd = 3;
    } else if (Finger1 == 0 && Finger2 == 0 && Finger3 == 0) {
      cmd = 4;
    } else if (Finger == 0 && Finger2 == 0  && Finger3 == 1) {
      cmd = 5;
    }
    lastTrigger3 = millis();
  }

  //           ***********************actual code***************************  set lcd to value, prints to serial, and plays the sound
  if (cmd != lastCmd) {
    if (!tmrpcm.isPlaying() || (millis() - lastTrigger2 > 500)) {
      if (cmd != 0) {
        tmrpcm.play(filename[cmd]);
        lcd.setCursor(0, 1);
        lcd.print(command[cmd]);
        com = command[cmd];
        cmd = 0;
      }
      lastTrigger2 = millis();
    }
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

void setupMPU() {
  Wire.beginTransmission(MPU); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();
  Wire.beginTransmission(MPU); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4)
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s
  Wire.endTransmission();
  Wire.beginTransmission(MPU); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5)
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission();
}

void recordGyroRegisters() {
  Wire.beginTransmission(MPU); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(MPU, 6); //Request Gyro Registers (43 - 48)
  while (Wire.available() < 6);
  gyroX = Wire.read() << 8 | Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read() << 8 | Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read() << 8 | Wire.read(); //Store last two bytes into accelZ
  processGyroData();
}

void processGyroData() {
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0;
  rotZ = gyroZ / 131.0;
}

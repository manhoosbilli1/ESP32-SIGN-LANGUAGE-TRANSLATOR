//libraries 


String command, com;
unsigned long lastTrigger, lastTrigger1, lastTrigger2;             //timers
float latitude, longitude;                                         //for gps
bool playedOnce = false;

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


//audio and sd card

TMRpcm tmrpcm;

//---------------


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  tmrpcm.speakerPin = 9;
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Command:      ");
  lcd.setCursor(0, 1);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - lastTrigger > 2000) {                            //will continously print to serial every 2 second with new values
    command_encoder(latitude, longitude, com);
    lastTrigger = millis();
  }

}

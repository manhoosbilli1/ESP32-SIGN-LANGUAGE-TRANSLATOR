    
#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"
#include <LiquidCrystal.h>
//LiquidCrystal lcd(3,4,5, 6, 7, 8);
LiquidCrystal lcd(8, 7, 6, 5, 4, A2);
TMRpcm tmrpcm;
const int analogInPina = A0; 
const int analogInPinb = A1; 
const int analogInPinc = A2; 
const int analogInPind = A3; 
const int analogInPine = A4; 
int sensorValuea = 0;  
int sensorValueb = 0;  
int sensorValuec = 0;  
int sensorValued = 0; 
int sensorValuee = 0;   


void setup(){ 
  lcd.begin(16, 2);     
tmrpcm.speakerPin = 9;
Serial.begin(9600);
if (!SD.begin(SD_ChipSelectPin)) {
Serial.println("SD fail");
return;
}
  pinMode(2,INPUT_PULLUP);
  

}
boolean fa=0;
boolean fb=0;
boolean fc=0;
boolean fd=0;
boolean fe=0;
boolean aa=0;
boolean bb=0;
boolean cc=0;
boolean dd=0;
boolean ee=0;
boolean uf=0;
unsigned int lcc=0;
void loop()
{
  again:
  aa=0;
  bb=0;
  cc=0;
  dd=0;
  ee=0;
 sensorValuea = analogRead(analogInPina); 
 sensorValueb = analogRead(analogInPinb);
 sensorValuec = analogRead(analogInPinc);
 sensorValued = analogRead(analogInPind);
 sensorValuee = analogRead(analogInPine);
if(sensorValuea<300)
{
  aa=1;
}
if(sensorValueb<300)
{
  bb=1;
}
if(sensorValuec<300)
{
  cc=1;
}
if(sensorValued<300)
{
  dd=1;
}
if(sensorValuee<300)
{
  ee=1;
}



if(digitalRead(2))
{
byte nv=0;
bitWrite(nv, 0, aa);
bitWrite(nv, 1, bb);
bitWrite(nv, 2, cc);
bitWrite(nv, 3, dd);
bitWrite(nv, 4, ee);
Serial.println(nv);

if(nv==0||nv>26)
{
 uf=0; 
  lcd.setCursor(0,0); 
  lcd.print("Alphabet :    ");
}else
{
lcc++;
if(lcc<10)
{
  delay(250);
  goto again;
}else
{
  lcc=0;
}
  //lcd.setCursor(12,1); 
  char nnn=64+nv;
  lcd.begin(16,2);
  lcd.print("Alphabet : ");
lcd.write(nnn);
Serial.write(nnn);
 if(!uf)
 {
  uf=1; 
  tmrpcm.setVolume(7);
if(nv==1)
{
tmrpcm.play("A.wav");  
}else if(nv==2)
{
tmrpcm.play("B.wav");  
}else if(nv==3)
{
tmrpcm.play("C.wav");  
}else if(nv==4)
{
tmrpcm.play("D.wav");  
}else if(nv==5)
{
tmrpcm.play("E.wav");  
}else if(nv==6)
{
tmrpcm.play("F.wav");  
}else if(nv==7)
{
tmrpcm.play("G.wav");  
}else if(nv==8)
{
tmrpcm.play("H.wav");  
}else if(nv==9)
{
tmrpcm.play("I.wav");  
}else if(nv==10)
{
tmrpcm.play("J.wav");  
}else if(nv==11)
{
tmrpcm.play("K.wav");  
}else if(nv==12)
{
tmrpcm.play("L.wav");  
}else if(nv==13)
{
tmrpcm.play("M.wav");  
}else if(nv==14)
{
tmrpcm.play("N.wav");  
}else if(nv==15)
{
tmrpcm.play("O.wav");  
}else if(nv==16)
{
tmrpcm.play("P.wav");  
}else if(nv==17)
{
tmrpcm.play("Q.wav");  
}else if(nv==18)
{
tmrpcm.play("R.wav");  
}else if(nv==19)
{
tmrpcm.play("S.wav");  
}else if(nv==20)
{
tmrpcm.play("T.wav");  
}else if(nv==21)
{
tmrpcm.play("U.wav");  
}else if(nv==22)
{
tmrpcm.play("V.wav");  
}else if(nv==23)
{
tmrpcm.play("W.wav");  
}else if(nv==24)
{
tmrpcm.play("X.wav");  
}else if(nv==25)
{
tmrpcm.play("Y.wav");  
}else if(nv==26)
{
tmrpcm.play("Z.wav");  
}


}
delay(250);
}
 

}else
{
  if(sensorValuea>300&&sensorValueb<300&&sensorValuec<300&&sensorValued<300&&sensorValuee<300)
  {
    lcd.setCursor(11,1);
    lcd.print("GOOD"); 
  }
  if(sensorValuea>300&&sensorValueb<300&&sensorValuec<300&&sensorValued<300&&sensorValuee>300)
  {
       lcd.setCursor(11,1);
    lcd.print("BAD ");    
  }
  if(sensorValuea<300&&sensorValueb<300&&sensorValuec<300&&sensorValued<300&&sensorValuee>300)
  {
        lcd.setCursor(11,1);
    lcd.print("Pee ");
  }
  if(sensorValuea<300&&sensorValueb<300&&sensorValuec<300&&sensorValued<300&&sensorValuee<300)
  {
        lcd.setCursor(11,1);
    lcd.print("....");
  }
}
}


  

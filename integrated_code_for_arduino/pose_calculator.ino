/* poseCalculator() {

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


//add another map if needed... 1 if 90 and 0 if 0; convert to binary   DONE
//comparing values

  if (Finger1 == 1 && Finger2 == 1 && Finger3 == 0) {
    lcd.setCursor(0, 1);
    lcd.print("PEE         ");
    playAudio("pee");
  } else if (Finger1 == 0 && Finger2 == 1 && Finger3 == 1) {
    lcd.setCursor(0, 1);
    lcd.print("FOOD        ");
    playAudio("food");
  }else if (Finger1 == 0 && Finger2 == 1 && Finger3 == 0) {
    lcd.setCursor(0, 1);
    lcd.print("BED         ");
    playAudio("bed");
  }else if (Finger1 == 1 && Finger2 == 0 && Finger3 == 0) {
    lcd.setCursor(0, 1);
    lcd.print("SLEEP        ");
    playAudio("sleep");
  }else if (Finger1 == 1 && Finger2 == 1 && Finger3 == 1) {
    lcd.setCursor(0, 1);
    lcd.print("              ");
    playAudio("");
  }
}
  
*/

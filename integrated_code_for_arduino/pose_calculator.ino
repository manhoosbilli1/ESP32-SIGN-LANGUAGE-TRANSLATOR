void poseCalculator() {

  //getting ADC reading
  int finger1 = analogRead(fingerPin1);
  int finger2 = analogRead(fingerPin2);
  int finger3 = analogRead(fingerPin3);

  //add the new code here
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

  if (Finger1 == 1 && Finger2 == 1 && Finger3 == 0) {
    say("pee");
  } else if (Finger1 == 0 && Finger2 == 1 && Finger3 == 1) {
    say("food");
  } else if (Finger1 == 0 && Finger2 == 1 && Finger3 == 0) {
    say("bed");
  } else if (Finger1 == 1 && Finger2 == 0 && Finger3 == 0) {
    say("sleep");
  } else if (Finger1 == 1 && Finger2 == 1 && Finger3 == 1) {
    say("  ");
  }




}

void pose_calculator() {
  int finger1 = analogRead(fingerPin1);
  int finger2 = analogRead(fingerPin2);
  int finger3 = analogRead(fingerPin3);
  int finger4 = analogRead(fingerPin4);
  int finger5 = analogRead(fingerPin5);

  finger1 = map(finger1, minimumVal1, maximumVal1, 0,90);            //map the values to certain values
  finger2 = map(finger2, minimumVal2, maximumVal2, 0,90);
  finger3 = map(finger3, minimumVal3, maximumVal3, 0,90);
  finger4 = map(finger4, minimumVal4, maximumVal4, 0,90);
  finger5 = map(finger5, minimumVal5, maximumVal5, 0,90);
  
  
}

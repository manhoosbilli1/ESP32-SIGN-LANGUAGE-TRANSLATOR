void pose_calculator() {

  //getting ADC reading
  int finger1 = analogRead(fingerPin1);
  int finger2 = analogRead(fingerPin2);
  int finger3 = analogRead(fingerPin3);
  int finger4 = analogRead(fingerPin4);
  int finger5 = analogRead(fingerPin5);

  //mapping values
  finger1 = map(finger1, minimumVal1, maximumVal1, 0, 90);           //map the values to certain values
  finger2 = map(finger2, minimumVal2, maximumVal2, 0, 90);
  finger3 = map(finger3, minimumVal3, maximumVal3, 0, 90);
  finger4 = map(finger4, minimumVal4, maximumVal4, 0, 90);
  finger5 = map(finger5, minimumVal5, maximumVal5, 0, 90);


  //add another map if needed... 1 if 90 and 0 if 0; convert to binary
  //comparing values

  if (finger1 == 90 , finger2 == 90 , finger3 == 90 , finger4 == 90, finger5 == 90 ) {        // if all fingers are stretched
    say("bed");                                                                                  // if counter 0, it wont do anything
  } else if (finger1 == 0, finger2 == 0, finger3 == 0 , finger4 == 0, finger5 == 0) {
                                                                                  // triggers a function
  } else if (finger1 == 0 , finger2 == 0 , finger3 == 90, finger4 == 90, finger5 == 90) {
    
  } else {
    
  }
  //extra commands
  /*else if (finger1 == , finger2 == , finger3 == , finger4 == , finger5 == ){

    }else if (finger1 == , finger2 == , finger3 == , finger4 == , finger5 == ){

    }else if (finger1 == , finger2 == , finger3 == , finger4 == , finger5 == ){

    }else if (finger1 == , finger2 == , finger3 == , finger4 == , finger5 == ){

    }else if (finger1 == , finger2 == , finger3 == , finger4 == , finger5 == ){

    }else if (finger1 == , finger2 == , finger3 == , finger4 == , finger5 == ){

    }else if (finger1 == , finger2 == , finger3 == , finger4 == , finger5 == ){

    }else if (finger1 == , finger2 == , finger3 == , finger4 == , finger5 == ){

    }else if (finger1 == , finger2 == , finger3 == , finger4 == , finger5 == ){

    }else if (finger1 == , finger2 == , finger3 == , finger4 == , finger5 == ){

    }else if (finger1 == , finger2 == , finger3 == , finger4 == , finger5 == ){

    }else if (finger1 == , finger2 == , finger3 == , finger4 == , finger5 == ){

    }else if (finger1 == , finger2 == , finger3 == , finger4 == , finger5 == ){

    }*/


  //playing audio and printing to screen

}

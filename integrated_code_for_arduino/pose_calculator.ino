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
    counter = 0;                                                                              // if counter 0, it wont do anything
  } else if (finger1 == 0, finger2 == 0, finger3 == 0 , finger4 == 0, finger5 == 0) {
    counter = 1;                                                                              // triggers a function
  } else if (finger1 == 0 , finger2 == 0 , finger3 == 90, finger4 == 90, finger5 == 90) {
    counter = 2;
  } else {
    counter = 0;
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
  if (counter != prevCounter) {           //only access if statement if command is new
    switch (counter) {
      case 0:
        //doesn't do anything here
        com = "";
        lcd.print("                   ");
        break;

      case 1:
        tmrpcm.play("A.wav");             //play a.wav
        com = "BED";
        lcd.print("BED");
        break;

      case 2:
        tmrpcm.play("B.wav");             //play a.wav
        com = "TEA";
        lcd.print("TEA");
        break;

      /*case 3:
        break;

        case 4:
        break;

        case 5:
        break;

        case 6:
        break;

        case 7:
        break;

        case 8:
        break;

        case 9:
        break;

        case 10:
        break;

        case 11:
        break;

        case 12:
        break;                              //extra commands

        case 13:
        break;

        case 14:
        break;

        case 15:
        break;

        case 16:
        break; */

      default:           //add a command that would diable audio
        //tmrpcm.stopPlayback();       check if the library doesn't automatically stop the audio
        //then add delay after playing and switch to break
        lcd.setCursor(0, 1);
        lcd.print("                       ");        //clear lcd
    }

    prevCounter = counter;
  }
}

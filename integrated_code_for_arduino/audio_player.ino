//this will print to lcd, feed the com string to send to esp, and also say it using speaker


void say(String s) {
  String filePath;
  if (s != lastS) {                      //if command has changed
    String i = s;                        //make a string i concat the space and feed to function
    i += "               ";
    lcd.setCursor(0, 1);                 //print to lcd
    lcd.print(i);
    com = s;                             //set the command to current s
    filePath = s;
    filePath += ".wav";                  //make a file path and feed that to function play
    playFlag = true;
    timerFlag = true;
    lastS = s;                           //save the current command to compare later
  }
  if (playFlag) {
    if (timerFlag) {
      timer = millis();                  //record the time
      timerFlag = false;
    }
    tmrpcm.play(filePath);               //if timer expires or if audio is not playing anymore
    if ((millis() - timer > 1000) || (!tmrpcm.isPlaying())) {        //get out of the loop
      playFlag = false;
    }
  } else {
    tmrpcm.stopPlayback();              //stop the music if not already stopped
  }
}                                       //might have to remove the stopplay back check. could also use tmrpcm.disable();

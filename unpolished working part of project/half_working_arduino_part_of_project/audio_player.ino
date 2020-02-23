/*this will print to lcd, feed the com string to send to esp, and also say it using speaker

/*
void say(String s, char* filename) {
  if (s != lastS && filename != lastFN) {                      //if command has changed
    String i = s;                        //make a string i concat the space and feed to function
    i += "               ";
    lcd.setCursor(0, 1);                 //print to lcd
    lcd.print(i);
    com = s;
    playFlag = true;
    timerFlag = true;
    lastS = s;                           //save the current command to compare later
    lastFN = filename;
  }
  if (playFlag) {
    if (timerFlag) {                                                                      //DIDNT WORK CAUSE OF FILEPATH CHAR
      timer = millis();                  //record the time
      timerFlag = false;
    }
    tmrpcm.play(filename);               //if timer expires or if audio is not playing anymore
    if ((millis() - timer > 1000) || (!tmrpcm.isPlaying())) {        //get out of the loop
      playFlag = false;
    }
  } else {
    tmrpcm.stopPlayback();              //stop the music if not already stopped
  }
}                                       //might have to remove the stopplay back check. could also use tmrpcm.disable();


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
}*/

//this will print to lcd, feed the com string to send to esp, and also say it using speaker
char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}

void say(String s) {
  char* filename;
  if (s != lastS) {                      //if command has changed
    String i = s;                        //make a string i concat the space and feed to function
    i += "               ";
    lcd.setCursor(0, 1);                 //print to lcd
    lcd.print(i);
    com = s;
    String wavPath = s;                  //setting up the filename string here
    wavPath += ".wav";
    filename = string2char(wavPath);      //feeding it to filename to convert to char
    playFlag = true;
    timerFlag = true;
    lastS = s;                           //save the current command to compare later
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

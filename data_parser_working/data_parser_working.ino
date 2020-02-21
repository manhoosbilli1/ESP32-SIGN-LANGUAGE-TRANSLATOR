String command;

void setup() {
  Serial.begin(9600);
}
void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n') {             //when the command is finished it will feed that data into the function
      parseData(command);
      command = "";                //empty command
    } else {
      command += c;                 //else add to the string
    }
  }
}

void parseData(String data) {   //data structure lat,long`cmd

  String lat = data.substring(0, data.indexOf(','));           //read the string from 0th index up until the space but not including
  String lng = data.substring(data.indexOf(',') + 1, data.indexOf('`'));       //read from the space but not including
  String cmd = data.substring(data.indexOf('`') +1);
  Serial.println(lat);
  Serial.println(lng);
  Serial.println(cmd);
}

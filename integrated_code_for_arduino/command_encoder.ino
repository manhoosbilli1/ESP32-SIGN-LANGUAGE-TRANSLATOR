
void command_encoder(float latitude, float longitude, String com) {
  String lati = String(latitude, 6);
  String longi = String(longitude, 6);     //convert float to strings

  //package the data up and encode
  command = "#";
  command.concat(lati);
  command.concat(",");
  command.concat(longi);
  command.concat("`");
  command.concat(com);
  command.concat("\n");
  Serial.print(command);
}

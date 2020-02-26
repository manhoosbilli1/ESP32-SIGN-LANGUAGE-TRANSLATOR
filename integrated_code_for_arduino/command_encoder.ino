
void command_encoder(float lati, float longi, String com) {
   char latitude[12];
   char longitude[12];
   esp.print('#');
   dtostrf(lati, 9,6,latitude);        //convert to char
   esp.print(latitude);
   esp.print(',');
   dtostrf(longi, 9,6,longitude);
   esp.print(longitude);
   esp.print('`');
   esp.print(com);
   esp.print('\n');
}

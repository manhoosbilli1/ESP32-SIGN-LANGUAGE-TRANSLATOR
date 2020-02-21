void parseData(String data) {
 
  String latitude = data.substring(0, data.indexOf(','));           //read the string from 0th index up until the space but not including
  String longitude = data.substring(data.indexOf(',') + 1, data.indexOf('`'));       //read from the space but not including
  String command = data.substring(data.indexOf('`') +1);
}

#include <TinyGPS++.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HardwareSerial.h>
//type "esp/" in browser search bar

const char* ssid = "Mi A2 Lite-Shoaib";
const char* password = "D01234567890";
#define RXD2 16
#define TXD2 17
HardwareSerial GPSserial(2);
TinyGPSPlus gps;
WebServer server(80);

float long_val = 22.2445;                                       //these are the values you need to change..just throw in real gps value into this variable and the program should do the rest
float lat_val = 12.224;

String SendHTML(float long_val, float lat_val) {                 //main html page
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>GPS DATA LOGGER</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "<script>\n";
  ptr += "setInterval(loadDoc,200);\n";
  ptr += "function loadDoc() {\n";
  ptr += "var xhttp = new XMLHttpRequest();\n";
  ptr += "xhttp.onreadystatechange = function() {\n";
  ptr += "if (this.readyState == 4 && this.status == 200) {\n";
  ptr += "document.getElementById(\"webpage\").innerHTML =this.responseText}\n";
  ptr += "};\n";
  ptr += "xhttp.open(\"GET\", \"/\", true);\n";
  ptr += "xhttp.send();\n";
  ptr += "}\n";
  ptr += "</script>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>GPS DATA LOGGER</h1>\n";

  ptr += "<p>Longitude: ";
  ptr += long_val;
  ptr += "<p>Latitude: ";
  ptr += lat_val;

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

void handleRoot() {
  server.send(200, "text/html", SendHTML(long_val, lat_val));
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup() {
  GPSserial.begin(9600,SERIAL_8N1, RXD2, TXD2);      //gps
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  while (GPSserial.available() > 0) {
    if (gps.encode(GPSserial.read())) {
      displayInfo();
    }
  }
  server.handleClient();      //upload to the server
}

void displayInfo()
{
  if (gps.location.isValid()) {
    lat_val = gps.location.lat();
    long_val = gps.location.lng();

    Serial.setCursor(0, 0);
    Serial.print("Latitude: ");
    Serial.print(lat_val, 6);
    Serial.setCursor(0, 1);
    Serial.print("Longitude: ");
    Serial.print(lat_val, 6);
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
  }
}

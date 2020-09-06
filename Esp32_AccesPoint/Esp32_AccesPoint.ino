//#include <WiFi.h>
#include <ESP8266WiFi.h>

const char* ssid = "ESP32-Acces-Point";
const char* password = "davidprr";

//  Definiendo el puerto del servidor a 80
WiFiServer server(80);

int led =  LED_BUILTIN;
int status = WL_IDLE_STATUS;


void setup() {
  Serial.begin(9600);

  pinMode(led, OUTPUT);

  digitalWrite(led, LOW);

  if(WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield no encontrada");
    while(true);
  }

  Serial.print("Ceando Acces Point llamado: ");
  Serial.println(ssid);

  status = WiFi.softAP(ssid);
  /*if(status != WL_AP_LISTENING) {
    Serial.println("Error creando Acces Point");

    while(true);
  }*/

  delay(10000);

  server.begin();

  printWiFiStatus();
}

void loop() {
  WiFiClient client = server.available();

  if(client) {
    Serial.println("Nuevo Cliente");
    String currentLine = "";
    while (client.connected()) {
      if(client.available()) {
        char c = client.read();
        Serial.write(c);
        if(c == '\n') {

          if(currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {
            currentLine = "";
          }
        } else if(c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("/H")) {
          Serial.println(" LED Encendido...");
          digitalWrite(led, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("/L")) {
          Serial.println(" LED Apagado...");
          digitalWrite(led, LOW);                // GET /L turns the LED off
        }
      }
    }
    /*client.stop();
    Serial.println("client disconnected");*/
  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);

}

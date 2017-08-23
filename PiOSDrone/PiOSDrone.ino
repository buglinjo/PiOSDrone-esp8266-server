#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <WebSocketsServer.h>

WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            break;

        case WStype_CONNECTED: {
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
        	  break;
        }

        case WStype_TEXT:
            Serial.printf("%s\n", payload);
            break;
    }
}

const char *ssid = "PiOSDrone";
const char *password = "piosdrone";

void setup() {
    delay(1000);
    Serial.begin(115200);
    Serial.println();
    Serial.println("Configuring access point...");
   
    WiFi.softAP(ssid, password);

    IPAddress myIP = WiFi.softAPIP();
    
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    Serial.print("AP SSID: ");
    Serial.println(ssid);
    Serial.print("AP PASS: ");
    Serial.println(password);
    
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}

void loop() {
    webSocket.loop();
}

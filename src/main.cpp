#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h" //ssid, password and other credentials

//add ssid and password on a different file
WiFiClient myWifiClient;
PubSubClient client (myWifiClient);
unsigned long lastMsg = 0;

#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup()
{
  Serial.begin (115200);
  WiFi.mode (WIFI_STA);
  WiFi.begin (WifiSSID, WifiPASS);
  Serial.print ("connectin to: ");
  Serial.println (WifiSSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay (500);
    Serial.print (".");
  }
}

void loop()
{
  Serial.println ("hola mundo");
  delay (1000);
}

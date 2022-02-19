#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h" //ssid, password, mqtt server and other credentials

WiFiClient myWifiClient;
PubSubClient client (myWifiClient);
unsigned long lastReconnectAttempt = 0;
unsigned long lastLDRSendAttempt = 0;
unsigned long now;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void callback (char* topic, byte* payload, unsigned int length)
{
  Serial.print ("Message arrived [");
  Serial.print (topic);
  Serial.print ("] ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print ((char)payload[i]);
  }
  Serial.println();
  // Switch on the LED if an 1 was received as first character
  // INSTEAD change this to recieve an int for servo's position
  if ((char)payload[0] == '1') {
    digitalWrite (LED_BUILTIN, LOW);  // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite (LED_BUILTIN, HIGH); // Turn the LED off by making the voltage HIGH
  }
}

bool reconnect()
{
  Serial.print ("Attempting MQTT connection...");
  // Create a random client ID
  String clientId = "ESP8266Client-";
  clientId += String (random (0xffff), HEX);
  // Attempt to connect
  //client constructor can receive user and password like:
  //  client("clientID", "USER", "password");
  //  NOTE: maximun lenght of clientID + user + password is 128bytes. To increase use: client.setBufferSize(255);
  if (client.connect (clientId.c_str())) {
    Serial.println ("Successfully connected!");
    // Once connected, publish an announcement...
    client.publish ("outTopic", "hello world");
    // ... and resubscribe
    client.subscribe ("inTopic");
  } else {
    Serial.print ("failed, rc=");
    Serial.println (client.state());
  }
  return client.connected();
}

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
  randomSeed (micros());
  client.setServer (mqtt_server, 1883);
  client.setCallback (callback);
  lastReconnectAttempt = 0;
}

void loop()
{
  if (!client.connected()) {
    now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      if (reconnect()) {
        //do your stuff after the reconnection here
      }
    }
  } else {
    //do your stuff here, the mqtt client is connected to the broker
    client.loop();
    now = millis(); //needed because the time always go on
    if (now - lastLDRSendAttempt > 2000) {
      lastLDRSendAttempt = now;
      ++value;
      snprintf (msg, MSG_BUFFER_SIZE, "hello world #%d", value);
      Serial.print ("Publish message: ");
      Serial.println (msg);
      client.publish ("outTopic", msg);
    }
  }
}

//WiFi
#include <WiFi.h>
int status = WL_IDLE_STATUS;
const char* ssid     = "SSID";
const char* password = "SSIDPASSWORD";
String token = "XXXX-xxxxxxxxxxxxxxxxxxxxxxxxxxx";
WiFiClient ubidots;

String humidity, temperature;

//MQTT
#include <PubSubClient.h>
PubSubClient pubSubClient(ubidots);
#define MQTT_CLIENT_NAME "esp32-client"
char mqttBroker[]  = "industrial.api.ubidots.com";
char payload[256];
char pubTopic[150];

// Ubidots
String DEVICE_LABEL = "esp32";
String humidityVarLabel = "kelembaban";
String temperatureVarLabel = "suhu";

//read sensor and send data interval
unsigned long lastCheck = 0;
unsigned long lastMillis = 0;
unsigned long intv;
unsigned long Interval = 20000;
unsigned long beginInterval = 0;

void setup() {
  Serial.begin(115200);
  wifiInit();
  mqttInit();
  lastMillis = millis();
  intv = beginInterval;
}

void loop() {
  delay(1);
  if (!pubSubClient.connected()) {
    reconnect();
  }
  pubSubClient.loop();
  if (millis() - lastMillis >= intv)
  {
    intv = Interval;
    lastMillis = millis();
    getAirValue();
    publishDataToUbidots();
  }
}

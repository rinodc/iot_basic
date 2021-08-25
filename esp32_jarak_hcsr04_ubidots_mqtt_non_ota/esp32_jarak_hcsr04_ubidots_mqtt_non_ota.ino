//WiFi
#include <WiFi.h>
int status = WL_IDLE_STATUS;
const char* ssid     = "SSID";
const char* password = "SSIDPASSWORD";
String token = "XXXX-xxxxxxxxxxxxxxxxxxxxxxxxxxx";
WiFiClient ubidots;

//MQTT
#include <PubSubClient.h>
PubSubClient pubSubClient(ubidots);
#define MQTT_CLIENT_NAME "esp32-client"
char mqttBroker[]  = "industrial.api.ubidots.com";
char payload[100];
char pubTopic[150];

// Ubidots
String device = "esp32";
String levelAirVarLabel =  "level-air";

//Sensor HCSR04
#include <NewPing.h>
#define TRIGGER_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int distance;
String distanceStr;

//read sensor and send data interval
unsigned long lastCheck = 0;
unsigned long lastMillis = 0;
unsigned long intv;
//unsigned long Interval = 20000;
unsigned long Interval = 5000;
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
    readDistance();
    publishDataToUbidots();
  }
}

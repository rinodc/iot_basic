//WiFi
const char* ssid     = "SSID";
const char* password = "SSIDPASSWORD";
const char* token = "XXXX-xxxxxxxxxxxxxxxxxxxxxxxx";

// Ubidots
#include "UbidotsEsp32Mqtt.h"
const char* device = "esp32";
const char* levelAirVarLabel =  "level-air";
Ubidots ubidots(token);

//Sensor HCSR04
#include <NewPing.h>
#define TRIGGER_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int distance;
String distanceStr;

//read sensor and send data interval
unsigned long timer;
const int PUBLISH_FREQUENCY = 10000;

void setup() {
  Serial.begin(115200);
  ubidots.setDebug(true);
  wifiInit();
  mqttInit();
  timer = 10000;
}

void loop() {
  if (!ubidots.connected())
  {
    ubidots.reconnect();
  }
  if (abs(millis() - timer) > PUBLISH_FREQUENCY) // triggers the routine every 5 seconds
  {
    readDistance();
    ubidots.add(levelAirVarLabel, distance); // Insert your variable Labels and the value to be sent
    ubidots.publish(device);
    timer = millis();
  }
  ubidots.loop();
}

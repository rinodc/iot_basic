// Ubidots
#include "UbidotsEsp32Mqtt.h"
const char *UBIDOTS_TOKEN = "XXXX-xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "SSID";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "SSIDPASSWORD";      // Put here your Wi-Fi password
const char *DEVICE_LABEL = "esp32";   // Put here your Device label to which data  will be published
const char *VARIABLE_LABEL = "light"; // Put here your Variable label to which data  will be published
const int PUBLISH_FREQUENCY = 10000; // Update rate in milliseconds
unsigned long timer;
Ubidots ubidots(UBIDOTS_TOKEN);

// LDR
#define LDR 13
#define DARK 0
int ldr_value = 0;

// LED
#define LED 2


void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
//  pinMode(LDR, INPUT);
  pinMode(LDR, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  mqtt_begin();

  timer = millis();
}

void loop()
{
  // put your main code here, to run repeatedly:
  ldr_read();
  if (!ubidots.connected())
  {
    ubidots.reconnect();
  }
  if (abs(millis() - timer) > PUBLISH_FREQUENCY) // triggers the routine every 5 seconds
  {
    send_data();
    timer = millis();
  }
  ubidots.loop();
}

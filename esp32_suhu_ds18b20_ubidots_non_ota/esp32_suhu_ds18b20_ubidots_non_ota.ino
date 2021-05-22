//DS18B20 declarations
#include <OneWire.h>
#include <DallasTemperature.h>
const int oneWireBus = 25;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
float tem;
String temString;
DeviceAddress insideThermometer;

//WiFi
#include <WiFi.h>
#include <HTTPClient.h>
int status = WL_IDLE_STATUS;
const char* ssid     = "SSID";
const char* password = "SSIDPASSWORD";
WiFiClient client;

// Ubidots
char iot_server[] = "http://things.iot.ubidots.com";
const int port = 80;
String token = "BBFF-yvYUKs34eSn1fYJ7dXtNbYm31ZjjT6";
String DEVICE_LABEL = "esp32";
String temperatureVarLabel = "suhu";


//read sensor and send data interval
unsigned long lastMillis = 0;
unsigned long intv;
unsigned long Interval = 20000;
unsigned long beginInterval = 0;

void setup() {
  Serial.begin(115200);
  wifiInit();
  sensorInit();
  lastMillis = millis();
  intv = beginInterval;
}

void loop() {
  if (millis() - lastMillis >= intv)
  {
    intv = Interval;
    lastMillis = millis();
    readSensor();
    sendData();
  }
}

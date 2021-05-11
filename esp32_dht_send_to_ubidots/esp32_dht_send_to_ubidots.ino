
//DHT declarations

#include <dht.h> 
dht sensor;
int readResp;
float hum, tem;
const int dhtPin = 23;

#define DHT11
//#define DHT22

// Connections

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = "SSID";
const char* password = "SSIDPASSWORD";

int status = WL_IDLE_STATUS;
char server[] = "http://things.iot.ubidots.com";
const int port = 80;
String token = "XXXX-xxxxxxxxxxxxxxxxxxxxxxxxxxx";

String humString, temString;

WiFiClient client;

// Ubidots
String DEVICE_LABEL = "esp32";
String humidityVarLabel = "kelembaban";
String temperatureVarLabel = "suhu";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  wifiInit();
}

void loop() {
  readDHT();
  sendData();
  delay(10000);
}

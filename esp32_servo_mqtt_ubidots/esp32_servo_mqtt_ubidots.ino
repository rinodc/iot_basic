#include <WiFi.h>
#include <PubSubClient.h>

#define WIFISSID "SSID" // Put your WifiSSID here
#define PASSWORD "SSIDPASSWORD" // Put your wifi password here
#define TOKEN "XXXX-xxxxxxxxxxxxxxxxxxxxxxxxxxx" // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "ESP32" // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 

#define VARIABLE_LABEL "servo" // Assign the variable label
#define DEVICE_LABEL "esp32-device" // Assign the device label

char mqttBroker[]  = "industrial.api.ubidots.com";
char payload[100];
char topic[150];

#include <Servo.h>
#define SERVO_PIN 27

Servo servo;


WiFiClient ubidots;
PubSubClient client(ubidots);
long lastMsg = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  char sub_payload[64];
  int servoPos;
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    sub_payload[i] =  (char)payload[i];
  }
  Serial.println();

  sscanf((char*)sub_payload, "%i", &servoPos);
  String buf = "Servo Pos set to = " + String(servoPos) + " °";
  Serial.println(buf);
  servo.write(servoPos);
  delay(15);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");

    // Attemp to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}


void setup() {
  servo.attach(SERVO_PIN);
  Serial.begin(115200);
  WiFi.begin(WIFISSID, PASSWORD);
  Serial.println();
  Serial.print("Wait for WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);
  sprintf(topic, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, VARIABLE_LABEL);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    client.subscribe(topic);
  }
}

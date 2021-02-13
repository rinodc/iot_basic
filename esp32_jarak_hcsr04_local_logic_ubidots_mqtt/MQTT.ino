void mqttInit()
{
  pubSubClient.setServer(mqttBroker, 1883);
  pubSubClient.setCallback(callback);
  char deviceChar[32];
  char servoVarLabelChar[32];
  device.toCharArray(deviceChar, device.length() + 1);
  servoVarLabel.toCharArray(servoVarLabelChar, servoVarLabel.length() + 1);
  sprintf(subTopic, "/v1.6/devices/%s/%s/lv", deviceChar, servoVarLabelChar);
}

void callback(char* subTopic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(subTopic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    sub_payload[i] =  (char)payload[i];
  }
  Serial.println();
  
  delay(20);
}

void reconnect() {
  if (!pubSubClient.connected())
  {
    Serial.println("Attempting MQTT connection...");

    // Attemp to connect
    char TOKEN[64];
    token.toCharArray(TOKEN, token.length() + 1);
    if (pubSubClient.connect(MQTT_CLIENT_NAME, TOKEN, "")) 
    {
      Serial.println("Connected");
    }
    else
    {
      Serial.print("Failed, rc=");
      Serial.print(pubSubClient.state());
      Serial.println();
    }
  }
}

void publishDataToUbidots()
{
  String buff;
  buff = "";
  buff = "/v1.6/devices/" + device;
  buff.toCharArray(pubTopic, buff.length() + 1);
  for (int i = 0; i < buff.length() + 1; i++)
  {
    Serial.print(pubTopic[i]);
  }
  Serial.println();

  buff = "";
  buff += "{";
  buff += "\"" + levelAirVarLabel   + "\": " + distanceStr;
  buff += "}";
  buff.toCharArray(payload, buff.length() + 1);
  for (int i = 0; i < buff.length() + 1; i++)
  {
    Serial.print(payload[i]);
  }
  Serial.println();
  pubSubClient.publish(pubTopic, payload);
}

void mqttInit()
{
  pubSubClient.setServer(mqttBroker, 1883);
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
  Serial.println();
  
  buff = "";
  buff = "/v1.6/devices/" + DEVICE_LABEL;
  buff.toCharArray(pubTopic, buff.length() + 1);
  for (int i = 0; i < buff.length() + 1; i++)
  {
    Serial.print(pubTopic[i]);
  }
  Serial.println();
  Serial.println();


  // publish val 1
  buff = "";
  buff += "{";
  buff += "\"" + humidityVarLabel     + "\" : " + humidity     +  "";
  buff += "}\r\n";
  buff.toCharArray(payload, buff.length() + 1);
  for (int i = 0; i < buff.length() + 1; i++)
  {
    Serial.print(payload[i]);
  }
  Serial.println();
  pubSubClient.publish(pubTopic, payload);

  memset(payload, 0, 256);
  // publish val 2
  buff = "";
  buff += "{";
  buff += "\"" + temperatureVarLabel  + "\" : " + temperature  +  "";
  buff += "}\r\n";
  buff.toCharArray(payload, buff.length() + 1);
  for (int i = 0; i < buff.length() + 1; i++)
  {
    Serial.print(payload[i]);
  }
  Serial.println();
  buff.toCharArray(payload, buff.length() + 1);
  pubSubClient.publish(pubTopic, payload);
  Serial.println();
}

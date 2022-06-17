void mqtt_begin()
{
  // ubidots.setDebug(true);  // uncomment this to make debug messages available
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();
}

void send_data()
{ 
  delay(200);
  Serial.println("send data, soil_value = " + String(soil_value));
  ubidots.add(VARIABLE_LABEL, soil_value); // Insert your variable Labels and the value to be sent
  ubidots.publish(DEVICE_LABEL);
}

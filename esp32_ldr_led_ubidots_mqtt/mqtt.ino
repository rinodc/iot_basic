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
  Serial.println("send data, ldr_value = " + String(ldr_value));
  ubidots.add(VARIABLE_LABEL, ldr_value); // Insert your variable Labels and the value to be sent
  ubidots.publish(DEVICE_LABEL);
}

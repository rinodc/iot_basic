void wifiInit()
{
  delay(1000);
  Serial.print("Connecting to " + *ssid);
  delay(500);
  ubidots.connectToWifi(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("connecting to network...");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

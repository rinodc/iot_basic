void sensorInit()
{
  
  sensors.begin();
  if (!sensors.getAddress(insideThermometer, 0))
  {
    Serial.println("Unable to find address for Device 0");
  }
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();
  sensors.setResolution(insideThermometer, 12);
}

void readSensor()
{
  Serial.println("Read DS18B20 Sensor...");
  sensors.requestTemperatures();
  tem = sensors.getTempCByIndex(0); // get temperature in °C

  // test
  //randomSeed(analogRead(A7));
  //float randomNumber = random(251, 331);
  //tem = randomNumber/10;
  // test

  //  tem = sensors.getTempFByIndex(0); // get temperature in °F
  temString = String(tem);
  Serial.print(temString);
  Serial.println(" °C");
}

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

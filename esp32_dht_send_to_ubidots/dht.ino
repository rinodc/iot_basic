void readDHT()
{
  Serial.println("Read DHT Sensor...");

#if defined DHT11
  readResp = sensor.read11(dhtPin); // for DHT11 
#else
  readResp = sensor.read22(dhtPin); // for DHT22
#endif
 

  tem = sensor.temperature;
  hum = sensor.humidity;
  
  temString = String(tem);
  humString = String(hum);
  
  Serial.print(temString);
  Serial.print(" C");
  Serial.print('\t');
  Serial.print(humString);
  Serial.println(" %");

}

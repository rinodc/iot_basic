void getAirValue()
{
  //Dummy DATA
  Serial.println("DUMMY DATA");
  randomSeed(analogRead(A0));
  float randNumber;

  randNumber = random(250, 331);
  temperature = String(randNumber/10);
  Serial.println("Air Temperature = " + temperature);

  randNumber = random(610, 851);
  humidity = String(randNumber/10);
  Serial.println("Air Humidity = " + humidity);
  delay(1000);
}

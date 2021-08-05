void readDistance()
{
  distance = ultrasonic.ping_cm();

// test
//randomSeed(analogRead(A7));
//float randomNumber = random(0, 400);
//distance = randomNumber;
// test
  
  Serial.print("Distance = ");
  distanceStr = String(distance);
  Serial.print(distanceStr);
  Serial.println(" cm");
}

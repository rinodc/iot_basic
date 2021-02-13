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

  if(distance <= 10)                    // jika distance kurang dari sama dengan 10 cm,
  {
    servoPosLocal = 90;                 // maka ubah posisi servo ke 90°
    servo.write(servoPos);
  }
  else                                 // selain kondisi diatas,
  {
    servoPosLocal = 0;                 // maka ubah posisi servo ke 0°
    servo.write(servoPos);
  }
}

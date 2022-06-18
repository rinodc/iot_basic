void soil_read()
{
  analog_value = analogRead(SOIL);
  soil_value = map(analog_value,1772,4095,100,0);
  soil_value = constrain(soil_value, 0, 100);
  if(soil_value <= WET)
  {
    turn_on_led();
  }
  else
  {
    turn_off_led();
  }
}

void turn_on_led()
{
  digitalWrite(LED, HIGH);
}

void turn_off_led()
{
  digitalWrite(LED, LOW);
}

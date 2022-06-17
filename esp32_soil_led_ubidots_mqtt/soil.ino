void soil_read()
{
  int analog_value = analogRead(SOIL);
  soil_value = map(analog_value,0,4095,100,0);
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

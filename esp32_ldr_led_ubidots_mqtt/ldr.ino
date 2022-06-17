void ldr_read()
{
  ldr_value = digitalRead(LDR);
  if(ldr_value == DARK)
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

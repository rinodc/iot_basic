void ldr_read()
{
  ldr_value = digitalRead(LDR);
  if (ldr_value!=last_ldr_value) 
  {
  if (ldr_value == DARK)
    {
      turn_on_led();
    }
    else
    {
      turn_off_led();
    }
    send_data();
    last_ldr_value = ldr_value;
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

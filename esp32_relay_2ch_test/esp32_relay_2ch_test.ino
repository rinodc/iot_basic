#define RELAY1 23
#define RELAY2 22

void setup() {
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
}

void loop() {
  digitalWrite(RELAY1, LOW);
  delay(1000);                     
  digitalWrite(RELAY1, HIGH);    
  delay(1000);                       
  digitalWrite(RELAY2, LOW);   
  delay(1000);                      
  digitalWrite(RELAY2, HIGH);    
  delay(1000);   
}

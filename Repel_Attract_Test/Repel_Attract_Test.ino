int PWM_Mode = 14;
int dir = 13;
int PWM_Pin = 7;
 

void setup() {
  // put your setup code here, to run once:

  pinMode(PWM_Mode, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(PWM_Pin, OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:

   analogWrite(PWM_Pin, 255);

  for(;;)
  {
    digitalWrite(dir, HIGH);
    delay(1000);
    Serial.println(dir);
    digitalWrite(dir, LOW);
    delay(1000);
  }

}

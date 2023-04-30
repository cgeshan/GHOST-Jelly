const int dir = 13;
const int steps = 15;
const int stepsPerRev = 2000;

void setup() {
  // put your setup code here, to run once:
  pinMode(dir, OUTPUT);
  pinMode(steps, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

    for(int i = 0; i < 2000; i++)
    {
      // Set motor direction clockwise
    digitalWrite(dir, HIGH);

    // Spin motor slowly
    for(int i = 0; i < stepsPerRev; i++)
    {
      digitalWrite(steps, HIGH);
      delayMicroseconds(1000);
      digitalWrite(steps, LOW);
      delayMicroseconds(1000);
    }
    delay(5000); // Wait a second
    
    // Set motor direction counterclockwise
    digitalWrite(dir, LOW);

    // Spin motor quickly
    for(int i = 0; i < stepsPerRev; i++)
    {
      digitalWrite(steps, HIGH);
      delayMicroseconds(1000);
      digitalWrite(steps, LOW);
      delayMicroseconds(1000);
    }
  }
}

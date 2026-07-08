// C++ code
//
const int potPin=A0;
const int ledPin=6;
int potVal=0;
int pwmVal=0;
void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  potVal= analogRead(potPin);
  pwmVal=map(potVal, 0, 1023, 0, 255);
  analogWrite(ledPin, pwmVal);
  Serial.print("Potentiometer Value: ");
  Serial.print(potVal);
  Serial.print(" | PWM Value: ");
  Serial.println(pwmVal);
  delay(150);
}

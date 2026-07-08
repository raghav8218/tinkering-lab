// C++ code
const int ldrPin = A0;
const int ledPin = 9; 

int ldrVal = 0;
int pwmVal = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  ldrVal = analogRead(ldrPin);             
  pwmVal = map(ldrVal, 0, 1023, 0, 255);  
  analogWrite(ledPin, pwmVal);             

  Serial.print("LDR Value: ");
  Serial.print(ldrVal);
  Serial.print(" | PWM Value: ");
  Serial.println(pwmVal);

  delay(100);
}

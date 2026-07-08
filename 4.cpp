bool pirState = LOW;
int pirPin = 13;
int ledPin = 8;

unsigned long lastMotionTime = 0;
const unsigned long delayTime = 6000; // 1 minute (60,000 ms)

void setup()
{
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int pirOP = digitalRead(pirPin);

  // Motion detected
  if (pirOP == HIGH)
  {
    digitalWrite(ledPin, HIGH);
    lastMotionTime = millis();  // reset timer

    if (!pirState)
    {
      Serial.println("Moving");
      pirState = HIGH;
    }
  }

  // No motion — check if 1 minute has passed
  if (pirState && (millis() - lastMotionTime >= delayTime))
  {
    digitalWrite(ledPin, LOW);
    Serial.println("Stopped Moving.");
    pirState = LOW;
  }
}

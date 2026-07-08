#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int signalPin = 9;
const int ledPin = 11;
const int buzzerPin = 12;

long duration;
float distance;

unsigned long previousMillis = 0;
int blinkInterval = 1000;
bool ledState = LOW;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.print("Parking Assist");
  delay(2000);
  lcd.clear();
}

void loop() {

  // Trigger ultrasonic
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, LOW);
  delayMicroseconds(2);
  digitalWrite(signalPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(signalPin, LOW);

  pinMode(signalPin, INPUT);
  duration = pulseIn(signalPin, HIGH);

  distance = duration * 0.034 / 2;

  // Serial output
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // LCD display
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm   ");

  lcd.setCursor(0, 1);

  // -------- STATE LOGIC --------

  if (distance > 50) {
    // SAFE
    lcd.print("SAFE      ");
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    noTone(buzzerPin);
  }

  else if (distance > 20 && distance <= 50) {
    // CAUTION
    lcd.print("CAUTION   ");
    blinkInterval = 800;
    digitalWrite(buzzerPin, LOW);
    noTone(buzzerPin); 
    blinkLED();
  }

  else {
    // CRITICAL
    lcd.print("CRITICAL  ");
    blinkInterval = 200;
    tone(buzzerPin, 1000);
    blinkLED();
  }

  delay(100);
}

// Non-blocking blink function
void blinkLED() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= blinkInterval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}

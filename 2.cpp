#include <Wire.h>

const int ledPin = 13;
int receivedData = 0;

void setup() {
  Wire.begin(8);              // Start as Slave with address 8
  Wire.onReceive(receiveEvent);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, receivedData);
}

void receiveEvent(int howMany) {
  if (Wire.available()) {
    receivedData = Wire.read();
  }
}

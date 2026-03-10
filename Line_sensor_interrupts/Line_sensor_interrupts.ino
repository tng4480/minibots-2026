const int lineSensorPin = 12;

volatile bool lineDetected = false;

void lineSensorISR() {
  if (digitalRead(lineSensorPin) == LOW) {
    lineDetected = true;
  } else {
    lineDetected = false;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(lineSensorPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(lineSensorPin), lineSensorISR, CHANGE);
}

void loop() {

  if (lineDetected) {
    Serial.println("on");
    lineDetected = false;
  }
  delay(100);
}
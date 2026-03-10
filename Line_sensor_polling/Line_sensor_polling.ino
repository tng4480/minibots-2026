const int lineSensorPin = 12;  // the number of the pushbutton pin

// variables will change:
int ls = 0;  // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  Serial.begin(9600);
  // initialize the pushbutton pin as an input:
  pinMode(lineSensorPin, INPUT_PULLUP);
}

void loop() {
  // read the state of the pushbutton value:
  ls = digitalRead(lineSensorPin);

  if (ls == LOW) {
    Serial.println("on");
  } else {
    Serial.println("off");
  }
  delay(100);
}
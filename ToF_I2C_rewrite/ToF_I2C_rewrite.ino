#include <Wire.h>
#include <VL53L0X.h>

// Using VL53L0X library by Pololu
// https://github.com/pololu/vl53l0x-arduino

VL53L0X sensor1;
VL53L0X sensor2;

#define XSHUT1 4
#define XSHUT2 5
// This are the square pads next to the connector, used to change I2C address


void scanI2C() {
  Serial.println("I2C scan:");

  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Device at 0x");
      if (addr < 16) Serial.print("0");
      Serial.println(addr, HEX);
    }
  }

  Serial.println("Scan done\n");
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Wire.begin();
  scanI2C();

  pinMode(XSHUT1, OUTPUT);
  pinMode(XSHUT2, OUTPUT);

  digitalWrite(XSHUT1, LOW);
  digitalWrite(XSHUT2, LOW);
  delay(10);

  digitalWrite(XSHUT1, HIGH);
  delay(10);
  sensor1.init();
  sensor1.setAddress(0x30);

  digitalWrite(XSHUT2, HIGH);
  delay(10);
  sensor2.init();
  sensor2.setAddress(0x31);

  scanI2C();
}

void loop() {
  Serial.print("S1: ");
  Serial.println(sensor1.readRangeSingleMillimeters());

  Serial.print("S2: ");
  Serial.println(sensor2.readRangeSingleMillimeters());

  delay(200);
}
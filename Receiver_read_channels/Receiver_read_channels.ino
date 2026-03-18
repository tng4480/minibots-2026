#include <Arduino.h>

#define CRSF_BAUD 420000

uint16_t channels[16];
uint8_t buffer[64];
int frameCount = 0;

void decodeCRSFChannels(const uint8_t *payload, uint16_t *channels) {
  uint32_t bitBuffer = 0;
  uint8_t bits = 0;
  int payloadIndex = 0;

  for (int ch = 0; ch < 16; ch++) {
    while (bits < 11) {
      bitBuffer |= ((uint32_t)payload[payloadIndex++]) << bits;
      bits += 8;
    }
    channels[ch] = bitBuffer & 0x7FF;
    bitBuffer >>= 11;
    bits -= 11;
  }
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(CRSF_BAUD);   // RP3 TX -> Nano RX
}

void loop() {
  // wait for full CRSF frame
  if (Serial1.available() < 26) return;

  // sync to frame start
  if (Serial1.peek() != 0xC8) {
    Serial1.read();
    return;
  }

  // read full frame
  Serial1.readBytes(buffer, 26);

  // basic validation
  if (buffer[1] != 24) return;      // length
  if (buffer[2] != 0x16) return;    // RC channels frame

  // decode payload
  decodeCRSFChannels(&buffer[3], channels);

  frameCount++;

  // print all channels
  for (int i = 0; i < 16; i++) {
    int us = map(channels[i], 172, 1811, 1000, 2000);
    Serial.print("CH");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(us);
    Serial.print("  ");
  }
  Serial.println();
}
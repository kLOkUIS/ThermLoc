#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include "lora_pins.h"
#include "led_helper.h"

void setup() {
  Serial.begin(115200);
  ledInit(0x400000);              // red‑ish

  SPI.setSCK(LORA_SCK); SPI.setMISO(LORA_MISO); SPI.setMOSI(LORA_MOSI);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(LORA_FREQ)) { for (;;) ledFlash(0xFF0000,200); }
  ledFlash(0x00FF00, 500);        // green once
}

void loop() {
  int n = LoRa.parsePacket();
  if (n) {
    String in;
    while (LoRa.available()) in += (char)LoRa.read();
    Serial.print("[RX] "); Serial.println(in);
    ledFlash(0xFFFF00);           // yellow on packet
  }
}

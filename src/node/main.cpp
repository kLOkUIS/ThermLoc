#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "lora_pins.h"
#include "led_helper.h"
#include <MS5611.h>

MS5611 ms;
uint32_t lastSend = 0;
uint16_t pkt = 0;

void setup() {
  Serial.begin(115200);
  ledInit(0x004000);               // green‑ish

  // I²C on custom pins
  Wire.setSDA(12); Wire.setSCL(13); Wire.begin();
  if (!ms.begin()) Serial.println("MS5611 fail!");

  SPI.setSCK(LORA_SCK); SPI.setMISO(LORA_MISO); SPI.setMOSI(LORA_MOSI);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(LORA_FREQ)) { for (;;) ledFlash(0xFF0000,200); }
}

void loop() {
  if (millis() - lastSend > 5000) {
    ms.read();
    float t = ms.getTemperature();
    float p = ms.getPressure() * 2;          // scale fix
    String out = String("N=")+NODE_ID+" T="+t+" P="+p+" #"+pkt++;
    LoRa.beginPacket(); LoRa.print(out); LoRa.endPacket();
    Serial.println(out);
    ledFlash(0x0000FF);                      // blue
    lastSend = millis();
  }
}

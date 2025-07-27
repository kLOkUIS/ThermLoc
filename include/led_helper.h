// led_helper.h
#pragma once
#include <Adafruit_NeoPixel.h>
constexpr uint8_t LED_PIN = 16;
constexpr uint8_t LED_COUNT = 1;
static Adafruit_NeoPixel led(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

inline void ledInit(uint32_t col = 0) {
  led.begin(); led.setBrightness(40); led.fill(col); led.show();
}
inline void ledFlash(uint32_t col, uint16_t ms = 100) {
  led.fill(col); led.show(); delay(ms);
  led.clear();  led.show();
}
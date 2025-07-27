/***************************************************************************
 *  MS5611 pressure‑temperature quick test – RP2040 Zero (ThermLoc project)
 *
 *  – RP2040 I²C pins:
 *      GP12  →  SDA
 *      GP13  →  SCL
 *
 *  – Library:  Rob Tillaart / MS5611
 *              (PlatformIO:  lib_deps = robtillaart/MS5611)
 *
 *  The Rob Tillaart library’s getPressure() value is exactly half
 *  of the true mbar reading; we correct it here with   pressure *= 2.0;
 *
 *  Baud‑rate: 115 200 Bd   (set in platformio.ini → monitor_speed)
 ***************************************************************************/

#include <Arduino.h>
#include <Wire.h>
#include <MS5611.h>

MS5611 ms;                                // default I²C address 0x77

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println(F("\nThermLoc – MS5611 diagnostics"));

  /* ---------- I²C on custom pins (RP2040 Zero) ---------- */
  Wire.setSDA(12);                        // GP12  SDA
  Wire.setSCL(13);                        // GP13  SCL
  Wire.begin();

  /* ---------- Sensor init ---------- */
  if (!ms.begin())
  {
    Serial.println(F("❌  MS5611 not found – check wiring / address"));
    while (1) delay(10);
  }

  /* Highest oversampling the library exposes */
  #ifdef MS5611_OSR_4096
      ms.setOversampling(MS5611_OSR_4096);
      Serial.println(F("OSR set to 4096 (ultra‑high)"));
  #endif

  Serial.println(F("MS5611 ready\n"));
}

void loop()
{
  ms.read();

  float temperature = ms.getTemperature();   // °C
  float pressure    = ms.getPressure();      // library value (half scale)
  pressure *= 2.0;                           // correct to true mbar (hPa)

  /* Simple altitude estimate (ISA model, sea‑level 1013.25 mbar) */
  float altitude   = 44330.0 * (1.0 - pow(pressure / 1013.25, 0.1903));

  /* ---------- Serial output ---------- */
  Serial.print(F("T "));
  Serial.print(temperature, 2);
  Serial.print(F(" °C | P "));
  Serial.print(pressure, 2);
  Serial.print(F(" mbar | alt "));
  Serial.print(altitude, 1);
  Serial.println(F(" m"));

  delay(1000);                              // 1 Hz update
}

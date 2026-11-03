/*
  ESP32 UART pin finder  -  find which header hole is TX and which is GND

  WIRING (router header CN1 -> ESP32 DevKit)
  ------------------------------------------
  Router USB port metal shell (GND) -> ESP32 GND
  Header hole 1 (marked "1")        -> GPIO25 (D25)
  Header hole 2                     -> GPIO26 (D26)
  Header hole 3                     -> GPIO27 (D27)
  Header hole 4                     -> GPIO14 (D14)

  Do NOT connect ESP32 3V3 or VIN to anything.
  Do NOT connect the router's VCC (3.3V) pin to the ESP32.
  All four pins are INPUTS only, nothing is driven.
  The router has its own power adapter.

  HOW TO USE
  ----------
  1. Board: ESP32 Dev Module. Serial Monitor at 115200 baud.
  2. Press EN on the ESP32 once.
  3. Plug in the router's power.
  4. Watch for ~10 seconds.

  HOW TO READ THE RESULT
  ----------------------
  edges in the hundreds/thousands -> that hole is the router TX
  stays LOW, edges=0              -> GND
  stays HIGH, edges=0 or few      -> power pin or RX (do not connect)
*/


const int pins[4] = {25, 26, 27, 14};
volatile uint32_t edges[4];
void IRAM_ATTR h0() { edges[0]++; }
void IRAM_ATTR h1() { edges[1]++; }
void IRAM_ATTR h2() { edges[2]++; }
void IRAM_ATTR h3() { edges[3]++; }
void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 4; i++) pinMode(pins[i], INPUT_PULLUP);
  attachInterrupt(pins[0], h0, CHANGE);
  attachInterrupt(pins[1], h1, CHANGE);
  attachInterrupt(pins[2], h2, CHANGE);
  attachInterrupt(pins[3], h3, CHANGE);
}
void loop() {
  for (int i = 0; i < 4; i++)
    Serial.printf("hole%d %s edges=%lu | ", i + 1,
                  digitalRead(pins[i]) ? "HIGH" : "LOW",
                  (unsigned long)edges[i]);
  Serial.println();
  delay(500);
}



/*
  header_finder  -  ESP32 router boot log reader

  WIRING (router header CN1 -> ESP32 DevKit)
  ------------------------------------------
  Router TX hole (found with the pin scanner) -> RX2 (GPIO16)
  Router USB port metal shell (GND)           -> ESP32 GND

  Leave every other header hole empty.
  Do NOT connect ESP32 3V3 or VIN to anything.
  Do NOT connect the router's VCC (3.3V) pin to the ESP32.
  Do NOT use RX0/TX0 (those are the USB link to the PC).

  HOW TO USE
  ----------
  1. Board: ESP32 Dev Module. Serial Monitor at 115200 baud.
  2. Press EN on the ESP32 once.
  3. Wait until "[bytes received: 0]" prints.
  4. THEN plug in the router's power. It only prints for a few seconds.

  HOW TO READ THE RESULT
  ----------------------
  bytes received > 0   -> the router is printing, read the text on screen
  readable words       -> bootloader or boot ROM is running
  random symbols       -> alive, but the baud rate is wrong (try 57600 or 9600)
  stays at 0           -> check the GND wire and that TX goes to RX2

  The ESP32's own startup text (rst:0x1 ... ets Jul 29 2019) is normal.
  Ignore it.
*/

uint32_t n = 0;  // total bytes received from the router

void setup() {
  Serial.begin(115200);                       
  Serial2.begin(115200, SERIAL_8N1, 16, -1);  

void loop() {
  
  while (Serial2.available()) {
    Serial.write(Serial2.read());
    n++;
  }

  
  static uint32_t t;
  if (millis() - t > 3000) {
    t = millis();
    Serial.printf("\n[bytes received: %lu]\n", n);
  }
}  

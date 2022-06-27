#include <Arduino.h>
#include "heltec.h"

#include "setups/setup_bt.hpp"
#include "setups/setup_lora.hpp"
#include "setups/setup_bme.hpp"
#include "setups/setup_sd.hpp"
// #include "setups/setup_gps.hpp"
#include "setups/setup_tasks.hpp"

void setup() {
  Heltec.begin(false, true, true, true, LORA_BAND);
  setup_bt();
  setup_lora();
  setup_bme();
  setup_sd();
  // setup_gps();
  digitalWrite(LED, HIGH);
  Serial.print("modules init");
  bluetooth_serial.print("modules init");
  setup_tasks();
}

void loop() {

}
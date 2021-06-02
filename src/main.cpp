#include <Arduino.h>
#include "heltec.h"

#include "setup_lora.hpp"
#include "setup_tasks.hpp"

void setup() {
  Heltec.begin(true, false, true, true, LORA_BAND);
  setup_lora();
  setup_tasks();
}

void loop() {

}
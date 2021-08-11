#ifndef INCLUDE_SETUPS_SETUP_SD_H__
#define INCLUDE_SETUPS_SETUP_SD_H__
#include <SPI.h>
#include "SD.h"

#include "setups/setup_bt.hpp"

#define MICRO_SD_SCK 32
#define MICRO_SD_MISO 33
#define MICRO_SD_MOSI 2
#define MICRO_SD_CS 23

File altitude_logger;

SPIClass spi1;

void setup_sd() {
  SPIClass(1);
  spi1.begin(MICRO_SD_SCK, MICRO_SD_MISO, MICRO_SD_MOSI, MICRO_SD_CS);
  
  if (!SD.begin(MICRO_SD_CS, spi1)) {
    Serial.println("Erro ao abrir o cartão sd!");
    bluetooth_serial.println("Erro ao abrir o cartão sd!");
    ESP.restart();
  }
  Serial.println("sd init");
  bluetooth_serial.println("sd init");
}

#endif // INCLUDE_SETUPS_SETUP_SD_H__

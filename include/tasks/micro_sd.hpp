#ifndef INCLUDE_TASKS_MICRO_SD_H__
#define INCLUDE_TASKS_MICRO_SD_H__
#include <SPI.h>

#include "SD.h"
#include "heltec.h"
#include "setup_tasks.hpp"

#define MICRO_SD_SCK 33
#define MICRO_SD_MISO 2
#define MICRO_SD_MOSI 32
#define MICRO_SD_CS 23

#define sd_chip_select 23
#define led_pin 25

File altitude_logger;

SPIClass spi1;

void micro_sd_code(void* parameters) {
  pinMode(sd_chip_select, OUTPUT);
  pinMode(led_pin, OUTPUT);

  SPIClass(1);
  spi1.begin(MICRO_SD_SCK, MICRO_SD_MISO, MICRO_SD_MOSI, MICRO_SD_CS);

  // digitalWrite(SS, LOW);
  // digitalWrite(sd_chip_select, HIGH);

  uint64_t time = 0;
  float altitude = 0;
  bool recovery = false;
  // LoRa.sleep();
  // digitalWrite(SS, LOW);
  if (!SD.begin(MICRO_SD_CS, spi1)) {
    Serial.println("Erro ao abrir o cartão sd!");
    bool status = false;
    // xQueueSend(error_alarm_queue_micro_sd, &status, portMAX_DELAY);
    ESP.restart();
  }
  uint8_t module_ok = 1;
  xQueueSend(led_queue_sd_ok, &module_ok, portMAX_DELAY);
  digitalWrite(led_pin, HIGH);

  // uint64_t timer = millis();
  // uint8_t count = 0;
  while (true) {
    xQueueReceive(micro_sd_queue_altitude, &altitude, portMAX_DELAY);
    xQueueReceive(micro_sd_queue_time, &time, portMAX_DELAY);
    xQueueReceive(micro_sd_queue_recovery, &recovery, 1);
    // xSemaphoreTake(lora_semaphore, portMAX_DELAY);
    // LoRa.sleep();
    // digitalWrite(SS, LOW);
    // digitalWrite(sd_chip_select, HIGH);

    altitude_logger = SD.open("/alt_log.csv", FILE_APPEND);

    if (altitude_logger) {
      altitude_logger.print(time);
      altitude_logger.print(",");
      altitude_logger.print(altitude);
      altitude_logger.print(",");
      altitude_logger.println(recovery);
      altitude_logger.close();
      // count++;
    } else {
      Serial.println("Erro na gravacao");
      digitalWrite(led_pin, LOW);
    }
    // digitalWrite(SS, HIGH);
    // digitalWrite(sd_chip_select, LOW);
    
    // xSemaphoreGive(lora_semaphore);

    // if (millis() > timer + 1000) {
    //   Serial.println(count);
    //   while (true) {
    //   }
    // }
  }
}

#endif  // INCLUDE_TASKS_MICRO_SD_H__

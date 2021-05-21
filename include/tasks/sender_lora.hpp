#ifndef INCLUDE_TASKS_SENDER_LORA_H__
#define INCLUDE_TASKS_SENDER_LORA_H__
#include "heltec.h"
#include "setup_tasks.hpp"

void sender_lora_code(void* parameters) {
  float altitude = 0;
  uint64_t time = 0;
  bool recovery = false;
  bool init = false;

  uint64_t timer = 0;
  // xQueueReceive(sender_lora_queue_init, &init ,portMAX_DELAY);

  while(true){
    xQueueReceive(sender_lora_queue_altitude, &altitude, portMAX_DELAY);
    xQueueReceive(sender_lora_queue_time, &time, portMAX_DELAY);
    xQueueReceive(sender_lora_queue_recovery, &recovery, pdMS_TO_TICKS(1));
    xSemaphoreTake(lora_semaphore, portMAX_DELAY);
    // Serial.print("\tAltitude: "); Serial.println(altitude);
    // timer = millis();
    LoRa.beginPacket();
    LoRa.write(0xFF);
    LoRa.write(0xF3);
    LoRa.write((uint8_t*)(&altitude), sizeof(altitude));
    LoRa.write((uint8_t*)(&time), sizeof(time));
    LoRa.write(recovery);
    LoRa.endPacket();
    // Serial.println(millis()-timer);
    xSemaphoreGive(lora_semaphore);
    vTaskDelay(1);
  }
}

#endif // INCLUDE_TASKS_SENDER_LORA_H__

#ifndef INCLUDE_TASKS_SENDER_LORA_H__
#define INCLUDE_TASKS_SENDER_LORA_H__
#include "setups/setup_tasks.hpp"

void sender_lora_code(void* parameters) {
  float altitude = 0;
  uint64_t time = 0;
  bool recovery = false;
  float latitude = 0;
  float longitude = 0;

  while(true){
    xQueueReceive(sender_lora_queue_altitude, &altitude, portMAX_DELAY);
    xQueueReceive(sender_lora_queue_time, &time, portMAX_DELAY);
    xQueueReceive(sender_lora_queue_recovery, &recovery, 1);
    // xQueueReceive(sender_lora_queue_latitude, &latitude, 1);
    // xQueueReceive(sender_lora_queue_longitude, &longitude, 1);
    LoRa.beginPacket();
    LoRa.write(0xFF);
    LoRa.write(0xF3);
    LoRa.write((uint8_t*)(&altitude), sizeof(altitude));
    LoRa.write((uint8_t*)(&time), sizeof(time));
    LoRa.write(recovery);
    // LoRa.write((uint8_t*)(&latitude), sizeof(altitude));
    // LoRa.write((uint8_t*)(&longitude), sizeof(longitude));
    LoRa.endPacket();
    // Serial.println("Send Lora");
    // bluetooth_serial.println("Send Lora");
  }
}

#endif // INCLUDE_TASKS_SENDER_LORA_H__

#ifndef INCLUDE_TASKS_MICRO_SD_H__
#define INCLUDE_TASKS_MICRO_SD_H__
#include "setups/setup_sd.hpp"
#include "setups/setup_tasks.hpp"

void micro_sd_code(void* parameters) {
  uint64_t time = 0;
  float altitude = 0;
  bool recovery = false;
  float latitude = 0;
  float longitude = 0;

  while (true) {
    xQueueReceive(micro_sd_queue_altitude, &altitude, portMAX_DELAY);
    xQueueReceive(micro_sd_queue_time, &time, portMAX_DELAY);
    xQueueReceive(micro_sd_queue_recovery, &recovery, 1);
    // xQueueReceive(micro_sd_queue_latitude, &latitude, 1);
    // xQueueReceive(micro_sd_queue_longitude, &longitude, 1);

    altitude_logger = SD.open("/alt_log.csv", FILE_APPEND);

    if (altitude_logger) {
      altitude_logger.print(time);
      altitude_logger.print(",");
      altitude_logger.print(altitude);
      altitude_logger.print(",");
      altitude_logger.print(recovery);
      // altitude_logger.print(",");
      // altitude_logger.print(latitude, 6);
      // altitude_logger.print(",");
      // altitude_logger.print(longitude, 6);
      altitude_logger.println();
      altitude_logger.close();
      // count++;
    } else {
      Serial.println("Erro na gravacao");
      bluetooth_serial.println("Erro na gravacao");
      digitalWrite(LED, LOW);
    }
  }
}

#endif  // INCLUDE_TASKS_MICRO_SD_H__

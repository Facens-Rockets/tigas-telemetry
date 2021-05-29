#ifndef INCLUDE_TASKS_MICRO_SD_H__
#define INCLUDE_TASKS_MICRO_SD_H__
#include <SPI.h>
#include "heltec.h"
#include "SD.h"
#include "setup_tasks.hpp"

#define sd_chip_select 3

File altitude_logger;

void micro_sd_code(void* parameters) {
  uint64_t time = 0;
  float altitude = 0;
  
  if(!SD.begin(sd_chip_select)){
    Serial.println("Erro ao abrir o cartão sd!");
    // vTaskDelete();
  }

  while(true){
    altitude_logger = SD.open("alt_log.csv", FILE_WRITE);

    xQueueReceive(micro_sd_queue_altitude, &altitude, portMAX_DELAY);
    xQueueReceive(micro_sd_queue_time, &time, portMAX_DELAY);

    if(altitude_logger){
      altitude_logger.print(time);
      altitude_logger.print(",");
      altitude_logger.println(altitude);
      altitude_logger.close();
    }
  }
}

#endif // INCLUDE_TASKS_MICRO_SD_H__

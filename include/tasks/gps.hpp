#ifndef INCLUDE_TASKS_GPS_H__
#define INCLUDE_TASKS_GPS_H__
#include "setups/setup_gps.hpp"
#include "setups/setup_tasks.hpp"

void gps_code(void *pvParameters) {
  float latitude = 0;
  float longitude = 0;
  bool calibration = false;
  int satellites = 0;

  while(!calibration) {
    while (gps_serial.available()) gps.encode(gps_serial.read());

    if (gps.satellites.isValid()) {
      satellites = gps.satellites.value();
      xQueueSend(debug_queue_satellites, &satellites, portMAX_DELAY);
    }

    if (gps.location.isValid()) {
      latitude = gps.location.lat();
      longitude = gps.location.lng();
      xQueueSend(debug_queue_latitude, &latitude, portMAX_DELAY);
      xQueueSend(debug_queue_longitude, &longitude, portMAX_DELAY);
    }
    xQueueReceive(gps_queue_calibration, &calibration, 100);
  }

  while (true) {
    while (gps_serial.available()) gps.encode(gps_serial.read());

    if (gps.location.isValid()) {
      latitude = gps.location.lat();
      longitude = gps.location.lng();
      xQueueSend(micro_sd_queue_latitude, &latitude, portMAX_DELAY);
      xQueueSend(micro_sd_queue_longitude, &longitude, portMAX_DELAY);
      xQueueSend(sender_lora_queue_latitude, &latitude, portMAX_DELAY);
      xQueueSend(sender_lora_queue_longitude, &longitude, portMAX_DELAY);
    }

    vTaskDelay(1);
  }
}

#endif  // INCLUDE_TASKS_GPS_H__

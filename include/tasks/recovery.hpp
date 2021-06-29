#ifndef INCLUDE_TASKS_RECOVERY_H__
#define INCLUDE_TASKS_RECOVERY_H__
#include "heltec.h"
#include "setup_tasks.hpp"

#define BME_SCALE 2

#define recovery_pin 12

void trigger_recovery() {
  digitalWrite(recovery_pin, HIGH);
  vTaskDelay(pdMS_TO_TICKS(200));
  digitalWrite(recovery_pin, LOW);
}

void recovery_code(void* parameters) {
  pinMode(recovery_pin, OUTPUT);

  float altitude = 0;
  // float last_altitude = 0;
  float variation = 0;
  float initial_altitude = 0;
  float max_altitude = 0;
  bool recovery = false;
  bool first = true;
  // uint8_t i = 0;
  // uint64_t timer = xTaskGetTickCount();

  while (true) {
    xQueueReceive(recovery_queue_altitude, &altitude, portMAX_DELAY);
    // xQueueReceive(recovery_queue_calibration, &first, 1);
    // xQueueSend(plot_oled_queue_altitude, &altitude, pdMS_TO_TICKS(1));

    if (first) {
      first = false;
      // max_altitude = altitude;
      initial_altitude = altitude;
    }

    variation = (initial_altitude - altitude) * -1;


    if (altitude > max_altitude) {
      max_altitude = altitude;
      // xQueueSend(plot_oled_queue_max_altitude, &max_altitude, portMAX_DELAY);
    } else if (variation > 10 && altitude < (max_altitude - (BME_SCALE * 2))) {
      if (!recovery) {
        Serial.println("Recovery triggered");
        recovery = true;
        trigger_recovery();
        xQueueSend(micro_sd_queue_recovery, &recovery, portMAX_DELAY);
        xQueueSend(sender_lora_queue_recovery, &recovery, portMAX_DELAY);
        xQueueSend(buzzer_alarm_queue_recovery, &recovery, portMAX_DELAY);
        // xQueueSend(plot_oled_queue_recovery, &recovery, portMAX_DELAY);
      }
    }
    // xQueueSend(plot_oled_queue_variation, &variation, portMAX_DELAY);
    // i++;
    // if (i >= 13) {
    //   Serial.println("Recovery triggered");
    //   recovery = true;
    //   xQueueSend(plot_oled_queue_recovery, &recovery, portMAX_DELAY);
    //   xQueueSend(buzzer_alarm_queue_recovery, &recovery, portMAX_DELAY);
    //   recovery = false;
    // }
  }
  // else {
  //   i = 0;
  // }
}

#endif  // INCLUDE_TASKS_RECOVERY_H__
#ifndef INCLUDE_TASKS_RECOVERY_H__
#define INCLUDE_TASKS_RECOVERY_H__
#include "heltec.h"
#include "setups/setup_tasks.hpp"

#define BME_SCALE 10

#define recovery_pin 13

void trigger_recovery() {
  digitalWrite(recovery_pin, HIGH);
  vTaskDelay(pdMS_TO_TICKS(200));
  digitalWrite(recovery_pin, LOW);
}

void recovery_code(void* parameters) {
  pinMode(recovery_pin, OUTPUT);

  float altitude = 0;
  float variation = 0;
  float initial_altitude = 0;
  float max_altitude = 0;
  bool recovery = false;
  
  xQueueReceive(recovery_queue_altitude, &initial_altitude, portMAX_DELAY);
  while (true) {
    xQueueReceive(recovery_queue_altitude, &altitude, portMAX_DELAY);

    variation = (initial_altitude - altitude) * -1;

    if (altitude > max_altitude) {
      max_altitude = altitude;
      // xQueueSend(plot_oled_queue_max_altitude, &max_altitude, portMAX_DELAY);
    } else if (variation > 5 && altitude < (max_altitude - (BME_SCALE * 2))) {
      if (!recovery) {
        Serial.println("Recovery triggered");
        recovery = true;
        xQueueSend(micro_sd_queue_recovery, &recovery, portMAX_DELAY);
        xQueueSend(sender_lora_queue_recovery, &recovery, portMAX_DELAY);
        xQueueSend(buzzer_alarm_queue_recovery, &recovery, portMAX_DELAY);
        // xQueueSend(plot_oled_queue_recovery, &recovery, portMAX_DELAY);
        trigger_recovery();
      }
    }
  }
}

#endif  // INCLUDE_TASKS_RECOVERY_H__
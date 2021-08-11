#ifndef INCLUDE_TASKS_READ_BMP_H__
#define INCLUDE_TASKS_READ_BMP_H__
#include "setups/setup_bme.hpp"
#include "setups/setup_tasks.hpp"
#include "setups/setup_bt.hpp"
#include "tasks/buzzer_alarm.hpp"

void read_bmp_code(void* parameters) {
  float altitude = 0;
  uint64_t timer = 0;
  bool calibration = false;

  while (!calibration) {
    altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
    xQueueSend(debug_queue_altitude, &altitude, portMAX_DELAY);
    xQueueReceive(read_bmp_queue_calibration, &calibration, pdMS_TO_TICKS(20));
  }

  while (true) {
    altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
    timer = millis();

    xQueueSend(debug_queue_altitude, &altitude, portMAX_DELAY);
    xQueueSend(recovery_queue_altitude, &altitude, portMAX_DELAY);
    xQueueSend(micro_sd_queue_altitude, &altitude, portMAX_DELAY);
    xQueueSend(micro_sd_queue_time, &timer, portMAX_DELAY);
    xQueueSend(sender_lora_queue_altitude, &altitude, portMAX_DELAY);
    xQueueSend(sender_lora_queue_time, &timer, portMAX_DELAY);
    // xQueueSend(plot_oled_queue_altitude, &altitude, portMAX_DELAY);

    vTaskDelay(pdMS_TO_TICKS(20));
  }
}

#endif  // INCLUDE_TASKS_READ_BMP_H__

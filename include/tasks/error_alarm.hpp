#ifndef INCLUDE_TASKS_ERROR_ALARM_H__
#define INCLUDE_TASKS_ERROR_ALARM_H__
#include "setup_tasks.hpp"
#include "tasks/buzzer_alarm.hpp"

void error_alarm_code(void* parameters) {
  bool bmp = true;
  bool micro_sd = true;
  bool calibration = false;
  while (true) {
    xQueueReceive(error_alarm_queue_calibration_button, &calibration,
                  portMAX_DELAY);
    xQueueReceive(error_alarm_queue_bmp, &bmp, pdMS_TO_TICKS(500));
    xQueueReceive(error_alarm_queue_micro_sd, &micro_sd, pdMS_TO_TICKS(500));

    if (calibration) {
      if (!bmp || !micro_sd) {
        vTaskDelete(plot_oled_task);
        digitalWrite(buzzer_pin, HIGH);
        Heltec.display->clear();
        if (!bmp) {
          Heltec.display->drawString(0, 0, "Error BMP");
        }
        if (!micro_sd) {
          Heltec.display->drawString(0, 10, "Error SD");
        }
        Heltec.display->drawString(0, 30, "Rebooting...");
        vTaskDelay(pdMS_TO_TICKS(500));
        digitalWrite(buzzer_pin, LOW);
        ESP.restart();
      }
    }
  }
}

#endif  // INCLUDE_TASKS_ERROR_ALARM_H__

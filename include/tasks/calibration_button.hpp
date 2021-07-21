#ifndef INCLUDE_TASKS_CALIBRATION_BUTTON_H__
#define INCLUDE_TASKS_CALIBRATION_BUTTON_H__
#include "setup_tasks.hpp"
#include "tasks/buzzer_alarm.hpp  "

#define calibration_button_pin 22

void calibration_button_code(void* parameters) {
  bool first = true;
  bool calibration = false;
  pinMode(calibration_button_pin, INPUT_PULLUP);

  while (true) {
    // Serial.println(digitalRead(calibration_button_pin));
    if (!digitalRead(calibration_button_pin)) {
      vTaskDelay(pdMS_TO_TICKS(20));
      while (!digitalRead(calibration_button_pin)) {
      }
      if (first) {
        first = false;
      } else {
        calibration = true;
        digitalWrite(buzzer_pin, HIGH);
        vTaskDelay(pdMS_TO_TICKS(200));
        digitalWrite(buzzer_pin, LOW);

        xQueueSend(calibration_button_queue_button, &calibration,
                   portMAX_DELAY);
        // xQueueSend(error_alarm_queue_calibration_button, &calibration,
        //            portMAX_DELAY);
        Serial.println("calibrated");
        vTaskDelete(calibration_button_task);
      }
      // if (!digitalRead(calibration_button_pin)) {
      // }
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

#endif  // INCLUDE_TASKS_CALIBRATION_BUTTON_H__

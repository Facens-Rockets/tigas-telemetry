#ifndef INCLUDE_TASKS_BUZZER_ALARM_H__
#define INCLUDE_TASKS_BUZZER_ALARM_H__
#include "heltec.h"
#include "setup_tasks.hpp"

#define buzzer_pin 13

void buzzer_alarm_code(void* parameters) {
  bool recovery = false;

  pinMode(buzzer_pin, OUTPUT);

  while (true) {
    xQueueReceive(buzzer_alarm_queue_recovery, &recovery, portMAX_DELAY);

    while (recovery) {
      digitalWrite(buzzer_pin, HIGH);
      vTaskDelay(pdMS_TO_TICKS(200));
      digitalWrite(buzzer_pin, LOW);
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  }
}

#endif  // INCLUDE_TASKS_BUZZER_ALARM_H__
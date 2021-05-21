#ifndef INCLUDE_SETUP_TASKS_H__
#define INCLUDE_SETUP_TASKS_H__
#include "heltec.h"

TaskHandle_t plot_oled_task;
TaskHandle_t read_bmp_task;
TaskHandle_t save_file_task;
TaskHandle_t recovery_task;
TaskHandle_t buzzer_alarm_task;
TaskHandle_t sender_lora_task;

QueueHandle_t plot_oled_queue_variation;
QueueHandle_t plot_oled_queue_altitude;
QueueHandle_t plot_oled_queue_recovery;
QueueHandle_t plot_oled_queue_max_altitude;

QueueHandle_t sender_lora_queue_time;
QueueHandle_t sender_lora_queue_altitude;
QueueHandle_t sender_lora_queue_recovery;
QueueHandle_t sender_lora_queue_init;

// QueueHandle_t recovery_queue_pressure;
QueueHandle_t recovery_queue_altitude;

QueueHandle_t buzzer_alarm_queue_recovery;

SemaphoreHandle_t lora_semaphore;

#include "tasks/plot_oled.hpp"
#include "tasks/read_bmp.hpp"
#include "tasks/recovery.hpp"
#include "tasks/buzzer_alarm.hpp"
#include "tasks/sender_lora.hpp"
// #include "tasks/save_file.hpp"


void core_zero(int core = 0) {
  xTaskCreatePinnedToCore(read_bmp_code, "bmp", 2000, NULL, 2, &read_bmp_task, core);
  xTaskCreatePinnedToCore(recovery_code, "recovery", 2000, NULL, 1, &recovery_task, core);
}
void core_one(int core = 1) {
  xTaskCreatePinnedToCore(sender_lora_code, "lora", 2000, NULL, 3, &sender_lora_task, core);
  // vTaskSuspend(sender_lora_task);
  xTaskCreatePinnedToCore(plot_oled_code, "oled", 2000, NULL, 2, &plot_oled_task, core);
  xTaskCreatePinnedToCore(buzzer_alarm_code, "buzzer", 2000, NULL, 2, &buzzer_alarm_task, core);
  // xTaskCreatePinnedToCore(save_file_code, "file", 5000, NULL, 1, &save_file_task, core);
}

void setup_tasks() {
  plot_oled_queue_variation = xQueueCreate(1, sizeof(float));
  plot_oled_queue_altitude = xQueueCreate(1, sizeof(float));
  plot_oled_queue_recovery = xQueueCreate(1, sizeof(bool));
  plot_oled_queue_max_altitude = xQueueCreate(1, sizeof(float));
  
  recovery_queue_altitude = xQueueCreate(1, sizeof(float));
  
  buzzer_alarm_queue_recovery = xQueueCreate(1, sizeof(bool));
  
  sender_lora_queue_recovery = xQueueCreate(1, sizeof(bool));
  sender_lora_queue_init = xQueueCreate(1, sizeof(bool));
  sender_lora_queue_altitude = xQueueCreate(1, sizeof(float));
  sender_lora_queue_time = xQueueCreate(1, sizeof(uint64_t));

  lora_semaphore = xSemaphoreCreateMutex();

  core_zero();
  core_one();
}

#endif // INCLUDE_SETUP_TASKS_H__
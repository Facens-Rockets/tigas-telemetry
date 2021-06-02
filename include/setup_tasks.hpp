#ifndef INCLUDE_SETUP_TASKS_H__
#define INCLUDE_SETUP_TASKS_H__
#include "heltec.h"

TaskHandle_t plot_oled_task;
TaskHandle_t read_bmp_task;
TaskHandle_t save_file_task;
TaskHandle_t recovery_task;
TaskHandle_t buzzer_alarm_task;
TaskHandle_t sender_lora_task;
TaskHandle_t micro_sd_task;
TaskHandle_t calibration_button_task;
TaskHandle_t error_alarm_task;

QueueHandle_t recovery_queue_calibration;

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

QueueHandle_t micro_sd_queue_altitude;
QueueHandle_t micro_sd_queue_time;

QueueHandle_t error_alarm_queue_bmp;
QueueHandle_t error_alarm_queue_micro_sd;
QueueHandle_t error_alarm_queue_calibration_button;

QueueHandle_t calibration_button_queue_button;

SemaphoreHandle_t lora_semaphore;

#include "tasks/plot_oled.hpp"
#include "tasks/read_bmp.hpp"
#include "tasks/recovery.hpp"
#include "tasks/buzzer_alarm.hpp"
#include "tasks/sender_lora.hpp"
#include "tasks/micro_sd.hpp"
#include "tasks/calibration_button.hpp"
#include "tasks/error_alarm.hpp"
// #include "tasks/save_file.hpp"


void core_zero(int core = 0) {
  xTaskCreatePinnedToCore(read_bmp_code, "bmp", 3000, NULL, 3, &read_bmp_task, core);
  xTaskCreatePinnedToCore(recovery_code, "recovery", 3000, NULL, 1, &recovery_task, core);
  // xTaskCreatePinnedToCore(error_alarm_code, "alarm", 3000, NULL, 1, &error_alarm_task, core);
}
void core_one(int core = 1) {
  // xTaskCreatePinnedToCore(sender_lora_code, "lora", 2000, NULL, 3, &sender_lora_task, core);
  xTaskCreatePinnedToCore(calibration_button_code, "calibration", 1000, NULL, 2, &calibration_button_task, core);
  xTaskCreatePinnedToCore(plot_oled_code, "oled", 2000, NULL, 2, &plot_oled_task, core);
  xTaskCreatePinnedToCore(buzzer_alarm_code, "buzzer", 2000, NULL, 2, &buzzer_alarm_task, core);
  xTaskCreatePinnedToCore(micro_sd_code, "sd", 10000, NULL, 2, &micro_sd_task, core);
}

void setup_tasks() {
  plot_oled_queue_variation = xQueueCreate(1, sizeof(float));
  plot_oled_queue_altitude = xQueueCreate(1, sizeof(float));
  plot_oled_queue_recovery = xQueueCreate(1, sizeof(bool));
  plot_oled_queue_max_altitude = xQueueCreate(1, sizeof(float));
  
  recovery_queue_altitude = xQueueCreate(1, sizeof(float));
  recovery_queue_calibration = xQueueCreate(1, sizeof(bool));
  
  buzzer_alarm_queue_recovery = xQueueCreate(1, sizeof(bool));
  
  sender_lora_queue_recovery = xQueueCreate(1, sizeof(bool));
  sender_lora_queue_init = xQueueCreate(1, sizeof(bool));
  sender_lora_queue_altitude = xQueueCreate(1, sizeof(float));
  sender_lora_queue_time = xQueueCreate(1, sizeof(uint64_t));

  micro_sd_queue_altitude = xQueueCreate(1, sizeof(float));
  micro_sd_queue_time = xQueueCreate(1, sizeof(uint64_t));

  error_alarm_queue_bmp = xQueueCreate(1, sizeof(bool));
  error_alarm_queue_micro_sd = xQueueCreate(1, sizeof(bool));
  error_alarm_queue_calibration_button = xQueueCreate(1, sizeof(bool));

  calibration_button_queue_button = xQueueCreate(1, sizeof(bool));

  lora_semaphore = xSemaphoreCreateMutex();

  core_zero();
  core_one();
}

#endif // INCLUDE_SETUP_TASKS_H__
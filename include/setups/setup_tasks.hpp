#ifndef INCLUDE_SETUP_TASKS_H__
#define INCLUDE_SETUP_TASKS_H__
#include "heltec.h"

// TaskHandle_t plot_oled_task;
TaskHandle_t read_bmp_task;
TaskHandle_t recovery_task;
TaskHandle_t buzzer_alarm_task;
TaskHandle_t sender_lora_task;
TaskHandle_t micro_sd_task;
TaskHandle_t calibration_button_task;
TaskHandle_t gps_task;
TaskHandle_t debug_task;

QueueHandle_t recovery_queue_calibration;

// QueueHandle_t plot_oled_queue_variation;
// QueueHandle_t plot_oled_queue_altitude;
// QueueHandle_t plot_oled_queue_recovery;
// QueueHandle_t plot_oled_queue_max_altitude;

QueueHandle_t sender_lora_queue_time;
QueueHandle_t sender_lora_queue_altitude;
QueueHandle_t sender_lora_queue_recovery;
QueueHandle_t sender_lora_queue_init;
QueueHandle_t sender_lora_queue_latitude;
QueueHandle_t sender_lora_queue_longitude;

QueueHandle_t recovery_queue_altitude;

QueueHandle_t buzzer_alarm_queue_recovery;

QueueHandle_t micro_sd_queue_altitude;
QueueHandle_t micro_sd_queue_time;
QueueHandle_t micro_sd_queue_recovery;
QueueHandle_t micro_sd_queue_latitude;
QueueHandle_t micro_sd_queue_longitude;

QueueHandle_t read_bmp_queue_calibration;

QueueHandle_t gps_queue_calibration;

QueueHandle_t debug_queue_altitude;
QueueHandle_t debug_queue_satellites;
QueueHandle_t debug_queue_latitude;
QueueHandle_t debug_queue_longitude;
QueueHandle_t debug_queue_recovery;

SemaphoreHandle_t debug_semaphore;

// #include "tasks/plot_oled.hpp"
#include "tasks/read_bmp.hpp"
#include "tasks/recovery.hpp"
#include "tasks/buzzer_alarm.hpp"
#include "tasks/sender_lora.hpp"
#include "tasks/micro_sd.hpp"
#include "tasks/calibration_button.hpp"
#include "tasks/sender_lora.hpp"
#include "tasks/gps.hpp"
#include "tasks/debug.hpp"


void core_zero(int core = 0) {
  xTaskCreatePinnedToCore(read_bmp_code, "bmp", 3000, NULL, 4, &read_bmp_task, core);
  xTaskCreatePinnedToCore(recovery_code, "recovery", 3000, NULL, 3, &recovery_task, core);
  xTaskCreatePinnedToCore(micro_sd_code, "sd", 10000, NULL, 2, &micro_sd_task, core);
}

void core_one(int core = 1) {
  xTaskCreatePinnedToCore(sender_lora_code, "lora", 2000, NULL, 2, &sender_lora_task, core);
  xTaskCreatePinnedToCore(calibration_button_code, "calibration", 1000, NULL, 2, &calibration_button_task, core);
  // xTaskCreatePinnedToCore(plot_oled_code, "oled", 2000, NULL, 2, &plot_oled_task, core);
  // xTaskCreatePinnedToCore(gps_code, "gps", 3000, NULL, 2, &gps_task, core);
  xTaskCreatePinnedToCore(buzzer_alarm_code, "buzzer", 2000, NULL, 2, &buzzer_alarm_task, core);
  xTaskCreatePinnedToCore(debug_code, "debug", 2000, NULL, 2, &debug_task, core);
  
}

void setup_tasks() {
  // plot_oled_queue_variation = xQueueCreate(1, sizeof(float));
  // plot_oled_queue_altitude = xQueueCreate(1, sizeof(float));
  // plot_oled_queue_recovery = xQueueCreate(1, sizeof(bool));
  // plot_oled_queue_max_altitude = xQueueCreate(1, sizeof(float));
  
  recovery_queue_altitude = xQueueCreate(1, sizeof(float));
  recovery_queue_calibration = xQueueCreate(1, sizeof(bool));
  
  buzzer_alarm_queue_recovery = xQueueCreate(1, sizeof(bool));

  sender_lora_queue_recovery = xQueueCreate(1, sizeof(bool));
  sender_lora_queue_init = xQueueCreate(1, sizeof(bool));
  sender_lora_queue_altitude = xQueueCreate(1, sizeof(float));
  sender_lora_queue_time = xQueueCreate(1, sizeof(uint64_t));
  sender_lora_queue_latitude = xQueueCreate(1, sizeof(float));
  sender_lora_queue_longitude = xQueueCreate(1, sizeof(float));

  micro_sd_queue_altitude = xQueueCreate(1, sizeof(float));
  micro_sd_queue_time = xQueueCreate(1, sizeof(uint64_t));
  micro_sd_queue_recovery = xQueueCreate(1, sizeof(bool));
  micro_sd_queue_latitude = xQueueCreate(1, sizeof(float));
  micro_sd_queue_longitude = xQueueCreate(1, sizeof(float));

  read_bmp_queue_calibration = xQueueCreate(1, sizeof(bool));
  
  gps_queue_calibration = xQueueCreate(1, sizeof(bool));

  debug_queue_altitude = xQueueCreate(1, sizeof(float));
  debug_queue_satellites = xQueueCreate(1, sizeof(int));
  debug_queue_recovery = xQueueCreate(1, sizeof(float));
  debug_queue_latitude = xQueueCreate(1, sizeof(float));
  debug_queue_longitude = xQueueCreate(1, sizeof(float));

  debug_semaphore = xSemaphoreCreateMutex();

  core_zero();
  core_one();
}

#endif // INCLUDE_SETUP_TASKS_H__
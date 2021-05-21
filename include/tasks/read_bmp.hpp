#ifndef INCLUDE_TASKS_READ_BMP_H__
#define INCLUDE_TASKS_READ_BMP_H__
#include "heltec.h"
#include "setup_tasks.hpp"

// #include "BME280.h"
#include <Adafruit_BME280.h>
#include <Wire.h>

#define SEALEVELPRESSURE_HPA (1013.25)

// BME280 bme(Wire,0x76);
// TwoWire secondI2C =
Adafruit_BME280 bme;

void read_bmp_code(void* parameters) {
  bool first = true;
  Wire1.begin(21, 22);

  // float pressure = 0;
  float altitude = 0;

  bool status_bme = bme.begin(0x76, &Wire1);

  if (!status_bme) {
    Serial.println(
        "Error communicating with bmp sensor, check wiring and I2C address");
    Serial.print("Sensor ID: 0x");
    Serial.println(bme.sensorID(), 16);
    Serial.print(
        "        ID of 0xFF probably means a bad address, a BMP 180 or BMP "
        "085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) {
      vTaskDelay(1);
    }
  }
  uint64_t timer = 0;
  uint64_t initial_timer = millis();
  while (true) {
    xSemaphoreTake(lora_semaphore, portMAX_DELAY);
    // pressure = bme.readPressure();
    altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
    timer = millis() - initial_timer;

    // Serial.print("Pressure: "); Serial.print(pressure);
    // Serial.print("\tAltitude: "); Serial.println(altitude);
    // timer = millis();
    xQueueSend(recovery_queue_altitude, &altitude, portMAX_DELAY);
    xQueueSend(plot_oled_queue_altitude, &altitude, portMAX_DELAY);
    xQueueSend(sender_lora_queue_altitude, &altitude, portMAX_DELAY);
    xQueueSend(sender_lora_queue_time, &timer, portMAX_DELAY);
    xSemaphoreGive(lora_semaphore);
    // vTaskResume(sender_lora_task);
    // xQueueSend(plot_oled_queue_altitude, &altitude, pdMS_TO_TICKS(1));
    // xQueueSend(plot_oled_queue_pressure, &pressure, portMAX_DELAY);
    // Serial.println(millis()-timer);
    // if(first){
    //   xQueueSend(sender_lora_queue_init, &first, portMAX_DELAY);
    //   first = false;
    // }

    vTaskDelay(pdMS_TO_TICKS(80));
  }
}

#endif  // INCLUDE_TASKS_READ_BMP_H__
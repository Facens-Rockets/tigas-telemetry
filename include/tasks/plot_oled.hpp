#ifndef INCLUDE_TASKS_PLOT_OLED_H__
#define INCLUDE_TASKS_PLOT_OLED_H__

#include "heltec.h"
#include "setup_tasks.hpp"

void plot_oled_code(void* parameters) {
  // float pressure = 0;
  float altitude = 0;
  // float initial_altitude = 0;
  float max_altitude = 0;
  float variation = 0;
  // bool first = true;
  bool recovery = false;

  // xQueueReceive(plot_oled_queue_altitude, &altitude, portMAX_DELAY);
  // initial_altitude = altitude;
  // uint64_t timer = 0;
  while (true) {
    xQueueReceive(plot_oled_queue_altitude, &altitude, 1);
    xQueueReceive(plot_oled_queue_variation, &variation, 1);
    xQueueReceive(plot_oled_queue_recovery, &recovery, 1);
    xQueueReceive(plot_oled_queue_max_altitude, &max_altitude, 1);

    Heltec.display->clear();

    Heltec.display->setFont(ArialMT_Plain_10);
    // Heltec.display->drawString(0, 0, "Presure: " + String(pressure) + " Pa");
    Heltec.display->drawString(0, 0, "Altitude: " + String(altitude) + " mts");
    Heltec.display->drawString(0, 20,
                               "Variação: " + String(variation) + " mts");
    Heltec.display->drawString(0, 10, "Altitude Max: " + String(max_altitude) + " mts");
    Heltec.display->drawString(0, 30, "Variação Max: " + String(max_altitude) + " mts");
    Heltec.display->drawString(0, 40, recovery ? "Recovery Triggered" : "Recovery waiting...");
                               
    Heltec.display->display();
    // Serial.println(millis() - timer);
    vTaskDelay(1);
  }
}

#endif  // INCLUDE_TASKS_PLOT_OLED_H__

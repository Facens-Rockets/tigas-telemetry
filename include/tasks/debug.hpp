#ifndef INCLUDE_TASKS_DEBUG_H__
#define INCLUDE_TASKS_DEBUG_H__
#include "setups/setup_tasks.hpp"

void debug_code(void *pvParameters) {
  float altitude = 0;
  int satellites = 0;
  float latitude = 0;
  float longitude = 0;
  bool recovery = false;

  while (true) {
    xQueueReceive(debug_queue_altitude, &altitude, 1);
    xQueueReceive(debug_queue_recovery, &recovery, 1);
    xQueueReceive(debug_queue_satellites, &satellites, 1);
    xQueueReceive(debug_queue_latitude, &latitude, 1);
    xQueueReceive(debug_queue_longitude, &longitude, 1);

    Serial.print("Alt:"); Serial.print(altitude);
    Serial.print(" Rec:"); Serial.print(recovery);
    Serial.print(" Sat:"); Serial.print(satellites);
    Serial.print(" Lat:"); Serial.print(latitude,6);
    Serial.print(" Lng:"); Serial.print(longitude,6);
    Serial.println();

    bluetooth_serial.print("Alt:"); bluetooth_serial.print(altitude);
    bluetooth_serial.print(" Rec:"); bluetooth_serial.print(recovery);
    bluetooth_serial.print(" Sat:"); bluetooth_serial.print(satellites);
    bluetooth_serial.print(" Lat:"); bluetooth_serial.print(latitude,6);
    bluetooth_serial.print(" Lng:"); bluetooth_serial.print(longitude,6);
    bluetooth_serial.println();

    vTaskDelay(1);
  }
}

#endif // INCLUDE_TASKS_DEBUG_H__

#ifndef INCLUDE_SETUPS_SETUP_BME_H__
#define INCLUDE_SETUPS_SETUP_BME_H__
#include <Adafruit_BME280.h>
#include <Wire.h>

#include "setups/setup_bt.hpp"

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

void setup_bme() {
  Wire.begin(4, 15);

  bool status_bme = bme.begin(0x76, &Wire);
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
    bluetooth_serial.println("XX Error bme XX");
    ESP.restart();
  }
  Serial.println("bme init");
  bluetooth_serial.println("bme init");
}

#endif // INCLUDE_SETUPS_SETUP_BME_H__

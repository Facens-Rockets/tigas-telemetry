#ifndef INCLUDE_SETUP_BT_H__
#define INCLUDE_SETUP_BT_H__
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial bluetooth_serial;

void setup_bt() {
  bluetooth_serial.begin("Tigas Avionics");
  Serial.println("bt init");
}

#endif // INCLUDE_SETUP_BT_H__

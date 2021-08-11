#ifndef INCLUDE_SETUPS_SETUP_GPS_H__
#define INCLUDE_SETUPS_SETUP_GPS_H__
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#define GPS_TX 0
#define GPS_RX 22
#define GPS_BAUDRATE 9600

TinyGPSPlus gps;

SoftwareSerial gps_serial(GPS_TX, GPS_RX);

void setup_gps() {
  gps_serial.begin(GPS_BAUDRATE);
}

#endif // INCLUDE_SETUPS_SETUP_GPS_H__

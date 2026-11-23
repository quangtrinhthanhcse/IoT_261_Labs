#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <Arduino.h>

// Sensor values (written by sensor task)
extern float glob_temperature;
extern float glob_humidity;

// ESP32 Access Point credentials
extern String ssid;
extern String password;

// Router credentials received from /settings
extern String wifi_ssid;
extern String wifi_password;

// Network status shared across tasks
extern bool isWifiConnected;
extern SemaphoreHandle_t xBinarySemaphoreInternet;

#endif
